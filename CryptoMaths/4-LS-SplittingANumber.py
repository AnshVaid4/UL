'''Write a sage function that takes two positive integers L, S as input.
It should return the list of integers a0, a1, . . . , ak that is obtained by breaking up S
into blocks of length L (starting at the right end).
For example, if L = 3 and S = 1234567890 the function should return the list with
elements a0 = 1, a1 = 234, a2 = 567, a3 = 890 '''

L=int(input("Enter the number in which parts it needs to be divided: "))
S=int(input("Enter the number which has to be splitted: "))

S=str(S)
splits=[]

while(len(S)>L):
    splits.append(S[-1:(L*-1)-1:-1][::-1])
    S=S.replace(S[-1:(L*-1)-1:-1][::-1],'')
   
if(len(S)%L!=0):
    splits.append(S)

counter=0
for i in splits[::-1]:
    print("a",counter,"=",i,end=', ',sep='')
    counter+=1


#For SAGE MATHS

L=3
S=1234567890

S=str(S)
splits=[]

while(len(S)>L):
    splits.append(S[-1:(L*-1)-1:-1][::-1])
    S=S.replace(S[-1:(L*-1)-1:-1][::-1],'')
   
if(len(S)%L!=0):
    splits.append(S)

counter=0
for i in splits[::-1]:
    print("a",counter,"=",i,end=', ',sep='')
    counter+=1
