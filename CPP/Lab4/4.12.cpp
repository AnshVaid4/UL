#include<iostream>
#include<vector>
#include<array>
using namespace std;

void enter_percent(vector<double>& student_percentages)
{
	double x=0;
	cout << endl;
	while (x >= 0)
	{
		cout << "Enter percentage: ";
		cin >> x;
		if (x >= 0)
			student_percentages.push_back(x);
	}
}

void get_grades(const vector<double>& student_percentages, vector<char>& student_grades)
{
	for (int i = 0; i < student_percentages.size(); i++)
	{
		if (student_percentages.at(i) >= 0)
		{
			if (student_percentages.at(i) >= 80)
			{
				student_grades.push_back('A');
			}
			else if (student_percentages.at(i) >= 65)
			{
				student_grades.push_back('B');
			}
			else if (student_percentages.at(i) >= 50)
			{
				student_grades.push_back('C');
			}
			else if (student_percentages.at(i) >= 35)
			{
				student_grades.push_back('D');
			}
			else if (student_percentages.at(i) < 35)
			{
				student_grades.push_back('F');
			}
		}
			
	}
}


void print_grade_summary(const vector<char>& student_grades)
{
	int A = 0,B=0,C=0,D=0,F=0;

	for (int i = 0; i < student_grades.size(); i++)
	{
		if (student_grades.at(i) == 'A')
		{
			A++;
		}
		else if (student_grades.at(i) == 'B')
		{
			B++;
		}
		if (student_grades.at(i) == 'C')
		{
			C++;
		}
		if (student_grades.at(i) == 'D')
		{
			D++;
		}
		if (student_grades.at(i) == 'F')
		{
			F++;
		}
	}

	cout << "\nTotal Grdaes: A:" << A<<", B:"<<B<<", C:"<<C<<", D:"<<D<<", F:"<<F;
}


int main()
{
	vector<double> pervect[3];
	vector<char> gradvec[3];

	enter_percent(pervect[0]);
	enter_percent(pervect[1]);
	enter_percent(pervect[2]);

	get_grades(pervect[0],gradvec[0]);
	get_grades(pervect[1], gradvec[1]);
	get_grades(pervect[2], gradvec[2]);

	print_grade_summary(gradvec[0]);
	print_grade_summary(gradvec[1]);
	print_grade_summary(gradvec[2]);

}
