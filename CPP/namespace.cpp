#include<iostream>
using namespace std;

namespace alpha
{
	void calc(int x, int y)
	{
		cout << "Alpha: " << x + y;
	}
}

namespace beta
{
	void calc(int x, int y)
	{
		cout << "Beta: " << x - y;
	}
}

using namespace alpha;
using namespace beta;

int main()
{
	int a{ 10 }, b{ 20 };
	alpha::calc(a, b);
	cout << endl;
	beta::calc(a, b);
}