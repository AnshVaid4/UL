#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int n,i2,j2,k2,l2;
    cout<<"Enter a number: ";
    cin>>n;
    
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<i; j++)
        {
            for(int k=0; k<j; k++)
            {
                for(int l=0; l<k; l++)
                {
                    if(n-(pow(i,2)+pow(j,2)+pow(k,2)+pow(l,2)) == 0)
                    {
                        cout<<"Numbers are: "<<i<<", "<<j<<", "<<k<<", "<<l<<"\n";
                        cout<<"Sum of "<<pow(i,2)<<"+"<<pow(j,2)<<"+"<<pow(k,2)<<"+"<<pow(l,2)<<"="<<n<<"\n\n";
                        exit(0);
                    }
                }
            }
        }
    }

    return 0;
}