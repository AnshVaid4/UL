#include<iostream>
#include<cmath>
#include<vector>
using namespace std;

bool isPrime(int a)
{
	bool result = true;
	for (int i = 2; i <= sqrt(a); i++)
	{
		//cout << a<<" " << i <<" " << a % i << endl;
		if (a % i == 0)
		{
			result=false;
			break;
		}
	}
	return result;
}

vector<int>* getRange(int min, int max)
{
	vector<int> *a=new vector<int> ();
	int counter = 0;

	for (int i = min+1; i < max; i++)
	{
		if (isPrime(i))
		{
			a->insert(a->begin() + counter, 1, i);
			counter++;
		}
		else continue;
	}
	return a;
}

int main()
{
	int a,min,max;
	vector<int> *x;
	cout << "Enter an integer to test if it's prime or not: ";
	cin >> a;
	isPrime(a) ? cout<<"\nNumber is prime!!" : cout<<"\nX Number is not prime X";

	cout << "\n\nEnter minimum and maximum value between which the prime numbers have to be checked: ";
	cin >> min >> max;

	x = getRange(min, max);
	cout << endl << "Prime numbers between " << min << " and " << max << " are"<<endl;

	for (int i = 0; i < x->size(); i++)
		cout << x->at(i) << " ";

}