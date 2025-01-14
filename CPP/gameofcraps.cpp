#include<iostream>
#include<cstdlib>
#include<conio.h>
#include<ctime>

using namespace std;

int main()
{
	srand(time(0));
	int d1, d2, prev = 0, game = 0;
	char ch;
	while (true)
	{

		if (game == 0)
		{
			cout << "\n\nPress any key to roll the dices!";
			_getch();
			d1 = rand() % 6 + 1;
			d2 = rand() % 6 + 1;

			cout << "\n>> Rolling <<";
			cout << "\n***** Dice 1: " << d1 << " ***** Dice 2: " << d2;

			if ((d1 + d2 == 7 || d1 + d2 == 11) && prev == 0)
			{
				cout << "\n!!!!!! Congrats !!!!!! You won the game";
				game = 1;
			}
			else if ((d1 + d2 == 2 || d1 + d2 == 3 || d1 + d2 == 12) && prev == 0)
			{
				cout << "\nXXXXX Hard Luck, You Lost The Game XXXXX";
			}
			else
			{
				cout << "\n You got a point: " << d1 + d2 << ". Roll again to get the same point! If you get 7 then you lose!!";
				if (d1 + d2 == prev && d1 + d2 != 7)
				{
					cout << "\n!!!!!! Congrats !!!!!! You won the game";
					game = 1;
				}
				else if (d1 + d2 != 7)
				{
					prev = d1 + d2;
					continue;
				}
				else
				{
					cout << "\nXXXXX Hard Luck, You Lost The Game XXXXX";
					game = 1;
				}
			}
		}
		else
		{
			cout << "\n\nDo you wanna play more?(y/Y)";
			cin >> ch;
			{
				if (ch == 'y' || ch == 'Y')
				{
					cout << "\n\n-----------------------------------------------------\n\n";
					game = 0;
					prev = 0;
					continue;
				}
				else
				{
					exit(0);
				}
			}
		}
	}
}
