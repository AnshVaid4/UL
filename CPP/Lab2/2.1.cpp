#include<iostream>
#include<vector>
using namespace std;

double fahrenheit2celsius(double fahrenheit)
{
	return ((double (5)/double (9))*(fahrenheit-32));
}

double celsius2fahrenheit(double celsius)
{
	return ((double(9) / double(5)) * celsius - 32);
}

//double * fahrenheit2celsiusRange(double fmin, double fmax, double step, vector<double> &results)
//{
//	results.clear();
//	int count = 0;
//	for (int i = fmin; i < fmax; i += step)
//	{
//		results.push_back(fahrenheit2celsius(i));
//		count += 1;
//	}
//
//	
//}

vector<double> fahrenheit2celsiusRange(double fmin, double fmax, double step)
{
	vector<double> x;
	int count = 0;
	x.clear();

	for (double i = fmin; i < fmax; i += step)
	{
		x.push_back(fahrenheit2celsius(int(i)));
		count += 1;
	}

	return x;
}

vector<double> *celsius2fahrenheitRange(double cmin, double cmax, double step)
{
	vector<double> *x = new vector<double>();
	int count = 0;
	x->clear();

	for (double i = cmin; i < cmax; i += step)
	{
		x->push_back(celsius2fahrenheit(int (i)));
		count += 1;
	}

	return x;
}

int main()
{
	int i;

	while (true)
	{
		cout << "\n1. Single fahrenheit to celsius\n2. Range fahrenheit to celsius"
			"\n3. Single celsius fahrenheit\n4. Range celsius to fahrenheit\n\n";
		cout << "Choose option from the list: ";
		cin >> i;

		double t;
		double min, max, iter;
		if (i == 1) 
		{
		
			cout << "\nSingle fahrenheit to celsius\n--------------------------"
				"\nEnter value: ";
			cin >> t;
			cout<<"\nFahrenheit to Celsius: "<<fahrenheit2celsius(t);

		}

		if (i == 2) 
		{
				cout << "\nSingle celsius to fahrenheit\n--------------------------"
					"\nEnter value: ";
				cin >> t;
				cout << "\nCelsiusn to Fahrenheit: " << celsius2fahrenheit(t);
		}

		if (i == 3) 
		{
			cout << "\nRange fahrenheit to celsius\n--------------------------"
				"\nEnter value (min,max,step): ";
			cin >> min >> max >> iter;
			cout << "\nFahrenheit to Celsiusn (Range): \n";
			vector<double> x = fahrenheit2celsiusRange(min, max, iter);

			for (int i = 0; i < max - min; i++)
			{
				cout << x[i] << " ";
			}
			cout << endl;

		}

		if (i == 4) {

			cout << "\nRange celsius to fahrenheit\n--------------------------"
				"\nEnter value (min,max,step): ";
			cin >> min >> max >> iter;
			cout << "\nCelsiusn to Fahrenheit (Range): \n";

			vector<double>* y = celsius2fahrenheitRange(min, max, iter);

			for (int i = 0; i < max - min; i++)
			{
				cout << y->at(i) << " ";
			}
			cout << endl;
		}

	}	
}