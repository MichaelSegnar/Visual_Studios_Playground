#pragma once
#include <string>
using namespace std;

//original game + setup/shutdown
void deckGame();
void loadDeck();
void clearGame();

//options
void deckOptions();
void handOptions();
void discardOptions();

//show function for revealing cards in pile
void show();

//shuffle function for shuffling piles
void shuffle();

//draw function
void drawCards();

//transfer function for moving cards between piles
void transfer(string destination);

//remove function for removing card from pile
void remove(int selected);