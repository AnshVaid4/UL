#include<iostream>
using namespace std;

int main()
{
	float i,count;
	cout<<"Enter integer: ";
	cin>>i;
	
	while(true)
	{
		if(i/2.0>100)
		{
			count++;
			i/=2.0;
		}
		else
		break;
	}
	
	cout<<"\n"<<count<<" number of times";
}
