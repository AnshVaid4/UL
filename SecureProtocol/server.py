import socket
import threading
import json
import os
from OpenSSL import crypto
from cryptography.hazmat.primitives import hashes, serialization
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives.asymmetric import padding
from cryptography.hazmat.primitives.asymmetric import rsa
from cryptography.hazmat.primitives.serialization import load_pem_private_key, load_pem_public_key
from hashlib import sha256
import time




active_sessions=[]  #Keep track of entity names
connections={}      #Keep a track of socket objects with respective entity name as dictionary key
TOTAL_CLIENTS=3     #No. of clients that server should host services for
stack=[]

def generate_keys():
    '''
    This is the initial step of the server to generate the private key and public key certificates
    for the server and all the entities
    '''

    #Check if entity A's directory is present which consists A's certificate and private key
    if not os.path.exists("A"):
        os.mkdir("A")

    #Check if entity B's directory is present which consists B's certificate and private key
    if not os.path.exists("B"):
        os.mkdir("B")
    
    #Check if entity C's directory is present which consists C's certificate and private key
    if not os.path.exists("C"):
        os.mkdir("C")
    
    #Check if entity S's directory is present which consists S's certificate and private key
    if not os.path.exists("S"):
        os.mkdir("S")   

    #Creating asymmetric RSA 2048 bits key pairs for the server and entities. Key has the integrity checks with SHA512 algorithm
    for entity in ['A', 'B', 'C', 'S']:
        key = crypto.PKey()
        key.generate_key(crypto.TYPE_RSA, 2048)
        
        cert = crypto.X509()
        cert.get_subject().CN = entity
        cert.set_serial_number(1000)
        cert.gmtime_adj_notBefore(0)
        cert.gmtime_adj_notAfter(1*24*60*60)
        cert.set_issuer(cert.get_subject())
        cert.get_subject().O = 'EE6032'  # Organization Name
        cert.get_subject().OU = "Communication & Security Protocols"  # Organizational Unit
        cert.get_subject().L = "Limerick"  # Locality (City)
        cert.get_subject().ST = "Limerick"  # State
        cert.get_subject().C = "IE"
        cert.set_pubkey(key)
        cert.get_subject().emailAddress = f'{entity.lower()}.socketchat@ee6032.com'
        cert.sign(key, 'sha512')
        
        #Respective entities' key pairs of respective entites are stored in their respective directory, 
        #and the certificate is also stored in the server for future distributions to authenticated clients
        with open(f'{entity}/{entity}_private.pem', 'wb') as priv_file:
            priv_file.write(crypto.dump_privatekey(crypto.FILETYPE_PEM, key))
        with open(f'{entity}/{entity}_cert.pem', 'wb') as cert_file:
            cert_file.write(crypto.dump_certificate(crypto.FILETYPE_PEM, cert))
        with open(f'S/{entity}_cert.pem', 'wb') as cert_file:
            cert_file.write(crypto.dump_certificate(crypto.FILETYPE_PEM, cert))




def sortNSendKeys(keys):
    '''
    Receive the key string, from client and sort it according to the sender, receiver, encrypted text, signature 
    and then forward it to correct receiver using correct socket object
    '''

    #SEG6S
    try:
        for items in keys:  # Encrypted nonce key string that were stored in stack from all the clients
            for key_sender,sender_SignedKeys in items.items():
                for key_receiver, value in sender_SignedKeys.items():
                    try:
                        if key_receiver != 'signature':
                            
                            # print(f'[+] From {key_sender}  to  {key_receiver}  sending  {value}  signed as  {sender_SignedKeys['signature']}')
                            conn = connections[key_receiver][0]
                            data = json.dumps({"sender": key_sender, "receiver": key_receiver, "nonce":value, "signature":sender_SignedKeys['signature']})+"<END>"
                            print(data)
                            conn.send(data.encode())
                            time.sleep(0.5)
                    except Exception as e:
                        break
                     
    except Exception as e:
        print(e)   
    
    print('\n\n')




def receiveKeys(server,entity):
    #SEG5S
    global stack
    lock=threading.Lock()

    try:
        lock.acquire()
        response = json.loads(server.recv(2048).decode())
        stack.append({entity:response})
        lock.release()        
    except Exception as e:
        print(e)




def forward_client_messages(conn, entity):
    '''
    Thread function to continuously listen for messages from a client and
    forward to other clients
    '''

    global connections
    while True:
        try:
            msg = json.loads(conn.recv(4096).decode().strip())  #Reciving from SEG8C
            msgreceiver=[]
            print(f"[+] Forwarding message from {msg.get('sender')} | message : {msg.get('msg')}")
            
            for key,value in connections.items():
                if key!=entity:
                    fwd = connections[key][0]
                    fwd.send(json.dumps(msg).encode())
                    msgreceiver.append(key)
            
            print(f"[+] Forwarded message to {','.join(msgreceiver)}\n")

        except Exception as e:
            print(f"[-] Error receiving message from {entity}: {e}")
            break

    print(f"[-] Stopping listener for {entity}")
    conn.close()
    del connections[entity]  # Remove from active connections




