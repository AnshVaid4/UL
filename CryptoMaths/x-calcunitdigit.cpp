#include <iostream>
#include<math.h>
using namespace std;

int calcunit(long long int x)
{
    long long int r;
    
    r=x%10;
    
    while(r/10!=0)
    {
        r=r%10;
    }
    
    return r;
}

int main()
{
    // cout<<<<lon>pow(7,8)+pow(8,7);
    long long int x=pow(7,8)+pow(8,7);
    cout<<calcunit(x);

    return 0;
}