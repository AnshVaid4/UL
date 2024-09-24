#include<iostream>
using namespace std;

int main()
{
	double r;
	const double pi{3.1415};
	cout<<"Enter radius of circle: "; cin>>r;
	cout<<"\nDiameter: "<<2*r;
	cout<<"\nCircumference: "<<2*pi*r;
	cout<<"\nArea: "<<pi*r*r;
	
	return 0;	
}
