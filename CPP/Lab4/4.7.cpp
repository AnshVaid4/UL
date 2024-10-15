#include<iostream>
#include<cstdlib>
using namespace std;


int main()
{
	const int m = 10;

	int x[m];
	for (int i = 0; i < m; i++)
	{
		x[i] = (rand() / (1000)) - 10;
	}


	for (int i = 0; i < m; i++)
	{
		cout << *(x+i) << " ";
	}

}