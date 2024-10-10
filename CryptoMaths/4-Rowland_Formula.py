#Rowland's Formula
import math 

an_1=7                          #First element is 7
elements=int(input("Enter the max elements to be displayed using Rowland's formula: "))
sequence=[an_1]

for n in range(2,elements):
    an=an_1+math.gcd(n,an_1)      #an=an-1+gcd(n,an-1)
    sequence.append(an)
    an_1=an

print(sequence)

primes=[]
for i in range(0,len(sequence)):    #deducing all primes from sequence
    if (i is not len(sequence)-1):# and (sequence[i+1]-sequence[i] not in primes):
        primes.append(sequence[i+1]-sequence[i])
        
print(primes)
