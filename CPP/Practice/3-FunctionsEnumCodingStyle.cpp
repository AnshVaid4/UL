/*
* K&R Coding Style
 • Indent coding style greatly improves readability (human benefit).
 • Used to clarify link between control structures and code
 • Many styles exists (cf. https://en.wikipedia.org/wiki/Indent_style
 ) 
• Introduced by Kernighan and Ritchie, widely used in C/C++:– Each function has its opening brace at the next line on the same indent level as its 
header, the statements within the braces are indented.– The closing brace at the end is on the same indent level as the 
header of the function at a line of its own. – The blocks inside a function, however, have their opening braces 
at the same line as their respective control statements; – Closing braces remain in a line of their own, unless followed 
by a keyword else or while

Commenting Guidelines
 • At beginning of each file, outline the purpose of the file (of its content), name
and date of the last modification (use a complete history if you wish)
 • Every function/method should be preceded by a block of comments detailing:– Name of the function/method & parameters– Description of its purpose in plain English– Description of each parameter and return value
 • Purpose of each variable should be explained
in plain English.
 • Comments within your code should explain what
is going on (in plain English) – the more complex
your code is, the more comments is should contain.

*/

#include<iostream>
using namespace std;

// to add two numbers
int add(int, int);

// to print a number
void print(int);

enum fruits{apple, mango, banana, kiwi, grapes};
enum class FRUITS { apple, orange, grapes };

int main()
{
	int a{ 2 }, b{ 3 };	///< intializing two integer variables
	
	print(a);			///< print function call
	cout << add(a, b)<<endl;	///< add function call to add two numbers

	/// enum fruits
	fruits x=apple, y=banana;	

	/// enum class FRUITS
	FRUITS X=FRUITS::grapes, Y=FRUITS::orange;

	if (x == y)		///< comments
	{
		cout << x << " is " << y<<endl;
	}
	else if (x < y)	///< comments
	{
		cout << x << " is less than " << y << endl;
	}
	else   ///< comments
	{
		cout << x << " is greater than " << y << endl;
	}

	if (X == Y)	///< comments
	{
		cout << static_cast<int>(X) << " is " << static_cast<int>(Y) << endl;
	}
	else if (X < Y)	///< comments
	{
		cout << static_cast<int>(X) << " is less than " << static_cast<int>(Y) << endl;
	}
	else   ///< comments
	{
		cout << static_cast<int>(X) << " is greater than " << static_cast<int>(Y) << endl;
	}

	return 0;

	/*
	Output:

	2
	5
	0 is less than 2
	2 is greater than 1
	*/
}


/*
* Function
* Usage
* Parameters and its usage
* Return
*/
int add(int x, int y)
{
	return x + y;
}

/*
* Function
* Usage
* Parameters and its usage
* Return
*/
void print(int x)
{
	cout << x << endl;
}
