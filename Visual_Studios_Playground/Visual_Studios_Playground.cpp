#include <iostream>
#include <string>
#include "DeckOfCards.h"
#include "Roulette.h"
#include "RockPaperScissors.h"
using namespace std;

int main()
{
	int choice;
	while (true)//Will loop until exit is selected
	{
		//Prints list of choices
		cout << "Select a program:" << endl;
		cout << "1. Deck of Cards" << endl;
		cout << "2. Roulette" << endl;
		cout << "3. Rock Paper Scissors" << endl;
		cout << "0. Exit" << endl;

		if (!(cin >> choice))//awaits integer choice. Resets if wrong value is made.
		{
			cin.clear();
			cin.ignore(40, '\n');
			choice = -1;
		}

		switch (choice)
		{
		case 0:
			cout << "Thanks for playing!" << endl;
			return 0; //ends program
		case 1:
			deckGame(); //plays Deck program
			break;
		case 2:
			roulette(); //plays roulette program
			break;
		case 3:
			rps();
			break;
		default:
			cout << "Invalid choice. Please try again." << endl; //default resets choices
		}

		cout << endl; // extra spacing in between games
	}
}
