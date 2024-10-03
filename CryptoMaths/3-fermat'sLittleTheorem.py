#Fermat's Little theorem: For a**k mod P, if P is prime and k in P-1 then the series of 1s is displayed
l1=list()

for a in range(0,11):
    l2=list()
    for k in range(1,13):
        l2.append((a**k)%11)
    l1.append(l2)
    
for i in l1:
    for j in i:
        print(j,end='\t')
    print()