#include <iostream>
using namespace std;

#include "header.h"

#include "header2.h"

#include "header2.h" /* without ifndef statements in header file
						'initializing': truncation from 'double' to 'float'	Preprocessor header2.h	1
						Error	C2374	'g': redefinition; multiple initialization	Preprocessor header2.h	1*/


#define recArea(l,b) (l * b)
#define recArea2(l,b) ((l) * (b))

int main()
{
	sayhello();
	cout <<endl<< g;
	cout << endl << recArea(3,5);
	cout << endl << recArea(2+1, 5);
	cout << endl << recArea2(2 + 1, 5);
}

/*
Output
Hello from header.h file
9.8
15
7
15
*/

/* header1
void sayhello()
{
	cout << endl << "Hello from header.h file";
}

header2
#ifndef HEADER2_H 
#define HEADER2_H
const float g = 9.8;
#endif
*/
