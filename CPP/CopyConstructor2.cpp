#include<iostream>
using namespace std;

class alpha
{
	int size;
	int* data;

public:
	alpha(int size = 0, int* data = nullptr)
	{
		this->size = size;
		this->data = new int[size];
	}

	
	alpha& operator=(alpha& x)		//assignment operator overload for deep copy
	{
		size = x.size;
		data = new int[size];
		for (int i = 0; i < x.size; i++)
		{
			data[i] = x.data[i];
		}

		return *this;
	}

	alpha(alpha &x)				// copy constructor for deep copy
	{
		size = x.size;
		data = new int[size];				//instead of implementing data=x.data
		for (int i = 0; i < x.size; i++)
		{
			data[i] = x.data[i];
		}

	}

	~alpha()
	{
		delete[] data;
	}

	void assign()
	{
		int n;
		for (int i = 0; i < size; i++)
		{
			cout << endl << "Enter value " << i + 1 << ":";
			cin >> n;
			data[i] = n;
		}
	}

	int* getdata()
	{
		return data;
	}
	int getsize()
	{
		return size;
	}
};

int main()
{
	alpha a(5);
	a.assign();
	int* ptr = a.getdata();
	cout << endl;
	for (int i = 0; i < a.getsize(); i++)
	{
		cout << ptr[i];
	}

	//b = a;		//calling copy constructor

	alpha b(a);		//calling copy constructor

	ptr = a.getdata();
	cout << endl;
	for (int i = 0; i < a.getsize(); i++)
	{
		cout << ptr[i];
	}
}
