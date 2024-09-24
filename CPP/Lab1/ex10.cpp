#include<iostream>
using namespace std;

int main()
{
	int a,b;
	char c;
	while(true)
	{
		cout<<"**** MENU ****"<<endl;
		cout<<"+) Addition"<<endl;
		cout<<"-) Subtraction"<<endl;
		cout<<"*) Multiplication"<<endl;
		cout<<"/) Division"<<endl;
		cout<<"x) Exit"<<endl;
		cout<<"**************"<<endl;
	
		cout<<"\nChoose a number from the menu: ";cin>>c;
		
		switch(c)
		{
			case '+': cout<<"Enter 2 numbers: ";cin>>a>>b;
					cout<<"\nAnswer: "<<a+b<<endl<<endl<<endl;
					break;
			
			case '-': cout<<"Enter 2 numbers: ";cin>>a>>b;
					cout<<"\nAnswer: "<<a-b<<endl<<endl<<endl;
					break;
					
			case '*': cout<<"Enter 2 numbers: ";cin>>a>>b;
					cout<<"\nAnswer: "<<a*b<<endl<<endl<<endl;
					break;
					
			case '/': cout<<"Enter 2 numbers: ";cin>>a>>b;
					cout<<"\nAnswer: "<<a/b<<endl<<endl<<endl;
					break;
					
			case 'x': exit(0);
					
			default: cout<<"\nInvalid input, try again!"<<endl<<endl<<endl;
		}
	}
	
}
