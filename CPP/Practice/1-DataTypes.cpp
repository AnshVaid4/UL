/*

Source code can be edited with any text editor.
 • IDEs (Visual Studio, Code:Blocks, Netbeans, Eclipse, etc.) integrate text 
editor, compiler & debugger.
 • Source files typically have extension .cpp
 • Compiler translates source code into machine code (binaries).
 • Binaries are machine and OS dependent – need to re-compile for different 
systems
 • Compilation is a 3 step process: 
  1. Pre-Processor
  – All lines beginning with # are pre-processor directives. – Performs text substitution (replace text with other text, e.g. macro substitution, 
  removing comments).– Provides header file inclusion, macros and conditional inclusion/compilation.
 
 2. Compiler
 – Transform C++ code into object code (incomplete machine code).
 – Checks that syntax of C++ code is correct and that identifiers are declared.
 – Some references (e.g. to variables, functions) may not yet been resolvable.
 – Any discovered mistakes will lead to “compile time 
errors”: These must be fixed by programmer before 
linking can take place.– Results in object code: “incomplete” machine code that
 is executable (some information is missing).


 3. Linker
– Joins various object code files and required libraries: Fills in missing pieces in object 
code and may re-arrange code.– All references must be resolved 
– otherwise a “link time error” occurs (for example if 
the object code for called function is not found).
– Results in an executable file specific to the hardware for which the compiler is 
designed.
*/


#include<iostream>
#include<cstdlib>
using namespace std;

int main()
{
	cout << sizeof(char) << " "
		<< sizeof(unsigned char) << " "
		<< sizeof(char16_t) << " "
		<< sizeof(char32_t) << " "
		<< sizeof(wchar_t); //Output: 1 1 2 4 2

	cout <<endl<<
		sizeof(int) << " "<<
		sizeof(short int) << " "
		<< sizeof(unsigned int) << " "
		<< sizeof(long int) << " "
		<< sizeof(long long int) << " "
		<< sizeof(20L) << " "
		<< sizeof(20LL) << " "
		<< sizeof(20U); //Output: 4 2 4 4 8 4 8 4

	cout << endl <<
		sizeof(float) << " " <<
		sizeof(double) << " " <<
		sizeof(long double) << " " <<
		sizeof(20.0F) << " " <<
		sizeof(20L) << " " <<
		sizeof(20.0L) << " " <<
		sizeof(20.0); //Output: 4 8 8 4 4 8 8

	volatile int a = 2; //value in variable can be changed by other program

	// return EXIT_FAILURE;
	return EXIT_SUCCESS;
}
