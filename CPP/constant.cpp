#include<iostream>
using namespace std;

int init()
{
	return 2;
}

constexpr int init2(int x)
{
	//Any new variable defined in this function will have to be initialized too. Can't leave uninitialized
	x = 20 * 30 - x;
	return x;
}

//consteval int greater(int x, int y) 
//{
//	//Any new variable defined in this function will have to be initialized too. Can't leave uninitialized
//	//x = 20 * 30 - x;
//	return x;
//}

int main()
{
	const int x1{ 10 }; //constant variables must be initialized
	//a++; //can't change the value of 'a' since line 6 has made the variable constant
	cout <<"Compile time constant 'x1': "<< x1;

	int x2;
	cout << "\n\nEnter valuse for 'x2': ";
	cin >> x2;
	const int y{ x2 };
	cout << "\nRuntime constant 'y': " << y;

	const int x3=init();
	cout << "\n\nRuntime constant 'x3': " << x3;

	int x4 = 4;
	const int x5 = x3 + x4;
	cout<< "\n\nRuntime constant 'x5': " << x5;





	//############################################ constexpr





	constexpr int x10{ 10 }; 
	cout << "\n\n\nCompile time constant 'x10': " << x10;


	int x20;
	cout << "\n\nEnter valuse for 'x20': ";
	cin >> x20;
	//constexpr int y0{ x20 };  //error since x20 value depends on user input, which is runtime
	//constexpr int y0{ x4 };  //x4 variable is not a constant varialble, therefore it's value can be changes
	constexpr int y0{ x10 };
	cout << "\nRuntime constant 'y0': " << y0;


	//constexpr int x30 = init();  //error since normal function calls comes under runtime expressions
	constexpr int x30 = 30;
	cout << "\n\nRuntime constant 'x30': " << x30;

	int x40 = 4;
	//constexpr int x50 = x30 + x40;  //error since x40 is not a constant variable
	constexpr int x50 = x30 + x30;
	cout << "\n\nRuntime constant 'x50': " << x50;





	//############################################ constexpr functions





	constexpr int x100{ 100 };
	cout << "\n\n\nCompile time constant 'x100': " << x100;


	int x200;
	cout << "\n\nEnter valuse for 'x200': ";
	cin >> x200;
	constexpr int y00{ x100 };
	cout << "\nRuntime constant 'y00': " << y00;


	constexpr int x300 = init2(x1);  //the parameters to constexpr function should not be a variable, but a constexpr/constant variable
	cout << "\n\nRuntime constant 'x300': " << x300;

	int x400 = 40;
	constexpr int x500 = x300 + x300;
	cout << "\n\nRuntime constant 'x500': " << x500;





	//############################################ constexpr functions





	//cout << init2(x200);
}