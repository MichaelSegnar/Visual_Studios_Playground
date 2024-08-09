#include <iostream>
#include <string>
#include<windows.h>
#include "Roulette.h";
using namespace std;

int choice(int numOfChoices)//Method for integer choices
{
	int selection;
	while (true)//Loops until proper number is selected
	{
		while (!(cin >> selection))//awaits integer choice within range. Resets if wrong value is made.
		{
			cin.clear();
			cin.ignore(40, '\n');
			cout << "Invalid Number. Please enter an integer." << endl;
		}
		if (selection <= 0)//If number is out of range, the method resets
		{
			cout << "Number too low. Please try again." << endl;
		}
		else if (selection > numOfChoices)
		{
			cout << "Number too high. Please try again." << endl;
		}
		else//Returns number once proper selection is made
		{
			return selection;
		}
	}
}

bool yesNo(string action)//Method for yes or no options
{
	cout << "\nWould you like to continue " << action << "? (y / n)" << endl;//Check if user wants to keep playing and explains what action they are performing
	string decide;
	while (true)//loops until proper selection is made
	{
		while (!(cin >> decide))//awaits character choice. Selects Invalid Choice is input is not char
		{
			cin.clear();
			cin.ignore(40, '\n');
			cout << "Invalid choice. Please insert text." << endl;
		}
		if (decide != "y" && decide != "n")//Resets if selection is neither y or n
		{
			cout << "Invalid choice. Please enter 'y' or 'n'." << endl;
		}
		else//Returns true if y, returns false if n
		{
			if (decide == "y")
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
}