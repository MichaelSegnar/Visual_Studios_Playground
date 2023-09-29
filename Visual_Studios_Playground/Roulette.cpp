#include <iostream>
#include <string>
#include<windows.h>
#include "Roulette.h";
using namespace std;

class Bet//Base class for bets
{
private:
	int amount;//Cash spent on bet
public:
	void setAmount(int amount)//Getter-Setter methods
	{
		this->amount = amount;
	}
	int getAmount()
	{
		return amount;
	}
	bool betCheck()//default bet result
	{
		return false;
	}
};

class NumberBet : Bet//Bets for specific numbers
{
private:
	int number;//Number selected
	NumberBet* next;//for Linked List
public:
	NumberBet(int amount, int number)//Constructor
	{
		setAmount(amount);//use setAmount in Base class
		this->number = number;
		next = NULL;//next is always NULL until similar bet is made
	}
	~NumberBet()//Deconstructor
	{

	}
	int betAmount()//method for recieving bet amount
	{
		return getAmount();
	}
	void setNext(NumberBet* next)//Getter-Setter method for next item in Linked List
	{
		this->next = next;
	}
	NumberBet* getNext()
	{
		return next;
	}
	bool betCheck(Slot* result)//Checks bet by seeing if numbers are equal
	{
		return number == result->getNumber();
	}
};

class ColorBet : Bet//Bet for colors
{
private:
	string color;//Colors recorded as string
	ColorBet* next;
public:
	ColorBet(int amount, string color)
	{
		setAmount(amount);
		this->color = color;
		next = NULL;
	}
	~ColorBet()
	{

	}
	int betAmount()
	{
		return getAmount();
	}
	void setNext(ColorBet* next)
	{
		this->next = next;
	}
	ColorBet* getNext()
	{
		return next;
	}
	bool betCheck(Slot* result)//Compares strings to get bet result
	{
		return color == result->getColor();
	}
};

class EvenOddBet : Bet//Checks if bet is even number or odd
{
private:
	bool even;//Even or Odd determined by bool
	EvenOddBet* next;
public:
	EvenOddBet(int amount, bool even)
	{
		setAmount(amount);
		this->even = even;
		next = NULL;
	}
	~EvenOddBet()
	{

	}
	int betAmount()
	{
		return getAmount();
	}
	void setNext(EvenOddBet* next)
	{
		this->next = next;
	}
	EvenOddBet* getNext()
	{
		return next;
	}
	bool betCheck(Slot* result)//Uses bool and number to find bet result
	{
		int resultNum = result->getNumber();
		if (even && resultNum % 2 == 0)
		{
			return true;
		}
		else if (!even && resultNum % 2 == 1)
		{
			return true;
		}
		return false;
	}
};

class RangeBet : Bet//For bets on a specific number range
{
private:
	int lowEnd, highEnd, mult;//integers for number range and pay out multiplier
	RangeBet* next;
public:
	RangeBet(int amount, int lowEnd, int highEnd)
	{
		setAmount(amount);
		this->lowEnd = lowEnd;
		this->highEnd = highEnd;
		next = NULL;
		if (highEnd - lowEnd <= 11)//if one-third of whole board
		{
			mult = 3;
		}
		else//if half of board
		{
			mult = 2;
		}
	}
	~RangeBet()
	{

	}
	int betAmount()
	{
		return getAmount();
	}
	void setNext(RangeBet* next)
	{
		this->next = next;
	}
	RangeBet* getNext()
	{
		return next;
	}
	int getMult()//Getter method for multiplier
	{
		return mult;
	}

	bool betCheck(Slot* result)//Gets result by seeing if number is within given range
	{
		return (result->getNumber() >= lowEnd && result->getNumber() <= highEnd);
	}
};



Slot::Slot(int number, string color)//Slot constructor
{
	this->number = number;
	this->color = color;
}

Slot::~Slot() {}//Slot deconstructor

int Slot::getNumber()//Getter methods for number and color
{
	return number;
}

string Slot::getColor()
{
	return color;
}

int cash;//Cash refers to current cash user holds.
int baseCash = 2000;//Base Cash is the initial amount the player recieves.

NumberBet* numberHead = NULL;//Heads of Linked Lists. One for each type of bet.
ColorBet* colorHead = NULL;
EvenOddBet* eoHead = NULL;
RangeBet* rangeHead = NULL;

Slot* wheel[37];//Array for all numbers on the roulette

