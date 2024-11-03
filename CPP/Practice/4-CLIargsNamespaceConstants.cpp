#include<iostream>
using namespace std;

int x = 23;

int add(int x, int y)
{
	return x + y;
}

namespace test
{
	int x = 20;
	int y=add(x, 10);
}

using namespace test;

int main(int argc, char* argv[])
{
	int x = 40;

	if (argc > 1)
	{
		for (int i = 0; i < argc; i++)
		{
			cout << "Argument " << i << ": " << argv[i]<<endl;
		}
		
		if (atoi(argv[1]) > 18)
			cout << "\nEligible to vote\n";
		else
			cout << "\nNot eligible to vote\n";

		if (atol(argv[2]) > 65535)
			cout << "\nEligible to buy air ticket\n";
		else
			cout << "\nNot eligible to buy air ticket\n";

		if (atof(argv[3]) > 0.5 && atof(argv[3]) <= 1)
			cout << "\nMuch likely to have an event\n";
		else
			cout << "\nNot likely to have an event is more\n";

		cout << endl << x;
		cout << endl << ::x;
		cout << endl << ::x;
		cout << endl << test::x;
		cout << endl << y;

		//constants
		/*
		const: both run time and compile time constant
		constexpr: compile time constant, if wanna use function call with parameters as constexpr variables,
					then the function's return type should be constexpr. This makes it both run-time and compile-time,
					and compiler makes the decision
		consteval: return type of function for compile time. This makes a function compile time constant
		*/

	}
	else {
		cout << "Pass some CLI options";
	}
}
