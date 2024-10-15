#include<iostream>
#include<cstdlib>
using namespace std;

void printArray(int* data, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << data[i] << " ";
	}
}

int main()
{
	const int m = 10;

	int x[m];
	for (int i = 0; i < m; i++)
	{
		x[i] = (rand() % 18) + 2;
	}


	printArray(x, m);


}