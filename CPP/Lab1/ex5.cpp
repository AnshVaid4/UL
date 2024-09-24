#include<iostream>
using namespace std;

int main()
{
	cout<<"Fahrenheit\tCelsius\n";
	for(float i=0; i<=300; i+=20)
	{
		cout<<i<<"\t"<<(5.0/9.0)*(i-32.0)<<endl;
	}
}
