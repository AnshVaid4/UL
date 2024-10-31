#include<iostream>
using namespace std;

int main()
{
	int a{ 2 }, b{3}, c = 0;
	c += a + b;
	cout << c<<endl;

	c += 1;
	c++;
	cout << c << endl;

	cout << c++ << endl;

	cout << (c>b) << endl;

	cout << (c&&b) << endl;

	cout << (c!=b) << endl;

	cout << (c&b) << endl;

	cout << (c<<a) << endl;

	cout << ~c << endl;

	cout << sizeof(c) << endl;

	cout << (c>b?a:b) << endl;

	cout << char (c) << endl;

	cout << static_cast<char>(c) << endl;

	cout << 3/2.0 << endl;

	if (a>b)
		cout << "a>b" << endl;
	else
		cout << "b>a" << endl;

	/*
	Output
	5
	7
	7
	1
	1
	1
	0
	32
	-9
	4
	2


	1.5
	b>a

	*/

	return 0;
}
