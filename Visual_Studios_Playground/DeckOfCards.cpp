#include <iostream>
#include <string>
#include <random>
#include <cstdlib>
#include <time.h>
#include "DeckOfCards.h";
#include "BasicChoices.h";
using namespace std;

class Card
{
private:
	string suit;
	int number;

public:
	Card(string suit, int number)//constructor
	{
		this->suit = suit;
		this->number = number;
	}
	~Card()//decostructor
	{
		
	}
	string getSuit()
	{
		return suit;//return suit type
	}
	string getNumber()
	{
		switch (number)//if non-numbered card, return card's type
		{
		case 1:
			return "Ace";
		case 11:
			return "Jack";
		case 12:
			return "Queen";
		case 13:
			return "King";
		}
		return to_string(number);
	}
};

Card* deck[52];
Card* hand[52];
Card* discard[52];

int deckSize = 0, handSize = 0, discardSize = 0;//keeps track of how many cards are in deck, hand, or discard
int select = 1;//set up selector. Default must be 1 so deck shuffles at start.

void deckGame()
{
	loadDeck(); //create deck

	while (select != 0)//until user want to exit game
	{
		cout << endl << "Select an option:" << endl << "1. Deck" << endl << "2. Hand" << endl << "3. Discard" << endl << "0. End Game" << endl;
		if (!(cin >> select))//awaits integer choice. Resets if wrong value is made.
		{
			cin.clear();
			cin.ignore(40, '\n');
			select = -1;
		}

		switch (select)
		{
		case 0:
			cout << "Deck has been put away." << endl;
			break;
		case 1://selecting Deck
			deckOptions();
			break;
		case 2://selecting Hand
			handOptions();
			break;
		case 3://selecting Discard
			discardOptions();
			break;
		default:
			cout << "Invalid Choice" << endl;
		}
	}

	clearGame(); //run function at end of game
}

void loadDeck()//played at beginning to initialize deck
{
	string types[4] = { "Spades", "Hearts", "Diamonds", "Clovers" };//automatically assigns suits
	int size = sizeof(types) / sizeof(types[0]);

	for (int i = 0; i < size; i++)
	{
		for (int j = 1; j < 14; j++)
		{
			deck[deckSize] = new Card(types[i], j);//adds each card to deck
			deckSize++;//increases deck size. Total will be 52.
		}
	}

	cout << "A fresh 52-card deck has been taken out." << endl;
	shuffle();
}

void clearGame()//sets everything to default
{
	deckSize = 0;
	handSize = 0;
	discardSize = 0;
	select = 1;
}

void deckOptions()
{

	if (deckSize <= 0)//stops function if no cards are in deck
	{
		cout << "Deck is empty." << endl;
		return;
	}
	int choice = -1;//intialize selector

	while (true)//loops until proper option is selected
	{
		cout << endl << "What would you like to do with the deck?" << endl << "1. Shuffle" << endl << "2. Draw" << endl << "0. Go Back" << endl;
		if (!(cin >> choice))//awaits integer choice. Resets if wrong value is made.
		{
			cin.clear();
			cin.ignore(40, '\n');
			choice = -1;
		}
		switch (choice)//chooses function based on user input
		{
		case 0:
			return;
		case 1:
			shuffle();
			return;
		case 2:
			drawCards();
			return;
		default:
			cout << "Invalid Choice" << endl;
		}
	}
}

void handOptions()//similar to deckOptions
{
	if (handSize <= 0)
	{
		cout << "Hand is empty." << endl;
		return;
	}
	int choice = -1;

	show();//displays hand for user

	while (true)
	{
		cout << endl << "What would you like to do with your hand?" << endl << "1. Discard" << endl << "2. Return to Deck" << endl << "0. Go Back" << endl;
		if (!(cin >> choice))//awaits integer choice. Resets if wrong value is made.
		{
			cin.clear();
			cin.ignore(40, '\n');
			choice = -1;
		}
		switch (choice)
		{
		case 0:
			return;
		case 1:
			transfer("Discard");
			return;
		case 2:
			transfer("Deck");
			return;
		default:
			cout << "Invalid Choice" << endl;
		}
	}
}

void discardOptions()//similar to deckOptions
{
	if (discardSize <= 0)
	{
		cout << "Discard is empty." << endl;
		return;
	}
	int choice = -1;

	show();//displays discard for user

	while (true)
	{
		cout << endl << "What would you like to do with the discard?" << endl << "1. Shuffle" << endl << "2. Return to Deck" << endl << "3. Return to Hand" << endl << "0. Go Back" << endl;
		if (!(cin >> choice))//awaits integer choice. Resets if wrong value is made.
		{
			cin.clear();
			cin.ignore(40, '\n');
			choice = -1;
		}
		switch (choice)
		{
		case 0:
			return;
		case 1:
			shuffle();
			return;
		case 2:
			transfer("Deck");
			return;
		case 3:
			transfer("Hand");
			return;
		default:
			cout << "Invalid Choice" << endl;
		}
	}
}

