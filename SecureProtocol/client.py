import socket
import json
import numpy as np
from OpenSSL import crypto
from cryptography.hazmat.primitives.asymmetric import padding
from cryptography.hazmat.primitives import hashes, serialization
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives.serialization import load_pem_private_key, load_pem_public_key
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.primitives import padding as symmetricpadding
from cryptography.hazmat.backends import default_backend
from hashlib import sha256
import time
import threading




sessionKeys=[]              #session key between the entities

def digitalSign(data):
    '''
    This function is used to create digital signature of the data passed in the parameter with entity's private key
    The entity name can't be forged since the session entity's name is used as variable
    '''

    with open(f"{entity}/{entity}_private.pem", "rb") as f:
        sender_priv_key = load_pem_private_key(f.read(),password=None)
    sender_signature = sender_priv_key.sign(data,                                           #Digital signature for nonce
                                                padding.PSS(mgf=padding.MGF1(hashes.SHA256()),
                                                salt_length=padding.PSS.MAX_LENGTH),
						                        hashes.SHA256())
    return sender_signature




def getPrivateKey(entity):
    '''
    Function to get the private key of the client
    '''

    with open(f"{entity}/{entity}_private.pem", "rb") as f:
                    #Loading entity's private key to decrypt the message
                    receiver_priv_key = load_pem_private_key(f.read(),password=None)
    return receiver_priv_key




def publicKeyEncrypt(entity,targetentity, data):
    '''
    This function is used to encrypt the data passed in the parameter with the public key of targetentity so that the data
    can't be read during transmission
    '''

    with open(f"{entity}/{targetentity}_cert.pem", "rb") as f:
        cert = crypto.load_certificate(crypto.FILETYPE_PEM, f.read())
    receiver_pub_key = cert.get_pubkey()
    receiver_pub_key = crypto.dump_publickey(crypto.FILETYPE_PEM, receiver_pub_key)
    receiver_pub_key = serialization.load_pem_public_key(receiver_pub_key, backend=default_backend())
    encrypted_data = receiver_pub_key.encrypt(data.encode(),                            #Encrypting plain-text nonce with receiver's public key
    							padding.OAEP(
        						mgf=padding.MGF1(algorithm=hashes.SHA512()),
        						algorithm=hashes.SHA512(),
        						label=None)
							)
    return encrypted_data



def signatureVerify(sender,signature, data):
    '''
    This function is used to verify the signatures with the respective sender parameter and signature parameter
    passed for the data parameter
    '''

    with open(f'{entity}/{sender}_cert.pem', 'rb') as cert_file:                            # Retrieving public key of sender
                    cert = crypto.load_certificate(crypto.FILETYPE_PEM, cert_file.read())
    sender_pub_key = cert.get_pubkey()
    sender_pub_key = crypto.dump_publickey(crypto.FILETYPE_PEM, sender_pub_key)
    sender_pub_key = load_pem_public_key(sender_pub_key)

    try:
        # Verifying the signatures
        sender_pub_key.verify(signature,  
                                data,  
                                padding.PSS(mgf=padding.MGF1(hashes.SHA256()),
                                salt_length=padding.PSS.MAX_LENGTH),
                                hashes.SHA256())
        return True
    except Exception as e:
        print(e)
        return False




def receiveKeys(client, entity, totalClients):
    '''
    Function to receives encrypted nonce along with signature of sender. If there are 3 participants
    then each participant will receive 2 (totalClients parameter) nonce. That has to be verified.
    Once verififed it is added to sessionKeys global variable, and then sorted and concatenated. Then
    this string's SHA256 hash is created, which is the session key for entities
    '''

    #SEG7C
    global sessionKeys  # session key is generated ad stored in this variable
    try:
        '''
        Error handling for safety
        '''

        for _ in range(totalClients):
            '''
            This loop will run the TOTAL_CLIENTS-1 times to receive the nonce from other participants.
            Recieve JSON data from sortKeys() of server
            '''

            data = ""                                           #JSON key received in chunks from server
            try:
                while True:
                    
                    #Get the key in chunks from #SEG6S
                    chunk = client.recv(2048).decode()          # Decode bytes to string
                    if "<END>" in chunk:                        # Check for termination marker
                        data += chunk.replace("<END>", "")      # Remove marker and stop receiving
                        break
                    else:
                        data += chunk
                
                data = json.loads(data.strip())                 # Parse JSON from the recived data from server
                print("[+] Receiving key", data)
              
            except Exception as e:
                if "}{" in data:
                    # Error handling for few cases in which multiple JSON strings are sent
                    data=data.split('}{')
                    data='{'+data[1]
                    data = json.loads(data.strip())             # Retrieving the key string from the exception
                    print('[+] Receiving key', data)
                else:
                    print(f"Error in receiving: {e}")

            # Retrieving contents from JSON key string from other client
            sender=data.get('sender')
            nonce=data.get('nonce')
            signature=bytes.fromhex(data.get('signature'))

            if entity == data.get('receiver'):                  
                # If the entity and receiver IDs are same
                
                # Get private key of receiver to decrypt the Nonce encrypted with entity's public key by sender
                receiver_priv_key=getPrivateKey(entity) 
                
                # Decrypt the encrypted nonce     
                decrypted_nonce = receiver_priv_key.decrypt(bytes.fromhex(nonce),
                            padding.OAEP(mgf=padding.MGF1(algorithm=hashes.SHA512()),
                                        algorithm=hashes.SHA512(),label=None))
                
                # Verify the nonce by checking the signature received in JSON key string from server
                if signatureVerify(sender,signature,sha256(decrypted_nonce).digest()):
                     # If signature is verified for the sender
                     sessionKeys.append(decrypted_nonce.decode())
                     print(f"[+] Received a verified nonce from {sender}\n")
                else:
                     print(f"[-] Received an invalid nonce from {sender}\n")
                     return False
        
        sessionKeys.sort()
        sessionKey=sha256(''.join(sessionKeys).encode('utf-8')).hexdigest()
        print(f'\n[+] Concatenated key is f{''.join(sessionKeys)} and session key is {sessionKey}')

    except Exception as e:
        print(f"Receiver thread error: {e}")

    return sessionKey