void roulette()
{
	rouletteSetup();//Sets up roulette
	
	cash = baseCash;//Gives player the initial amount of cash then displays it
	cout << "You have been given $" << cash << "." << endl;

	while (true)//Loops until the player wants the game to end or they run out of money
	{
		int cashAtStart = cash;//Records amount of cash held before bets are made

		makeBets();//Make bets first

		Slot* winner = spin();//Determine and record winning number

		cash += checkingBets(winner);//Determines how much cash was won and adds it to total

		int diff = abs(cash - cashAtStart);//Finds difference between old amount and new amount then explains how much was gained or lost
		if (cash - cashAtStart > 0)
		{
			cout << "\nYou gained $" << diff << "!" << endl;
		}
		else if (cash - cashAtStart < 0)
		{
			cout << "\nYou lost $" << diff << "!" << endl;
		}
		else
		{
			cout << "\nYou did not lose or gain any cash." << endl;
		}
		cout << "New total is $" << cash << "." << endl;

		if (cash <= 0)//Game Over when money runs out
		{
			cout << "\nYou are out of cash. Game Over!" << endl;
			break;
		}

		if (!yesNo("playing"))//Checks if user wants to keep playing. Ends game if he does not.
		{
			cout << "\nGame Over! Final Score: $" << cash << endl;//Determines if player has more or less cash than they initially started with
			int finalDiff = cash - baseCash;
			if (finalDiff > 0)
			{
				cout << "You earned $" << finalDiff << "!" << endl;
			}
			else if (finalDiff < 0)
			{
				cout << "You lost $" << abs(finalDiff) << "!" << endl;
			}
			else
			{
				cout << "No cash earned nor lost." << endl;
			}
			break;
		}
	}
}

void rouletteSetup()
{
	wheel[0] = new Slot(0, "Green");//add Zero
	
	for (int i = 1; i < 10; i = i + 2)//add Reds
	{
		wheel[i] = new Slot(i, "Red");
	}
	for (int i = 12; i < 20; i = i + 2)
	{
		wheel[i] = new Slot(i, "Red");
	}
	for (int i = 19; i < 28; i = i + 2)
	{
		wheel[i] = new Slot(i, "Red");
	}
	for (int i = 30; i < 37; i = i + 2)
	{
		wheel[i] = new Slot(i, "Red");
	}

	for (int i = 2; i < 12; i = i + 2)//add Blacks
	{
		wheel[i] = new Slot(i, "Black");
	}
	for (int i = 11; i < 19; i = i + 2)
	{
		wheel[i] = new Slot(i, "Black");
	}
	for (int i = 20; i < 30; i = i + 2)
	{
		wheel[i] = new Slot(i, "Black");
	}
	for (int i = 29; i < 37; i = i + 2)
	{
		wheel[i] = new Slot(i, "Black");
	}
}

void makeBets()
{
	while (true)//Loop until player stops making bets or runs out of cash
	{
		cout << "\nYou currently have $" << cash << ". How much would you like to bet?" << endl;

		int cashBet = choice(cash);//Let player choose how much cash to bet

		cash -= cashBet;//Remove betted cash

		cout << "\nWhat kind of bet would you like to make?" << endl << "1. Number (x32 Payout)" << endl << "2. Color (x2 Payout)" << endl << "3. Even/Odd (x2 Payout)" << endl << "4. Number Range (x2/3 Payout)" << endl;

		int betType = choice(4);//Player chooses what kind of bet to make. Different method used depending on choice.

		switch (betType)
		{
		case 1:
			makeNumberBet(cashBet);
			break;
		case 2:
			makeColorBet(cashBet);
			break;
		case 3:
			makeEvenOddBet(cashBet);
			break;
		case 4:
			makeRangeBet(cashBet);
			break;
		}

		if (cash <= 0)//Stops bets if there is no more cash
		{
			cout << "\nOut of cash. No more bets can be made." << endl;
			return;
		}

		if (!yesNo("betting"))//Asks if player wants to continue betting. Ends function if they choose no.
		{
			break;
		}
	}
}

void makeNumberBet(int cashBet)
{
	cout << endl << "Pick a number from 0 to 36:" << endl;

	int choice;
	while (true)//Loops until proper number is chosen (used over choice method for inclusion of 0)
	{
		while (!(cin >> choice))//awaits integer choice within range. Resets if wrong value is made.
		{
			cin.clear();
			cin.ignore(40, '\n');
			cout << "Invalid Number. Please enter an integer." << endl;
		}
		if (choice < 0)//Informs player if number is out of range, ends loop if within range
		{
			cout << "Number too low. Please try again." << endl;
		}
		else if (choice >= 37)
		{
			cout << "Number too high. Please try again." << endl;
		}
		else
		{
			return ;
		}
	}

	if (numberHead == NULL)//if this is first bet of specified type, make it head of Linked List
	{
		numberHead = new NumberBet(cashBet, choice);//Creates new bet using cash spent on bet and player's selection
	}
	else//goes down liked list to last made bet. Adds the new bet to the end of the Linked List.
	{
		NumberBet* trace = numberHead;
		while (trace->getNext() != NULL)
		{
			trace = trace->getNext();
		}
		trace->setNext(new NumberBet(cashBet, choice));
	}
}

