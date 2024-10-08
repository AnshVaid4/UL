#include<iostream>
using namespace std;

int main()
{
	int a[30][30],n,pen=1,x=0,y=0,locxi=0,locxd=0,locyi=1,locyd=0,r=1,l=0,spaces;	
	
	//pen 1 means down, 0 means up; locx, locy 0 means fixed, 1 means unfixed
	//locxi means increment on x axis, locxd means decrement on x axis

	while (true)
	{
		cout << "\nChoose the option:\n"
			"1. Pen up\n"
			"2. Pen down\n"
			"3. Turn right\n"
			"4. Turn left\n"
			"5. move x spaces forward (two number command), where the next number"
			"indicates the number of space to move\n"
			"6. Print the 30-by-30 array\n"
			"9. End of data\n";

		cin >> n;

		switch (n)
		{
		case 1:
			pen = 1;
			break;
		case 2:
			pen = 0;
			break;
		case 3:
			if (locyi)			//going towards ->> taking right turn
			{
				locyi = 0;
				locxi = 1;
				r = 1; l = 0;
				//cout << "RA";
			}
			else if (locxi)			//going downwards direction V taking right turn
			{
				locxi = 0;
				locyd = 1;
				r = 1; l = 0;
				//cout << "RB";
			}
			else if (locyd)			//going towards <<- taking right turn
			{
				locyd = 0;
				locxd = 1;
				r = 1; l = 0;
				//cout << "RC";
			}
			else if (locxd)			//going toward upward direction /\ taking right direction
			{
				locxd = 0;
				locyi = 1;
				r = 1; l = 0;
				//cout << "RD";
			}
			break;

		case 4:
			if (locyi)			//going towards ->> taking left turn
			{
				locyi = 0;
				locxd = 1;
				l = 1; r = 0;
				//cout << "LA";
			}
			else if (locxi)			//going downwards direction V taking left turn
			{
				locxi = 0;
				locyi = 1;
				l = 1; r = 0;
				//cout << "LB";
			}
			else if (locyd)			//going towards <<- taking left turn
			{
				locyd = 0;
				locxi = 1;
				l = 1; r = 0;
				//cout << "LC";
			}
			else if (locxd)			//going toward upward direction /\ taking left direction
			{
				locxd = 0;
				locyd = 1;
				l = 1; r = 0;
				//cout << "LD";
			}
			break;

		case 5:
			cin >> spaces;
			
			//if (r == 1)
			{
				if (locyi == 1 && y + spaces < 30)
				{
					//cout << "RL";
					for (int i = 0; i < spaces; i++)
					{
						//y++;
						if (pen)
						a[x][y] = 1;
						y++;
					}
				}

				if (locxi == 1 && x + spaces < 30)
				{
					//cout << "RM";
					for (int i = 0; i < spaces; i++)
					{
						//x++;
						if (pen)
						a[x][y] = 1;
						x++;
					}
				}

				if (locyd == 1 && y - spaces > -1)
				{
					//cout << "RN";
					for (int i = 0; i < spaces; i++)
					{
						//y--;
						if (pen)
						a[x][y] = 1;
						y--;
					}
				}

				if (locxd == 1 && x - spaces > -1)
				{
					//cout << "RO";
					for (int i = 0; i < spaces; i++)
					{
						//x--;
						if (pen)
						a[x][y] = 1;
						x--;
					}
				}

				cout << "Current position: " << x << " " << y;
			}

			if (l == 1)
			{
				if (locyi == 1 && y + spaces < 30)
				{
					//cout << "LL";
					for (int i = 0; i < spaces; i++)
					{
						//y++;
						if (pen)
						a[x][y] = 1;
						y++;
					}
				}

				if (locxi == 1 && x + spaces < 30)
				{
					//cout << "LM";
					for (int i = 0; i < spaces; i++)
					{
						//x++;
						if (pen)
						a[x][y] = 1;
						x++;
					}
				}

				if (locyd == 1 && y - spaces > -1)
				{
					//cout << "LN";
					for (int i = 0; i < spaces; i++)
					{
						//y--;
						if (pen)
						a[x][y] = 1;
						y--;
					}
				}

				if (locxd == 1 && x - spaces > -1)
				{
					//cout << "LO";
					for (int i = 0; i < spaces; i++)
					{
						//x--;
						if (pen)
						a[x][y] = 1;
						x--;
					}
				}
				cout << "Current position: " << x << " " << y;
			}

			break;
		case 6:
			for (int i = 0; i < 30; i++)
			{
				for (int j = 0; j < 30; j++)
				{
					if (a[i][j] == 1)
						cout << "*";				//Traced path
					else if (i == x && j== y)
						cout << "@";				//Current pointer direction
					else
						cout << ".";				//2D path
				}
				cout << endl;
			}

			break;
		case 9:
			exit(0);
		}
	}
	
}