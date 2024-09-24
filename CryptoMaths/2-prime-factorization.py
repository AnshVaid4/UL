def factorize(num):
    f=2
    done=[]                                             #list for adding all the completed factors and their possible powers
    print(num,": ",end="")
    while(f<=num):
        if(num%f==0 and f <= num and f not in done):
            print(f,end="*")
            num/=f
        else:
            i=1
            while True:
                if f**i <= num:
                    done.append(f**i)
                    i+=1
                else:
                    break
            f+=1
    print(1)

# num=int(input("Enter the number whose prime factorization needs to be done: "))
# factorize(num)

for i in range(2000,2015):
    factorize(i)