#include<iostream>
#include<vector>
using namespace std;

int main(int argc, char* argv[])
{
	int temp;
	vector<int> a(argc);

	for (int i = 1; i < argc; i++)
		/*a.push_back(atoi(argv[i]));*/
		a[i - 1] = atoi(argv[i]);



	for (int i = 0; i < argc; i++)
	{
		for (int j = i + 1; j < argc; j++)
		{
			if (a[i] > a[j])
			{
				temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
			else
				continue;
		}
	}

	for (int i = 0; i < argc; i++)
		cout << a[i] << " ";

}