#include<iostream>
using namespace std;

bool recip(double& a)
{
	if (a)
		return true;
	else
		return false;
}

int main()
{
	double x;

	do
	{
		cout << "\n value: ";
		cin >> x;
		recip(x)?cout<<"\nTrue":cout<<"\nFalse";
		/*cout << endl << x;*/
	} while (x || !x);
}