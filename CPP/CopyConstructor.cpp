#include <iostream>
using namespace std;

//Copy constructor is used when pointers or DMA is used within the class and we don't wat bit by bit copy of object

class alpha
{
	int* data, c;

public:
	alpha(int* data = nullptr, int c = 0)
	{
		this->data = data;
		this->c = c;
	}

	~alpha() { delete data; }    // dealocate the allocated memory

	void get()
	{
		cout << endl;
		cout << *data << " " << c;
	}

	alpha& operator=(alpha& other)
	{
		
		this->c = other.c;
		/*
		//correct way. Uncommnet to make this code work
		int* ptr = new int(*other.data);	
		this->data = ptr;
		*/

		this->data = other.data;
		return *this;
	}

};
int main()
{
	int* x = new int(20), *y = new int(40);
	alpha a(x, 5), b(y,10);
	a.get();
	b.get();

	b = a;
	b.get();
	a.get();
	


}
