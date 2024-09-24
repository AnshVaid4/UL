#include<iostream>
using namespace std;

int main()
{
	float min,max,step;
	cout<<"Enter minimum range, maximum range and step: ";
	cin>>min>>max>>step;
	cout<<"Fahrenheit\tCelsius\n";
	for(float i=min; i<=max; i+=step)
	{
		cout<<i<<"\t"<<(5.0/9.0)*(i-32.0)<<endl;
	}
}