def aes_cbc_encrypt(iv, plaintext, key):
    '''
    Encrypt data using AES-CBC with PKCS7 padding
    '''
    # print(key,'\n',iv)
    cipher = Cipher(algorithms.AES(key), modes.CBC(iv), backend=default_backend())
    encryptor = cipher.encryptor()

    # Apply PKCS7 Padding (since AES block size is 16 bytes)
    padder = symmetricpadding.PKCS7(128).padder()
    padded_plaintext = padder.update(plaintext.encode()) + padder.finalize()

    ciphertext = encryptor.update(padded_plaintext) + encryptor.finalize()
    return ciphertext

def aes_cbc_decrypt(ciphertext, key, iv):
    '''
    Decrypt data using AES-CBC with PKCS7 unpadding
    '''
    cipher = Cipher(algorithms.AES(key), modes.CBC(iv), backend=default_backend())
    decryptor = cipher.decryptor()

    decrypted_padded = decryptor.update(ciphertext) + decryptor.finalize()

    # Remove padding
    unpadder = symmetricpadding.PKCS7(128).unpadder()
    decrypted_text = unpadder.update(decrypted_padded) + unpadder.finalize()
    
    return decrypted_text.decode()



def send_data(client, entity, sharedKey, totalClients, iv,participants):
    '''
    Send messages to the other clients via the server which forwards the messages
    '''
    print('\n\n*****************  START CHATTING  *****************\n\n')
    while True:
        try:
            message = input('<< ')
            client.send(json.dumps({'sender':entity,'msg':aes_cbc_encrypt(iv,message,sharedKey).hex()}).encode())
        except Exception as e:
            print(f"[-] Error sending data: {e}")
            break  # Exit loop if sending fails




def receive_data(client, sharedKey, totalClients, iv, participants):
    '''
    Continuously receive the forwarded messages or any other messages from the server
    '''

    while True:
        try:
            data = json.loads(client.recv(4096).decode())
            if data:
                print(f"{data.get('sender')} >> {aes_cbc_decrypt(bytes.fromhex(data.get('msg')),sharedKey,iv)}")

        except Exception as e:
            print(f"[-] Error receiving data: {e}")
            break  # Exit loop if receiving fails




def startChat(client, entity, totalClients,sharedKey, participants):
    '''
    Main chat area responsible for -
    Starting both sender and receiver in separate threads for chatting
    '''

    #SEG8C
    iv=bytes.fromhex(sha256(sharedKey).hexdigest()[:32])
    print(f'[+] IV: {sha256(sharedKey).hexdigest()[:32]} as {iv} in bytes')

    receive_thread = threading.Thread(target=receive_data, args=(client, sharedKey, totalClients, iv, participants), daemon=True)
    send_thread = threading.Thread(target=send_data, args=(client, entity, sharedKey, totalClients, iv,participants), daemon=True)

    send_thread.start()
    receive_thread.start()

    send_thread.join()
    receive_thread.join()




