#pragma once
#include <string>
using namespace std;

class Slot //Slot class
{
private:
	int number;
	string color;
public:
	Slot(int number, string color);
	~Slot();
	int getNumber();
	string getColor();
};

//Game and setup
void roulette();
void rouletteSetup();

//Make bet method + types of bets
void makeBets();

void makeNumberBet(int amount);
void makeColorBet(int amount);
void makeEvenOddBet(int amount);
void makeRangeBet(int amount);

//checks results of bets
int checkingBets(Slot* winner);

//Determines winning number
Slot* spin();

//For selecting choices
int choice(int numOfChoices);
bool yesNo(string action);