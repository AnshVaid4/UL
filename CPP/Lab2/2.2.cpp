#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

int getRandomNumber(int min, int max)
{
	srand(time(0)*time(0));
	return (rand() % (max - min)) + min;
}

void printRandomNumber(int x[10])
{
	for (int i = 0; i < 10; i++)
		x[i] = getRandomNumber(i, 100);

}

int main()
{
	cout << getRandomNumber(20,30)<<endl;
	int a[10];

	printRandomNumber(a);

	for (int i = 0; i < 10; i++)
	{
		cout << a[i] << " ";
	}
}
