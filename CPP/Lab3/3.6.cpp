#include<iostream>
#include<vector>

using namespace std;

int main()
{
	vector<int> a;
	int n;
	/*a.push_back(1);
	cout << a.at(0);*/

	cout << "Enter 20 integers in 10-100 inclusive range: " << endl;

	while(a.size()<20)
	{
		int check = 0;
		cout << "Enter an integer: \n";
		cin >> n;

		if (n >= 10 && n <= 100) {
			for (int j = 0; j < a.size(); j++)
			{
				if (a[j] == n)
					check = 1;
			}

			if (check == 0)
				a.push_back(n);
			else
				cout << "Element already present, try another!\n";
		}
		else
		{
			cout << "Enter number in range 10-100 inclusive\n";
		}
	}

	cout << endl;
	for (int i = 0; i < a.size(); i++)
	{
		cout << a.at(i) << " ";
	}
}