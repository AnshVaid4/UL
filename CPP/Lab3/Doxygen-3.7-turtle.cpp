/*
* @file turtle.cpp
* @brief A program to create a turtle and record its moves in a 30x30 2D array
* @summary The Logo language made the concept of turtle graphics famous. Imagine a mechanical turtle
* that walks around the room under the control of a C++ program.
* The turtle holds a pen in one of two positions, up or down. While the pen is
* down, the turtle traces out shapes as it moves; while the pen is up, the turtle
* moves around freely without writing anything. In this problem, you’ll simulate
* the opertion of the turtle.  Using a 30-by-30 array floor, which is initialized to zeros. 
* The program reads commands from an array that contains numbers to indicate the commands 
* in menu. Keeping track of the turtle position and direction at all times and whether the pen
* is currently up or down. Assume that the turtle always starts at position 0,0 (top
* left corner) of the floor with its pen up and facing to the right.
*  As the turtle moves with the pen down, the array if elements is set to
* all 1s. When the command 6 (print) is given, wherever there’s a 1 in the
* array, display an asterisk(*). 
* 
* @author author: ansh vaid
* @date date: 8/10/2024
*/

#include<iostream>
using namespace std;

int main()
{
	int a[30][30],	///< 30x30 2D array which is the map for turtle to roam around
		n,			///< takes the option input from menu
		pen=1,		///< whether to trace path or not, by default '1', which means the path is getting tracked
		x=0,		///< to trace record the x cordinate of turtle
		y=0,		///< to trace y cordinate of turtle
		locxi=0,	///< to record if the x cordinate has to be incremented (generally when turtle goes from top to bottom)
		locxd=0,	///< to record if the x cordinate has to be decremented (generally when turtle goes from bottom to top)
		locyi=1,	///< to record if the y cordinate has to be incremented (generally when turtle goes from left to right)
		locyd=0,	///< to record if the y cordinate has to be decremented (generally when turtle goes from right to left)
		spaces;		///< to record number of steps to move in the direction chosen
	
	//! a general instruction for users to know the boundary
	cout << "Max spaces at a time 29\n";	

	//! infinite loop unless user choses to exit
	while (true)
	{
		//! showing turtle present x and y cordinates
		cout << endl << "Turtle position: " << x << " " << y << endl;

		/*
		* A menu where user gets various options to control the motion of turtle 
		* within the boundaries of 30x30 array, which includes turning the turtle left or right
		* at its position, choosing whether the path needs to be traced or not, then moving in that
		* direction, the number of steps specified by the user.
		*/
		cout << "\nChoose the option:\n"
			"1. Pen up\n"
			"2. Pen down\n"
			"3. Turn right\n"
			"4. Turn left\n"
			"5. move x spaces forward (two number command), where the next number"
			"indicates the number of space to move (eg. 5 6)\n"
			"6. Print the 30-by-30 array\n"
			"9. End of data\n>";

		cin >> n;	///< taking the user input of what user choses from above menu

		//! switch case for the option chosen by user
		switch (n)
		{
		case 1:					///< for option 1 for making the movement untraceable
			pen = 0;
			break;

		case 2:					///< for option 2 for making the movement traceable
			pen = 1;
			break;

		case 3:					///< for option 3 to turn the turtle right at its position
			if (locyi)			
			{
				/*
				* if turtle is going from left to right (points right), it means that locyi is set to 1,
				* therefore to turn right, the locyi is set to 0, and locxi should be set to 1,
				* that make turtle to point downwards, i.e., the right turn is successful
				*/

				locyi = 0;
				locxi = 1;
				//cout << "RA";
			}
			else if (locxi)			///< for option 3 to turn the turtle right at its position
			{
				/*
				* if turtle is going from top to bottom (points downward), it means that locxi is set to 1,
				* therefore to turn right, the locxi is set to 0, and locyd should be set to 1,
				* that make turtle to point (our) left, i.e., the right turn is successful
				*/

				locxi = 0;
				locyd = 1;
				//cout << "RB";
			}
			else if (locyd)			///< for option 3 to turn the turtle right at its position
			{
				/*
				* if turtle is going from right to left (points left), it means that locyd is set to 1,
				* therefore to turn right, the locyd is set to 0, and locxd should be set to 1,
				* that make turtle to point upward, i.e., the right turn is successful
				*/

				locyd = 0;
				locxd = 1;
				//cout << "RC";
			}
			else if (locxd)			///< for option 3 to turn the turtle right at its position
			{
				/*
				* if turtle is going from bottom to top (points upward), it means that locxd is set to 1,
				* therefore to turn right, the locxd is set to 0, and locyi should be set to 1,
				* that make turtle to point (our) right, i.e., the right turn is successful
				*/

				locxd = 0;
				locyi = 1;
				//cout << "RD";
			}
			break;

		case 4:
			if (locyi)			///< for option 4 to turn the turtle left at its position
			{
				/*
				* if turtle is going from left to right (points right), it means that locyi is set to 1,
				* therefore to turn left, the locyi is set to 0, and locxd should be set to 1,
				* that make turtle to point upward, i.e., the left turn is successful
				*/

				locyi = 0;
				locxd = 1;
				//cout << "LA";
			}
			else if (locxd)			///< for option 4 to turn the turtle left at its position
			{
				/*
				* if turtle is going from down to top (points up), it means that locxd is set to 1,
				* therefore to turn left, the locxd is set to 0, and locyd should be set to 1,
				* that make turtle to point in (our) left, i.e., the left turn is successful
				*/

				locxd = 0;
				locyd = 1;
				//cout << "LD";
			}
			else if (locyd)			///< for option 4 to turn the turtle left at its position
			{
				/*
				* if turtle is going from right to left (points left), it means that locyd is set to 1,
				* therefore to turn left, the locyd is set to 0, and locxi should be set to 1,
				* that make turtle to point downwards, i.e., the left turn is successful
				*/

				locyd = 0;
				locxi = 1;
				//cout << "LC";
			}
			else if (locxi)			///< for option 4 to turn the turtle left at its position
			{
				/*
				* if turtle is going from top to down (points down), it means that locxi is set to 1,
				* therefore to turn left, the locxi is set to 0, and locyi should be set to 1,
				* that make turtle to point in (our) right, i.e., the left turn is successful
				*/

				locxi = 0;
				locyi = 1;
				//cout << "LB";
			}			
			break;

		case 5:						///< for option 5 to move the turtle for some steps
			cin >> spaces;			///< input for number of steps in the direction to which it is pointing to
			
			if (locyi == 1 && y + spaces < 30)		///< if spaces to be moved are less than equal to boundary, the boundary ranges from 0-29 for 30x30 2D array
			{
				/*
				* if locyi is 1, this means the steps have to be moved in (our) right direction
				*/

				for (int i = 0; i < spaces; i++)	///< loop to increase the y cordinate of turtle
				{
					if (pen)						///< if pen is down (tracing is on) then the element at that position is set to 1
						a[x][y] = 1;
					y++;							///< increases y cordinate
				}
			}
			if (locxi == 1 && x + spaces < 30)		///< if spaces to be moved are less than equal to boundary, the boundary ranges from 0-29 for 30x30 2D array
			{
				/*
				* if locxi is 1, this means the steps have to be moved in downward direction
				*/

				for (int i = 0; i < spaces; i++)	///< loop to increase the x cordinate of turtle
				{
					if (pen)						///< if pen is down (tracing is on) then the element at that position is set to 1
						a[x][y] = 1;
					x++;							///< increases x cordinate
				}
			}
			if (locyd == 1 && y - spaces > -1)		///< if spaces to be moved are more than equal to boundary, the boundary ranges from 0-29 for 30x30 2D array
			{
				/*
				* if locyd is 1, this means the steps have to be moved in (our) left direction
				*/

				for (int i = 0; i < spaces; i++)	///< loop to decrease the y cordinate of turtle
				{
					if (pen)						///< if pen is down (tracing is on) then the element at that position is set to 1
						a[x][y] = 1;
					y--;							///< decreases y cordinate
				}
			}

			if (locxd == 1 && x - spaces > -1)		///< if spaces to be moved are more than equal to boundary, the boundary ranges from 0-29 for 30x30 2D array
			{
				/*
				* if locxd is 1, this means the steps have to be moved in upward direction
				*/

				for (int i = 0; i < spaces; i++)	///< loop to decrease the x cordinate of turtle
				{
					if (pen)						///< if pen is down (tracing is on) then the element at that position is set to 1
						a[x][y] = 1;
					x--;							///< decreases y cordinate
				}
			}
			break;

		case 6:										///< for option 6 to dispay the movements of turtle
			for (int i = 0; i < 30; i++)			///< simple 2D array print
			{
				for (int j = 0; j < 30; j++)
				{
					if (a[i][j] == 1)				///< if the element contains 1 then it means the path was chosen are traceable
						cout << "*";				///< traced path will be denoted by '*'
					else if (i == x && j== y)		///< this marks the current position of turtle
						cout << "@";				///< current turtle position is marked by '@'
					else
						cout << ".";				///< otherwise its just the 2D array path which remained unexplored by turtle or turtle made it untraceable
				}
				cout << endl;
			}
			break;

		case 9:										///< for option 9 to exit
			exit(0);
		}
	}
	
}