def fwdMsg():

    #SEG7S
    global connections
    
    for entity, conn_data in connections.items():
        conn = connections[entity][0]
        threading.Thread(target=forward_client_messages, args=(conn, entity), daemon=True).start()  #Reciving from SEG8C and forwarding to SEG8C receive_data() thread





def load_keys(entity):
    '''
    Server loads the certificate of the entity to derive its public key which is used later to verify didgital signatures
    of the nonce that is sent by the client
    '''

    with open(f'S/{entity}_cert.pem', 'rb') as cert_file:
        cert = crypto.load_certificate(crypto.FILETYPE_PEM, cert_file.read())
    return cert




def handle_client(server, addr):
    '''
    1. Initial connection request from the client and the response sequence from the server to client
    for authentication of the client connecting to it.
    Initially receives entity ID
    2. Server responds by sending 'AUTH_REQUEST', asking the client to authenticate itself first
    3. Server receives JSON formatted data from client having
                     {auth:True, message: <encrypted nonce using server's public key>, signature: <private key of client(SHA256(Nonce))>}
    4. Server gets loads its private key and decrypts the  encrypted message, i.e. plain-text nonce from JSON 
    5. Server loads the public key of the entity to verify the digital signature of client by verifying the SHA256(decrypted nonce)
    6. If successful then server sends the operation on nonce to client, this performs the mutual authentication by assuming the server's keys
    are not compromised.
    7. Server loads the certs of other entities, JSONify it and send to the client
    '''

    global active_sessions
    global TOTAL_CLIENTS
    global connections
    global stack
    
    #SEG1S
    #Initial connection request containing client ID
    entity = server.recv(1024).decode()
    print(f"[+] {entity} connected from {addr}")
    with open('S/S_cert.pem', 'rb') as file:
        S_cert = file.read().hex()
    message=json.dumps({'auth':"AUTH_REQUEST",'cert':S_cert}).encode()+b"<END>"
    server.send(message)

    #SEG2S
    #Authentication data in JSON format
    response = json.loads(server.recv(4096).decode()) #SEG2C
    if response.get("auth"):
        with open("S/S_private.pem", "rb") as f:
             #Loading server's private key to decrypt the message
             receiver_priv_key = load_pem_private_key(f.read(),password=None)
             decrypted_message = receiver_priv_key.decrypt(bytes.fromhex(response["message"]),
        						padding.OAEP(mgf=padding.MGF1(algorithm=hashes.SHA512()),
        						algorithm=hashes.SHA512(),label=None))
        
        #Loading the public key and verifying the signature by decrypting and equating SHA256(decrypted_nonce) == entity_private_key(SHA256(nonce))
        cert=load_keys(entity)
        sender_pub_key = cert.get_pubkey()
        sender_pub_key = crypto.dump_publickey(crypto.FILETYPE_PEM, sender_pub_key)
        sender_pub_key = load_pem_public_key(sender_pub_key)
        try:
            '''
            Error in this block means signatures were'nt verified successfully, in that case jumpt to exception
            '''

            signature = bytes.fromhex(response["signature"])
            sender_pub_key.verify(signature,  
                                   sha256(decrypted_message).digest(),  
                                   padding.PSS(mgf=padding.MGF1(hashes.SHA256()),
                                    salt_length=padding.PSS.MAX_LENGTH),
                                    hashes.SHA256())
            print(f"[+] Authentication completed for {entity}.")


            '''
            Operation on the received nonce and sending it
            '''
            with open(f"{entity}/{entity}_cert.pem", "rb") as f:
                cert = crypto.load_certificate(crypto.FILETYPE_PEM, f.read())
            receiver_pub_key = cert.get_pubkey()
            receiver_pub_key = crypto.dump_publickey(crypto.FILETYPE_PEM, receiver_pub_key)
            receiver_pub_key = serialization.load_pem_public_key(receiver_pub_key, backend=default_backend())
            encrypted_opr_nonce = receiver_pub_key.encrypt(str(int(decrypted_message.decode())+23).encode(),                            #Encrypting plain-text nonce with receiver's public key
                                        padding.OAEP(
                                        mgf=padding.MGF1(algorithm=hashes.SHA512()),
                                        algorithm=hashes.SHA512(),
                                        label=None)
                                    )
            with open("S/S_private.pem", "rb") as f:
                sender_priv_key = load_pem_private_key(f.read(),password=None)
            signature_opr_nonce = sender_priv_key.sign(sha256(str(int(decrypted_message.decode())+23).encode('utf-8')).digest() ,       #Digital signature for nonce
                                                        padding.PSS(mgf=padding.MGF1(hashes.SHA256()),
                                                        salt_length=padding.PSS.MAX_LENGTH),
						                        hashes.SHA256())
            #Perform operation on nonce when signatures are matched successfully

            print('[+] Sending encrypted nonce with operation')
            server.send(json.dumps({'nonce':encrypted_opr_nonce.hex(),'signature':signature_opr_nonce.hex()}).encode()+b"<END>")
            '''
            Operation on the received nonce completed, encrypted with client's public key, 
            signed with server's private key using SHA256 algorithm and sent to client
            '''
            #SEG3S
            msg=server.recv(1024).decode()
            if msg != 'Ack':
                print('[-] Invalid operation on nonce detected')
                exit()
            

            print('[+] Nonce verified successfully')

            #Create dictionary of certificates of other entities and JSONify it to share with successfully authenticated entity for future communications
            #with other entities
            certs = {}
            for e in ['A', 'B', 'C']:
                if entity !=e:
                     with open(f'S/{e}_cert.pem', 'rb') as file:
                              certs[e] = file.read().hex()
            data=json.dumps(certs).encode()
            server.send(data+b"<END>")
            active_sessions.append(entity)          # Client ID is added to the list
            connections[entity] = [server,addr]     # Socket connection object is stored in dictionary {<clientID> : <respective client socket object>}

            time.sleep(1)
            server.send("ROOM_INITIATED".encode())  # When received on client side then client expects all members (TOTAL_CLIENTS) to join the room
            
            #SEG4S
            try:
                while True:
                    participants=[]
                    if len(active_sessions) == TOTAL_CLIENTS:
                        # Once all the members join the room, server sends a JSON string to all clients to make aware about other clients in the room

                        for user in active_sessions:
                            if user != entity:
                                participants.append(user)
                        
                        server.send(json.dumps({"Session": "START", "TotalClients":TOTAL_CLIENTS-1,"Participants": ','.join(participants)}).encode())
                        
                        print('[+] Recieving key from',entity)
                        receiveKeys(server,entity)
                        if len(stack)==TOTAL_CLIENTS:
                            keys=stack
                            stack=None
                            sortNSendKeys(keys)
                            fwdMsg()
                            # fwdMsg(server)
                            break
            except Exception as e:
                print(e)          
        except Exception as e:
              '''
              Entity's signatures didn't match, therefore the authentication is failed and connection is closed
              '''

              print(f"[-] Invalid authentication for {entity}",e)
              server.send("AUTH_FAIL".encode())
              server.close()
            

