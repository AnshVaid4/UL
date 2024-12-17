#include<iostream>
using namespace std;

class alpha
{
	int a,b;
public:
	alpha(int x=0, int y=0)
	{
		a = x;
		b = y;
	}

	virtual void add()
	{
		cout << endl << "base: ";
		a += b;
		cout << a;
	}

	void add10()
	{
		cout << endl << "base: ";
		a += 10;
		b += 10;
	}

	void add20()
	{
		cout << endl << "base: ";
		a += 20;
		b += 20;
	}

	void get()
	{
		cout << endl << a << " " << b;
	}
};

class beta: public alpha
{
	int a, b;
public:
	beta(int x = 0, int y = 0):alpha(x,y)
	{
		a = x;
		b = y;
	}

	virtual void add()
	{
		cout << endl << "child: ";
		b += a;
		cout << b;
	}

	void add10()
	{
		cout << endl << "child: ";
		a += 10;
		b += 10;
	}

	void add20()
	{
		cout << endl << "child: ";
		a += 20;
		b += 20;
	}

	void get()
	{
		cout << endl << a << " " << b;
	}
};

int main()
{
	beta b(2, 3);
	alpha* ptr = &b;
	ptr->get();
	ptr->add10();
	ptr->get();
	ptr->add20();
	ptr->get();
	ptr->add();
	ptr->get();

}
