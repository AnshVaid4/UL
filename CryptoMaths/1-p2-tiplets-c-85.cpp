
#include <iostream>
using namespace std;

int main()
{
    long int count=0,a,b;
    cout<<"Possible triplets for c=85, where c=u^2+v^2:"<<endl;
    
    for(long int i=0L;i<=85*85;i++)
    {
        for(long int j=0L;j<=i;j++)
        {
            if(i*i+j*j==85 && count<=3)
            {
                if(count>3) exit(0);
                count+=1;
                
                a=(i*i)-(j*j);
                b=2*i*j;
                cout<<i<<","<<j<<endl;
                cout<<"a=u^2-v^2 => "<<a<<endl;
                cout<<"b=2uv => "<<b<<endl;
                cout<<"Triplet: "<<a<<","<<b<<","<<85<<endl;
                cout<<a*a+b*b<<"="<<85*85<<endl<<endl;
            }
        }
    }

    return 0;
}