if __name__ == "__main__":
    if (not os.path.exists("A")) or (not os.path.exists("B")) or (not os.path.exists("C")) or (not os.path.exists("S")):
        generate_keys()
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind(("127.0.0.1", 9999))
    server.listen(5)
    print("[*] Chat Server Started...")
    
    while True:
        client, addr = server.accept()
        threading.Thread(target=handle_client, args=(client, addr)).start()


'''
Overview of code:

#SEG1S
Get client ID and ask for authentiacation from client in return along with sharing
public certificate of server S

#SEG2S
Get the signed and encrypted nonce from client. Decrypt it and verify the signature
of the received nonce. Apply operation +23 on nonce, encrypt it with client's public key
and sign the SHA256(operated nonce) with server's private key and send it

#SEG3S
Receive 'Ack' from client if challenge response is verified successfully. Then the certificates
of other clients are  sent to this newly authenticted client. The newly connected
client ID is also added to active_sessions list and socket connection object is stored in a
dictionary value with client's ID as its key

#SEG4S
Unless the length of activ_sessions list equals 3, the server is in infinite loop, waiting
for other clients to join. Once it is equal to 3 then each client is made aware about other
client IDs. Example: A is made aware about B and C have joined the room

#SEG5S (receiveKeys())
Receive the symmetric key part from all the clients encrypted with respective recipient's
public key and a digital signature using SHA256 hash encrypted with private key of sender. 
Store all the combinations in a stack

#SEG6S (sortNSendKeys())
Get the keys from stack, sort according to receiver along with signature and send it to receiver
along with signature so that receiver could verify them correctly

#SEG7S (fwdMsg())
Loads the socket object from the connections dictionary for each entity and creates a thread using 
forward_client_messages() which listens the encrypted messages from respective loaded entity thread
and forwards to other clients by loading their respective socket object from connections dictionary
'''