def sharedKeyGen(client,entity,totalClients,participants):
    '''
    After each client has connected to the server, the server sends the START message to all
    the clients, then these clients generate a random number which is a part of the shared key 
    generation. The nonce is signed hashed with SHA256 algorithm to create digital signatures.
    The hash is encrypted with the public key of the receiver. Then in a JSON format 
    
    {<recipientID1> : <public key1 encrypted nonce>, <recipientID2> : <public key2 encrypted nonce>, signature : <signature>}

    is sent to the server. The server receives the JSON data, organizes it according to sender, receiver, encrypted message 
    and signature to be sent respective recipient and sends them.
    '''

    #SEG6C
    global sessionKeys
    sharedKeyNonce = str(np.random.randint(111111,999999))
    sessionKeys.append(sharedKeyNonce)
    sharedKeyNonce_hash=sha256(sharedKeyNonce.encode('utf-8')).digest()                                   #SHA256 for integrity checks
    sharedKeyNonce_signature = {"signature": digitalSign(sharedKeyNonce_hash).hex()}                      #Encrypt hash of plaintext nonce with entity's private key
    encryptedKeys={}
    for user in participants:
        encrypted_sender_sharedKeyNonce = publicKeyEncrypt(entity, user, sharedKeyNonce)                          #Encrypt plain text nonce with receiver client's public key
        encryptedKeys[user] = encrypted_sender_sharedKeyNonce.hex()
    
    message = encryptedKeys | sharedKeyNonce_signature                                                    #Combining two dictionaries and using as a single JSON

    auth_data = json.dumps(message)
    print(f'[+] Entity generated a part of shared key: {sharedKeyNonce}')
    print(f'[+] Sending encrypted and signed key part to {participants}\n')
    client.send(auth_data.encode())

    sharedKey=receiveKeys(client,entity,totalClients)  
    return sharedKey  




def auth_request(client):
    '''
    1. Function is triggered if server requests the client to authenticate itself upon initial connection
    2. Client loads its private key and generates a random nonce and creates its hash.
    3. The hash of the nonce is digitally signed using the private key of client.
    4. The plain text nonce is then encrypted using the public key of the server so that only the server can decrypt it.
    5. If server decrypts the nonce successfully then it creates the SHA256 hash of that plain text nonce and verifies the
       hash by decrypting the encrypted signature using public key of sender
    6. If the process is done successfully, therefore, the client is authenticated, but now in response the server has to
       perform an operation on nonce by adding 23 in the nonce and send the response. 
    7. Server sends: {'nonce':encrypted_opr_nonce.hex(),'signature':signature_opr_nonce.hex(),'cert':S_cert}"<END>" to client with operated
       nonce encrypted in 'nonce' JSON attribute, its digital signature with SHA256 algorithm and public key certificate of server for 
       decryption of nonce attribute and verification of signature
    8. If client is able to decrypt the nonce and equate with the operation, as well as verifies its signature, the client authenticates the
       server successfully
    ''' 
    
    #SEG2C
    #Generation of nonce, hashing it with SHA256 algorithm, 
    sender_nonce = str(np.random.randint(111111,999999))
    nonce_hash=sha256(sender_nonce.encode('utf-8')).digest()                                            #SHA256 for integrity checks
    
    sender_nonce_signature = digitalSign(nonce_hash)                                                    #Encrypt hash of plaintext nonce with entity's private key
    encrypted_sender_nonce = publicKeyEncrypt(entity,'S', sender_nonce)                                        #Encrypt plain text nonce with S's public key
    
    #JSONify the nonce data and send to the server for authentication
    auth_data = json.dumps({"auth": True, "message": encrypted_sender_nonce.hex(), "signature": sender_nonce_signature.hex()}) 
    print("[+] Sending encrypted and signed nonce to S") 
    client.send(auth_data.encode())

    #Get the response of authentication from the server with some operation performed on nonce
    '''
    Authentication of server
    '''
    #SEG3C
    opr_nonce=b''
    while True:
        chunk= client.recv(4096)
        if b"<END>" in chunk:
            opr_nonce += chunk.replace(b"<END>",b"")
            break
        else:
            opr_nonce += chunk
    auth_response=json.loads(opr_nonce.strip().decode())
    with open(f"{entity}/{entity}_private.pem", "rb") as f:
             #Loading client's private key to decrypt the operated nonce from server
             receiver_priv_key = load_pem_private_key(f.read(),password=None)
             decrypted_opr_nonce= receiver_priv_key.decrypt(bytes.fromhex(auth_response.get('nonce')),
                            padding.OAEP(mgf=padding.MGF1(algorithm=hashes.SHA512()),
                                        algorithm=hashes.SHA512(),label=None))
    '''
    Data for authenticating the server is received and stores, verifying the signature in nex step
    '''
    
    if (int(decrypted_opr_nonce.decode()) == int(sender_nonce)+23) and signatureVerify('S',bytes.fromhex(auth_response.get('signature')), sha256(str(int(decrypted_opr_nonce.decode())).encode('utf-8')).digest()):
        '''
        If the operations are successfully performed on the nonce by the server, 
        and signature of operated nonce from server is also verified successfully, then both 
        parties, client and server have authenticate themselves through this technique given
        the fact that keys of Servert are NOT compromised. If authenticated, therefore, the
        client is ready to fetch the certificates of other entities from the server S.
        '''

        print(f"[+] S authenticated successfully through challenge response")
        print(f"[+] Both S and {entity} authenticated successfully")
        client.send('Ack'.encode()) #to SEG3S
        print(f"[+] Receiving certificates of other entities from server")

        #SEG4C
        #Receiving the certificates of other 2 entities
        data=b''
        try:
            '''
            If there is any error, i.e. if client doesn't receive anything 
            then the client believes the certificates have been transferred to it unsuccessfully
            '''
            #from SEG3S
            while True:
                chunk=client.recv(2048)
                if b"<END>" in chunk:
                    data += chunk.replace(b"<END>",b"")
                    break
                else:
                    data += chunk
            certs=json.loads(data.strip().decode())
            for key, value in certs.items():
                with open(f'{entity}/{key}_cert.pem', 'wb') as cert_file:
                    cert_file.write(bytes.fromhex(value))
            print(f"[+] Received certificates from server")
            pass
        except Exception as e:
                '''
                Any error in this block means that client didn't receive the certificates from the client successfully
                '''

                print(f"[-] Unable to receive certificates from the server")
            
    else:
        print("[-] Authentication failed.")
        client.close()
    