void show()
{
	Card* showoff[52];//Create new array for deck to show
	int showSize = 0;

	switch (select)//sets display array equal to current selection
	{
	case 1:
		cout << "Deck currently contains:" << endl;
		memcpy(showoff, deck, sizeof(deck));
		showSize = deckSize;
		break;
	case 2:
		cout << "Hand currently contains:" << endl;
		memcpy(showoff, hand, sizeof(hand));
		showSize = handSize;
		break;
	case 3:
		cout << "Discard currently contains:" << endl;
		memcpy(showoff, discard, sizeof(discard));
		showSize = discardSize;
		break;
	default:
		cout << "No pile available." << endl;
		return;
	}

	for (int i = 0; i < showSize; i++)//displays each card listed
	{
		Card* view = showoff[i];
		cout << i + 1 << ". " << view->getNumber() << " of " << view->getSuit() << endl;
	}
}

void shuffle()
{
	Card* original[52];//Create new array for original pile
	int oSize = 0;

	switch (select)//sets display array equal to current selection
	{
	case 1:
		memcpy(original, deck, sizeof(deck));
		oSize = deckSize;
		break;
	case 2:
		memcpy(original, hand, sizeof(hand));
		oSize = handSize;
		break;
	case 3:
		memcpy(original, discard, sizeof(discard));
		oSize = discardSize;
		break;
	default:
		cout << "No pile available." << endl;
		return;
	}

	Card* shuffled[52];//Create new array for shuffled deck
	int shuffledSize = 0;

	srand(time(0));//ensures generated numbers are completely random

	while (oSize > 0)//Until old deck is empty, take random cards and add them to shuffled array
	{
		int randomCard = rand() % oSize;
		Card* add = original[randomCard];

		if (oSize > 1 && randomCard != (oSize - 1))//special remove function for substitute array
		{
			for (int i = randomCard; i < oSize - 1; i++)
			{
				original[i] = original[i + 1];
			}
		}
		oSize--;

		shuffled[shuffledSize] = add;
		shuffledSize++;
	}

	switch (select)//sets selected pile equal to shuffled.
	{
	case 1:
		memcpy(deck, shuffled, sizeof(deck));
		cout << "Deck has been shuffled." << endl;
		break;
	case 2:
		memcpy(hand, shuffled, sizeof(hand));
		cout << "Hand has been shuffled." << endl;
		break;
	case 3:
		memcpy(discard, shuffled, sizeof(discard));
		cout << "Discard has been shuffled." << endl;
		break;
	}
}

void drawCards()
{
	cout << endl << "How many cards would you like to draw: ";//See how many cards the user wants to draw
	int draws;
	if (!(cin >> draws))//awaits integer choice. Set to 1 if wrong value.
	{
		cout << "Value enetered is not an integer. Drawing 1 card instead." << endl;
		cin.clear();
		cin.ignore(40, '\n');
		draws = 1;
	}

	if (draws <= 0)//Minimum draws is 1
	{
		cout << "Draw number too small. Using minimum draw of 1 instead." << endl;
		draws = 1;
	}
	else if (draws > deckSize)//Maximum draws is equal to deck size
	{
		cout << "Draw number exceeds current deck size. Using maximum draw(s) of " << deckSize << " instead." << endl;
		draws = deckSize;
	}

	cout << endl << "Would you like to draw from top or bottom?" << endl;//Select draws from either top or bottom
	string tb;
	cin >> tb;

	Card* drawed;
	bool drawBottom = true;
	if (tb != "bottom" && tb != "top")
	{
		cout << "Invalid selection. Top selected by default." << endl;
		drawBottom = false;
	}
	else if (tb == "top")
	{
		drawBottom = false;
	}

	cout << "You drew:" << endl;
	for (int i = 0; i < draws; i++)//Removes cards from top of deck and adds to hand
	{
		int drawFrom = 0;
		if (drawBottom)
		{
			drawFrom = deckSize - 1;
		}

		drawed = deck[drawFrom];
		remove(drawFrom);
		hand[handSize] = drawed;
		handSize++;
		cout << drawed->getNumber() << " of " << drawed->getSuit() << endl;
	}
}

