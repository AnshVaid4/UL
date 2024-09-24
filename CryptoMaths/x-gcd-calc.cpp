#include <iostream>
using namespace std;

int gcd(long long int divisor, long long int dividend)
{
    long long int q,r;
    
    q=dividend/divisor;
    r=dividend%divisor;
    cout<<"-> q:"<<q<<" r:"<<r<<" divisor:"<<divisor<<" dividend:"<<dividend<<endl;
    
    // if(r!=0)
    while(r!=0)
    {
        dividend=divisor;
        divisor=r;
        q=dividend/divisor;
        r=dividend%divisor;
        cout<<"=> q:"<<q<<" r:"<<r<<" divisor:"<<divisor<<" dividend:"<<dividend<<endl;
    }
    
    return divisor;
}

int main()
{
    long long int x,y,ans;
    cout<<"Enter two numbers whose GCD has to be found: ";
    cin>>x>>y;
    ans=(y<x)?gcd(y,x):gcd(x,y);
    cout<<endl<<ans;

    return 0;
}