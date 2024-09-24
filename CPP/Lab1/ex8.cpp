#include<iostream>
using namespace std;

int main()
{
	int i;	
	do
	{
		cout<<"Enter a number: ";
		cin>>i;
		if(i>0)
		{
			i%2==0?cout<<"\nEven\n\n":cout<<"\nOdd\n\n";
		}
		else
		exit(0);		
		
	}while(i>0);
}
