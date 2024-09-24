#include<iostream>
using namespace std;

int main()
{
	int a,b,c;
	while(true)
	{
		cout<<"**** MENU ****"<<endl;
		cout<<"1. Addition"<<endl;
		cout<<"2. Subtraction"<<endl;
		cout<<"3. Multiplication"<<endl;
		cout<<"4. Division"<<endl;
		cout<<"5. Exit"<<endl;
		cout<<"**************"<<endl;
	
		cout<<"\nChoose a number from the menu: ";cin>>c;
		
		switch(c)
		{
			case 1: cout<<"Enter 2 numbers: ";cin>>a>>b;
					cout<<"\nAnswer: "<<a+b<<endl<<endl<<endl;
					break;
			
			case 2: cout<<"Enter 2 numbers: ";cin>>a>>b;
					cout<<"\nAnswer: "<<a-b<<endl<<endl<<endl;
					break;
					
			case 3: cout<<"Enter 2 numbers: ";cin>>a>>b;
					cout<<"\nAnswer: "<<a*b<<endl<<endl<<endl;
					break;
					
			case 4: cout<<"Enter 2 numbers: ";cin>>a>>b;
					cout<<"\nAnswer: "<<a/b<<endl<<endl<<endl;
					break;
					
			case 5: exit(0);
					
			default: cout<<"\nInvalid input, try again!"<<endl<<endl<<endl;
		}
	}
	
}