void makeColorBet(int cashBet)
{
	cout << endl << "Pick a color:\n1. Red\n2. Black" << endl;

	int colorChoice = choice(2);//Player chooses color based on numbers

	string color;//String value determined by number choice
	switch (colorChoice)
	{
	case 1:
		color = "Red";
		break;
	case 2:
		color = "Black";
		break;
	}

	if (colorHead == NULL)
	{
		colorHead = new ColorBet(cashBet, color);
	}
	else
	{
		ColorBet* trace = colorHead;
		while (trace->getNext() != NULL)
		{
			trace = trace->getNext();
		}
		trace->setNext(new ColorBet(cashBet, color));
	}
}

void makeEvenOddBet(int cashBet)
{
	cout << endl << "Pick one:\n1. Even\n2. Odd" << endl;

	int eoChoice = choice(2);

	bool even;//bool value determined by number choice
	switch (eoChoice)
	{
	case 1:
		even = true;
		break;
	case 2:
		even = false;
		break;
	}

	if (eoHead == NULL)
	{
		eoHead = new EvenOddBet(cashBet, even);
	}
	else
	{
		EvenOddBet* trace = eoHead;
		while (trace->getNext() != NULL)
		{
			trace = trace->getNext();
		}
		trace->setNext(new EvenOddBet(cashBet, even));
	}
}

void makeRangeBet(int cashBet)
{
	cout << endl << "Pick a range of numbers:\n\nHalves (x2 Payout):\n1. 1 - 18\n2. 19 - 36\n\nThirds (x3 Payout)\n3. 1 - 12\n4. 13 - 24\n5. 25 - 36" << endl;

	int rangeChoice = choice(5);

	int low, high;//low and high values based on number choice
	switch (rangeChoice)
	{
	case 1:
		low = 1;
		high = 18;
		break;
	case 2:
		low = 19;
		high = 36;
		break;
	case 3:
		low = 1;
		high = 12;
		break;
	case 4:
		low = 13;
		high = 24;
		break;
	case 5:
		low = 25;
		high = 36;
		break;
	}

	if (rangeHead == NULL)
	{
		rangeHead = new RangeBet(cashBet, low, high);
	}
	else
	{
		RangeBet* trace = rangeHead;
		while (trace->getNext() != NULL)
		{
			trace = trace->getNext();
		}
		trace->setNext(new RangeBet(cashBet, low, high));
	}
}

int checkingBets(Slot* winner)
{
	int cashWon = 0;//integer records amount of cash won

	while (numberHead != NULL)//Goes through each bet in Linked List.
	{
		NumberBet* nBet = numberHead;//Records current bet
		if (nBet->betCheck(winner))//Uses betCheck method to determine winner
		{
			int prize = nBet->betAmount() * 32;//if winner, cash award is determined to betted amount times payout multiplier
			Sleep(1000);//Dramatic pause
			cout << "You guessed the correct Number! You win $" << prize << "!" << endl;//Displays cash won then adds it to total
			cashWon += prize;
		}
		numberHead = numberHead->getNext();//Gets the next bet in the linked list
		delete nBet;//deletes the current bet
	}

	while (colorHead != NULL)
	{
		ColorBet* cBet = colorHead;
		if (cBet->betCheck(winner))
		{
			int prize = cBet->betAmount() * 2;
			Sleep(1000);
			cout << "You guessed the correct Color! You win $" << prize << "!" << endl;
			cashWon += prize;
		}
		colorHead = colorHead->getNext();
		delete cBet;
	}

	while (eoHead != NULL)
	{
		EvenOddBet* eoBet = eoHead;
		if (eoBet->betCheck(winner))
		{
			int prize = eoBet->betAmount() * 2;
			Sleep(1000);
			
			string evenOdd = "Even";
			if (winner->getNumber() % 2 == 1)
			{
				evenOdd = "Odd";
			}

			cout << "You guessed that the number was " << evenOdd << "! You win $" << prize << "!" << endl;
			cashWon += prize;
		}
		eoHead = eoHead->getNext();
		delete eoBet;
	}

	while (rangeHead != NULL)
	{
		RangeBet* rBet = rangeHead;
		if (rBet->betCheck(winner))
		{
			int prize = rBet->betAmount() * rBet->getMult();
			Sleep(1000);
			cout << "You guessed the correct Number Range! You win $" << prize << "!" << endl;
			cashWon += prize;
		}
		rangeHead = rangeHead->getNext();
		delete rBet;
	}

	if (cashWon == 0)//Tell player if no cash was won
	{
		Sleep(1000);
		cout << "All bets were wrong. No cash won." << endl;
	}

	return cashWon;//Returns total amount of cash won
}

Slot* spin()
{
	cout << "\nSpinning the wheel";
	for (int i = 0; i < 3; i++)
	{
		Sleep(500);//Dramatic buildup
		cout << ".";
	}
	Sleep(1000);
	srand(time(0));//Creates random number generator
	Slot* ballLandsAt = wheel[rand() % 37];//Picks random spot on the roulette
	cout << "\nBall landed at " << ballLandsAt->getNumber() << " " << ballLandsAt->getColor() << endl;//Displays outcome
	return ballLandsAt;//Returns outcome
}

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
		else if(selection > numOfChoices)
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
	while(true)//loops until proper selection is made
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