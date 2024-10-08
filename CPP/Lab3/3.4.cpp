#include<iostream>
#include<windows.h>
using namespace std;

int main()
{
	int a[200],counter200=0, counter300 = 0, counter400 = 0, counter500 = 0,
		counter600 = 0, counter700 = 0, counter800 = 0, counter900 = 0, counter1000 = 0;
	cout << "Initializing your array!\n";
	for (int i = 0; i < 200; i++)
	{
		srand(time(0) * time(0) * time(0));
		a[i] = (rand() % 800)+200;
		Sleep(10);
	}

	for (int i = 0; i < 200; i++)
	{
		cout << a[i] << " ";
	}

	cout << endl;

	for (int i = 0; i < 200; i++)
	{
		if (a[i] < 300 && a[i]>200)
			counter200++;
		else if (a[i] < 400 && a[i]>300)
			counter300++;
		else if (a[i] < 500 && a[i]>400)
			counter400++;
		else if (a[i] < 600 && a[i]>500)
			counter500++;
		else if (a[i] < 700 && a[i]>600)
			counter600++;
		else if (a[i] < 800 && a[i]>700)
			counter700++;
		else if (a[i] < 900 && a[i]>800)
			counter800++;
		else if (a[i] < 1000 && a[i]>900)
			counter900++;
		else if (a[i] >= 1000 )
			counter1000++;
	}

	cout << "\n200-299: " << counter200 <<
		"\n300-399: " << counter300 <<
		"\n400-499: " << counter400 <<
		"\n500-599: " << counter500 <<
		"\n600-699: " << counter600 <<
		"\n700-799: " << counter700 <<
		"\n800-899: " << counter800 <<
		"\n900-999: " << counter900 <<
		"\n1000 and over: " << counter1000;

}