#include<iostream>
using namespace std;

int main()
{
	int x;
	cout<<"Enter your percentage: ";
	cin>>x;
	
	if(x>=0)
	{
		if(x>=85)
		{
			cout<<"\nA1";
		}
		else if(x>=80)
		{
			cout<<"\nA2";
		}
		else if(x>=75)
		{
			cout<<"\nB1";
		}
		else if(x>=70)
		{
			cout<<"\nB2";
		}
		else if(x>=65)
		{
			cout<<"\nB3";
		}
		else if(x>=60)
		{
			cout<<"\nC1";
		}
		else if(x>=55)
		{
			cout<<"\nC2";
		}
		else if(x>=45)
		{
			cout<<"\nC3";
		}
		else if(x>=35)
		{
			cout<<"\nD1";
		}
		else if(x>=25)
		{
			cout<<"\nD2";
		}
		else
		{
			cout<<"\nF";
		}
	}
	else
	{
		cout<<"Enter a valid number";
	}
}
