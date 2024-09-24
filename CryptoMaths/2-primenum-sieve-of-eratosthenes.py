a=int(input("Enter a number to check if it is prime or not: "))
table=[]

for i in range(2,a):
    table.append(i)

for i in table:
    for j in table:
        if j>i and j%i==0:
            table.remove(j)

print("Prime numbers are: ",table)