void transfer(string destination)//returning Cards from one place to another
{
	while (true)//loops until no more cards from source or user chooses to end
	{
		Card* fromHere[52];//Create new array for original pile
		int fSize = 0;
		string loc;

		switch (select)//sets display array equal to current selection
		{
		case 1:
			memcpy(fromHere, deck, sizeof(deck));
			fSize = deckSize;
			loc = "Deck";
			break;
		case 2:
			memcpy(fromHere, hand, sizeof(hand));
			fSize = handSize;
			loc = "Hand";
			break;
		case 3:
			memcpy(fromHere, discard, sizeof(discard));
			fSize = discardSize;
			loc = "Discard";
			break;
		default:
			cout << "No start pile available." << endl;
			return;
		}

		cout << "Select a card to transfer (use numbers on the left)." << endl;//Tells user to use assigned numbers

		int returned;
		if (!(cin >> returned))//awaits integer choice. Invalid Choice selected if wrong value is entered.
		{
			cin.clear();
			cin.ignore(40, '\n');
			returned = -1;
		}
		if (returned <= 0 || returned > fSize)//if wrong number selected, discard the first card in array
		{
			cout << "Invalid choice. First card will be transfered instead." << endl;
			returned = 1;
		}

		Card* returnMe = fromHere[returned - 1];//take card information from array, then remove from said array
		remove(returned - 1);
		fSize--;

		if (destination == "Deck")
		{
			cout << "Where in the deck would you like to put the card (use the numbers)?" << endl << "1. Top" << endl << "2. Bottom" << endl << "3. Random" << endl;

			int choice;
			if (!(cin >> choice))//awaits integer choice. Selects Invalid if wrong option selected.
			{
				cin.clear();
				cin.ignore(40, '\n');
				choice = -1;
			}

			int place = 0;
			switch (choice)
			{
			case 2:
				place = deckSize;
				break;
			case 3:
				srand(time(0));//ensures generated number is completely random
				place = rand() % deckSize;
				for (int i = deckSize - 1; i >= place; i--)
				{
					deck[i + 1] = deck[i];
				}
				break;
			default:
				if (choice != 1)
				{
					cout << "Invalid Choice. Top selected instead." << endl;
				}
				for (int i = deckSize - 1; i >= 0; i--)
				{
					deck[i + 1] = deck[i];
				}
				break;
			}
			deck[place] = returnMe;
			deckSize++;
		}
		else if (destination == "Hand")
		{
			hand[handSize] = returnMe;//add card to hand
			handSize++;//increase discard size
		}
		else if (destination == "Discard")
		{
			for (int i = discardSize - 1; i >= 0; i--)
			{
				discard[i + 1] = discard[i];
			}
			discard[0] = returnMe;//add card to discard top of discard pile
			discardSize++;//increase discard size
		}
		else
		{
			cout << "No destination pile available." << endl;
			return;
		}

		cout << returnMe->getNumber() << " of " << returnMe->getSuit() << " has been transfered to " << destination << "." << endl;//Notify user that card has been returned

		if (fSize <= 0)//If no more cards left then end the function
		{
			cout << "No more cards left in " << loc << "." << endl;
			return;
		}
		else
		{
			if (yesNo("transfering"))
			{
				show();
			}
			else
			{
				break;
			}
		}
	}
}

void remove(int selected)
{
	if (select <= 0 || select >= 4)
	{
		cout << "Non-existant pile selected. Cannont perform removal.";
		return;
	}

	Card* removeFrom[52];//Create new array for deck to show
	int removeSize = 0;

	switch (select)//sets display array equal to current selection
	{
	case 1:
		memcpy(removeFrom, deck, sizeof(deck));
		removeSize = deckSize;
		break;
	case 2:
		memcpy(removeFrom, hand, sizeof(hand));
		removeSize = handSize;
		break;
	case 3:
		memcpy(removeFrom, discard, sizeof(discard));
		removeSize = discardSize;
		break;
	}

	if (removeSize > 1 && selected != (removeSize - 1))
	{
		for (int i = selected; i < removeSize - 1; i++)
		{
			removeFrom[i] = removeFrom[i + 1];
		}
	}

	removeSize--;

	switch (select)//sets display array equal to current selection
	{
	case 1:
		memcpy(deck, removeFrom, sizeof(removeFrom));
		deckSize = removeSize;
		break;
	case 2:
		memcpy(hand, removeFrom, sizeof(removeFrom));
		handSize = removeSize;
		break;
	case 3:
		memcpy(discard, removeFrom, sizeof(removeFrom));
		discardSize = removeSize;
		break;
	}
}