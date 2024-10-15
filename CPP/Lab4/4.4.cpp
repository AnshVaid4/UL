#include<iostream>
using namespace std;

void recip(double* a)
{
	*a = 1 / *a;
}

int main()
{
	double x;

	do
	{
		cout << "\n value: ";
		cin >> x;
		recip(&x);
		cout << endl << x;
	} while (x);
}