#include<iostream>
using namespace std;

class alpha
{
	int a;
	int b;
public:
	alpha()
	{
		a = 10;
		b = 20;
	}
	alpha(int x, int y)
	{
		a = x;
		b = y;
	}

	void add_n(int n)
	{
		a += n;
		b += n;
	}

	void sub_n(int n)
	{
		a -= n;
		b -= n;
	}

	void printData()
	{
		cout << endl << a << " " << b;
	}

	alpha& operator+(alpha x)			//returning reference or allias
	{
		alpha result(0,0);
		result.a = this->a + x.a;
		result.b = this->b + x.b;

		return result;
	}

	friend ostream& operator <<(ostream& out, alpha x);
	
};
ostream& operator <<(ostream& out, alpha x)	//returning reference or allias
{
	out << " " <<x.a << " " << x.b;

	return out;
}

int main()
{
	alpha a, b(50, 60),c(0,0);
	a.printData();
	a.add_n(10);
	a.printData();
	a.sub_n(5);
	a.printData();
	b.printData();
	c = a + b;
	c.printData();

	cout << endl << a << b << c;
}
