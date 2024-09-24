#include<iostream>
using namespace std;

int main()
{
	int a,b,r;
	cout<<"Enter two numbers: ";
	cin>>a>>b;
	
	r=a & b;
	cout<<endl<<"Bitwise AND:\t"<<hex<<"0x"<<a<<" & "<<hex<<"0x"<<b<<"="<<hex <<"0x"<<r;

	r=a | b;
	cout<<endl<<"Bitwise OR:\t"<<hex<<"0x"<<a<<" | "<<hex<<"0x"<<b<<"="<<hex <<"0x"<<r;
	
	r=a ^ b;
	cout<<endl<<"Bitwise XOR:\t"<<hex<<"0x"<<a<<" ^ "<<hex<<"0x"<<b<<"="<<hex <<"0x"<<r;
	
	r=~(a & b);
	cout<<endl<<"Bitwise NAND:\t"<<hex<<"0x"<<a<<" D0 "<<hex<<"0x"<<b<<"="<<hex <<"0x"<<r;

	r=~(a | b);
	cout<<endl<<"Bitwise NOR:\t"<<hex<<"0x"<<a<<" >0 "<<hex<<"0x"<<b<<"=" << hex <<"0x"<<r;

	r=a << b;
	cout<<endl<<"Bitwise shift left:\t"<<hex<<"0x"<<a<<" << "<<hex<<"0x"<<b<<"=" << hex <<"0x"<<r;
	
	r=a >> b;
	cout<<endl<<"Bitwise shift right:\t"<<hex<<"0x"<<a<<" >> "<<hex<<"0x"<<b<<"=" << hex <<"0x"<<r;
	

}
