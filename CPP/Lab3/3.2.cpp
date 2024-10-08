//Print Numbers in Binary Format

#include<iostream>
using namespace std;

void printBinary(int value) 
{
	int digit = 0x80;

	while (digit != 0)
	{
		if ((value & digit) == 0)
		{
			digit = digit >> 1;
			cout << 0;
		}
		else {
			digit = digit >> 1;
			cout << 1;
		}
	}
}

int main(int argc, char* argv[])
{
	printBinary(atoi(argv[1]));

	return 0;
}