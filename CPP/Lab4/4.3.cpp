#include<iostream>
#include<cstdlib>
using namespace std;

void countPosNegZero(int array[], int numElements,int& positive, int& negative, int& zero)
{
	for (int i = 0; i < numElements; i++)
	{
		if (array[i] > 0)
			positive++;
		else if (array[i] == 0)
			zero++;
		else
			negative++;
	}
}

int main()
{
	const int m = 10;

	int x[m];
	for (int i = 0; i < m; i++)
	{
		x[i]=(rand()/(1000))-10;
	}

	int p = 0,n=0,z=0;
	countPosNegZero(x, 10, p, n, z);

	for (int i = 0; i < m; i++)
	{
		cout << x[i] << " ";
	}

	cout << endl << "Positive: " << p << ", Negative: " << n << ", Zero: " << z;
}