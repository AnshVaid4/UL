
#include <iostream>
using namespace std;

int main()
{
    int a=0,b=1,sum=0,n;
    
    cout<<"\nEnter the number of elements to be displayed in fibonacci series: ";
    cin>>n;
    
    if(n>=1) cout<<a<<" ";
    if(n>=2) cout<<b<<" ";
    if(n>=3)
    {
        for(int i=0;i<n;i++)
        {
            sum=a+b;
            cout<<sum<<" ";
            a=b;
            b=sum;
        }
    }

    return 0;
}