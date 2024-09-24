/* P0 = 0, P1 = 1, P2 = 2and Pn+1 = 2Pn + Pn−1*/
/* a = (Pn+1)^2−(Pn)^2,   b = 2 Pn+1 Pn,   c = (Pn+1)^2 + (Pn)^2
*/

#include <iostream>
using namespace std;

int main()
{
    int x=0,y=1,val=0,count,a,b,c;
    cout<<"\nEnter the number of elements to be displayed: ";
    cin>>count;
    
    if(count>=1) cout<<x<<" ";
    if(count>=2) cout<<y<<" ";
    if(count>=3)
    {
        for(int i=2;i<count;i++)
        {
            val=(2*y)+x;
            cout<<val<<" ";
            x=y;
            y=val;
        }
        
        x=0;y=1;
    }
    
    cout<<endl<<endl;
   
    for(int i=0;i<count;i++)
    {
        val=(2*y)+x;
        
        a=(val*val) - (y*y);
        b=2*val*y;
        c=(val*val) + (y*y);
        
        x=y;
        y=val;
        
        cout<<"a:"<<a<<" b:"<<b<<" c:"<<c<<endl<<
        "(a^2 + b^2 = c^2): "<<a*a <<"+" << b*b<<"="<<c*c<<" => "<<a*a+b*b<<"="<<c*c<<endl<<
        "Difference between 'a' and 'b' |a-b|:"<<(a-b)*(a-b)<<endl<<endl;
    }
    
    return 0;
}