#include <iostream>
#include <string>
#include<windows.h>
#include "RockPaperScissors.h";
#include "BasicChoices.h";
using namespace std;

int playerHealth, opponets;

void rps()
{
	int types;//range of options when playing

	while (true)//play until player chooses to stop
	{
		//select game type
		cout << "What kind of game will this be? (Pick a number)" << endl << "1. Standard" << endl << "2. Add Lizard/Spock" << endl;
		if (choice(2) == 1) { types = 3; }
		else { types = 5; }

		cout << endl << "How many opponents will you face? (Pick between 1 and 100)" << endl;
		int health = choice(100);

		playerHealth = health, opponets = health;
		int round = 1;//Establish player health, number of opponents, and round number
		bool win = false;

		while (playerHealth > 0)
		{
			cout << "Your Health: " << playerHealth << endl << "Opponets left: " << opponets << endl << endl;//Report

			cout << "Round " << round << "! Choose your weapon (use numbers on left):" << endl << "1. Rock" << endl << "2. Paper" << endl << "3. Scissors" << endl;
			if (types > 3) { cout << "4. Lizard" << endl << "5. Spock" << endl; }//Lizard/Spock Mode
			int weapon = choice(types);//Select Rock, Paper, or Scissors (Lizard/Spock added if chosen)

			int r = 0, p = 0, s = 0, l = 0, sp = 0;//set up opponet weapons
			srand(time(0));//random number generator
			for (int i = 0; i < opponets; i++)
			{
				int pick = rand() % types;//add a Rock, Paper, or Scissors based on random pick
				switch (pick)
				{
				case 0:
					r++;
					break;
				case 1:
					p++;
					break;
				case 2:
					s++;
					break;
				case 3:
					l++;
					break;
				case 4:
					sp++;
					break;
				}
			}

			cout << "Ready..." << endl;//Dramatic buildup
			Sleep(1500);
			cout << "ROCK!" << endl;
			Sleep(1000);
			cout << "PAPER!" << endl;
			Sleep(1000);
			cout << "SCISSORS!" << endl;
			if (types > 3)
			{
				Sleep(1000);
				cout << "LIZARD!" << endl;
				Sleep(1000);
				cout << "SPOCK!" << endl;
			}
			Sleep(500);

			switch (weapon)
			{
			case 1://Rock
				win = outcome("Scissors", "crushed", s, "Paper", "covered", p, "Lizard", "crushed", l, "Spock", "vaporized", sp);
				break;
			case 2://Paper
				win = outcome("Rock", "covered", r, "Scissors", "cut", s, "Spock", "disproved", sp, "Lizard", "eaten", l);
				break;
			case 3://Scissors
				win = outcome("Paper", "cut", p, "Rock", "crushed", r, "Lizard", "decapitated", l, "Spock", "smashed", sp);
				break;
			case 4://Lizard
				win = outcome("Paper", "eaten", p, "Rock", "crushed", r, "Spock", "poisoned", sp, "Scissors", "decapitated", s);
				break;
			case 5://Spock
				win = outcome("Scissors", "smashed", s, "Lizard", "poisoned", l, "Rock", "vaporized", r, "Paper", "disproved", p);
				break;
			}

			if (win) { break; }//Finish if fight is over

			round++;
		}

		if (win)//Results
		{
			cout << "You were victorious after " << round << " Rounds! Congratulations!" << endl << endl;
		}
		else
		{
			cout << "You were defeated in battle. How sad." << endl << endl;
		}

		if (!yesNo("playing"))
		{
			cout << "Thanks for playing!" << endl << endl;
			break;
		}
	}

}

bool outcome(string winWeapon, string winAction, int damageDealt, string loseWeapon, string loseAction, int damageRecieved, string winWeapon2, string winAction2, int damageDealt2, string loseWeapon2, string loseAction2, int damageRecieved2)
{
	bool wins = false, losses = false;
	if (damageDealt > 0)//defeat users with weaker weapon
	{
		string opp = " Opponet";
		if (damageDealt > 1)//pronunciation
		{
			opp += "s";
			if (winWeapon != "Scissors")
			{
				winWeapon += "s";
			}
			winWeapon += " have ";
		}
		else
		{
			winWeapon += " has ";
		}

		wins = true;

		cout << damageDealt << opp << " with " << winWeapon << "been " << winAction << "!" << endl;
		opponets -= damageDealt;
	}

	if (damageDealt2 > 0)//Check second win (Lizard/Spock Mode)
	{
		if (wins)
		{
			Sleep(750);
			cout << "And ";//pronunciation
		}

		string oppB = " Opponet";
		if (damageDealt2 > 1)//pronunciation
		{
			oppB += "s";
			if (winWeapon2 != "Scissors")
			{
				winWeapon2 += "s";
			}
			winWeapon2 += " have ";
		}
		else
		{
			winWeapon2 += " has ";
		}

		wins = true;

		cout << damageDealt2 << oppB << " with " << winWeapon2 << "been " << winAction2 << "!" << endl;
		opponets -= damageDealt2;
	}

	if (opponets <= 0)//if victorious
	{
		Sleep(750);
		return true;
	}

	if (damageRecieved > 0)//Player takes damage from stronger weapon
	{
		losses = true;//If wins were printed earlier
		if (wins)
		{
			Sleep(750);
			cout << "... But ";
		}

		string opp2 = " Opponet";
		if (damageRecieved > 1)//pronunciation
		{
			opp2 += "s have ";
			if (loseWeapon != "Scissors")
			{
				loseWeapon += "s";
			}
		}
		else
		{
			opp2 += " has ";
		}

		cout << damageRecieved << opp2 << loseAction << " you with " << loseWeapon << "!" << endl;
		playerHealth -= damageRecieved;
	}

	if (damageRecieved2 > 0)//Second losing weapon (Lizard/Spock Mode)
	{
		if (losses)
		{
			Sleep(750);
			cout << "And ";//pronunciation
		}

		if (wins && !losses)
		{
			Sleep(750);
			cout << "... But ";
		}
		losses = true;//If wins were printed earlier

		string opp2B = " Opponet";
		if (damageRecieved2 > 1)//pronunciation
		{
			opp2B += "s have ";
			if (loseWeapon2 != "Scissors")
			{
				loseWeapon2 += "s";
			}
		}
		else
		{
			opp2B += " has ";
		}

		cout << damageRecieved2 << opp2B << loseAction2 << " you with " << loseWeapon2 << "!" << endl;
		playerHealth -= damageRecieved2;
	}

	if (!wins && !losses) //if it is a draw
	{
		cout << "Everyone chose the same weapon. This round is a draw." << endl;
	}

	Sleep(750);
	return false;
}