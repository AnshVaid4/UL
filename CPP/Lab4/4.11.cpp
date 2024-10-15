#include<iostream>
#include<cstdlib>
using namespace std;


int main()
{
	const int m = 5;

	int x[m];
	for (int i = 0; i < m; i++)
	{
		x[i] = (rand() % 18) + 2;
	}

	for (int i = 0; i < m; i++)
	{
		cout << m-(m+i) << " ";
	}

}