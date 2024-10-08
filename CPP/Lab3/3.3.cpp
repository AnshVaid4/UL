#include<iostream>
#include<cstdlib>
#include<ctime>
#include<conio.h>
#include <windows.h>

using namespace std;

int minValue(int field[], unsigned int size)
{
	int min=field[0];
	for (int i = 0; i < size; i++)
	{
		if (field[i] < min)
			min = field[i];
	}

	return min;
}

int maxValue(int field[], unsigned int size)
{
	int max = field[0];
	
	for (int i = 0; i < size; i++)
	{
		if (field[i] > max)
			max = field[i];
	}

	return max;
}

double averageValue(int field[], unsigned int size)
{
	double sum=0;

	for (int i = 0; i < size; i++)
	{
		sum+=field[i];
	}

	return sum/size;
}

int main()
{
	int a[20];
	cout << "Initializing your array!\n";
	for (int i = 0; i < 20; i++)
	{
		srand(time(0)*time(0));
		a[i] = rand() % 99;
		Sleep(500);
	}

	for (int i = 0; i < 20; i++)
	{
		cout << a[i]<<" ";
	}

	cout << "\nMin value: " << minValue(a, 20);
	cout << "\nMax value: " << maxValue(a,20);
	cout << "\nAvg value: " << averageValue(a, 20);

}