def authenticate(entity):
    '''
    The socket connection request is sent to server by sending 'entity name' to the server,
    in resonse the server asks the client for authentication by sending 'AUTH_REQUEST' parameter to client.
    '''

    #Establishing connection with server
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect(("127.0.0.1", 9999))

    #SEG1C
    client.send(entity.encode())        #sending client ID
    response=b''
    while True:
        chunk= client.recv(4096)
        if b"<END>" in chunk:
            response += chunk.replace(b"<END>",b"")
            break
        else:
            response += chunk
    response = json.loads(response)
    print('[+] Recieved Server\'s certificate successfully')
    with open(f'{entity}/S_cert.pem', 'wb') as cert_file:
         # Store the server's certificate to a file for signature verification in next step
         cert_file.write(bytes.fromhex(response.get('cert')))

    #If connection is established then server requests the client for authentication
    if response.get('auth') == "AUTH_REQUEST":
        auth_request(client)

    #SEG5C
    print("[+] Waiting for keys")
    response = client.recv(1024).decode()
    if response == "ROOM_INITIATED":
        response = json.loads(client.recv(1024).decode())   #From SEG4S
        if response.get("Session") == "START":
            print('\n[+]', entity,"connected with ", response.get("TotalClients"),"clients =>", response.get("Participants").split(','))
            sharedKey=sharedKeyGen(client,entity,response.get("TotalClients"),response.get("Participants").split(','))
            print(f'[+] Session Key: {sharedKey} as {bytes.fromhex(sharedKey)} in bytes')
            startChat(client,entity,response.get("TotalClients"),bytes.fromhex(sharedKey), response.get("Participants").split(','))   # Main chat environment after authentication and key generation
            


#Initial execution of the program
if __name__ == "__main__":
    entity = input("Enter entity name (A, B, or C): ")
    try:
        authenticate(entity)
    except Exception as e:
    	print("[-] Service is temporarily unavailable. Try again later!\n",e)



'''
Overview of code:

#SEG1C
Receive authentication request from server along with public certificate of server S

#SEG2C
Generate random nonce Na encrypted with public key os S, signing SHA256(Na) with
entity's private key and sending both to server

#SEG3C
Receive the encrypted response of nonce, decrypt and verify the signature and operation.
If bot matches correctly then the authentication is completed for both parties and 'Ack' is
sent to server

#SEG4C
Receiveing other clients' certificates

#SEG5C
Client waits in the room for other clients to join. Once all the 3 clients join the room then
they receive other clients' id which have joined the room

#SEG6C (sharedKeyGen())
Create a nonce which is a part of shared  symmetric key generation. Encrypt this with public key
of other 2 recipients and sign it using SHA256 hash encrypted using private key of sender entity.

#SEG7C (receiveKeys())
Get the sorted keys from the server which contains sender id, receiver id, encrypted nonce with
receiver's public key and signature of sender for that nonce. This is decrypted and verified by the
receiver and stores it in ascending order. The SHA256 hash of this concatinated sorted chunks from all
the clients is the actual MUTUALLY AGREED SESSION KEY

#SEG8C (startChat())
Starts the chat portal by creating each client's 2 threads, receive_data() and send_data(); these two
threads are in infinite while loop. receive_data() gets the forwarded message from server which indeed
sent to it by a sender. It also decrypts the message using AES algorithm and session key. send_data()
sends encrypted message to server encrypting using AES algorithm using session key
'''