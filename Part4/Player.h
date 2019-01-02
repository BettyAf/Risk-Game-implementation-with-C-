//Assignment 2_ Team 17                                     
//Comp 345_fall 2017    

#pragma once
#include "Map.h"
#include "DiceRollingFacility.h"
#include "Pack.h"
#include "Subject.h"


using namespace std;

// Player.h
class Player : public Subject{
	//These are what the player class will contain
private:
	string playerName;
	vector<string> myCountries; //this will be a vectored array that map class returns
	Hand *myHand;
	Dice *myDice;
	Deck* gameDeck;
	vector<Observer*> observers;
		

	//Public methods to be used by the player class
public:
	void observer_test();
	Player();
	Player(string);
	Player(string, Hand*, Dice*);
	void reinforce(Map&);
	void attack(Map&);
	void fortify(Map&);
	string getPlayerName();
	void setPlayerName(string);
	vector<string> getCountries();
	void getCountryList();
	void addCountry(string);
	void removeCountry(string);
	Hand* getHand();
	Dice* getDice();
	void addPlayer(Player*);
	string displayCountries();
	int defend(string defending, Map& location);	
	string setupCountryChoice(Map&);
	void addBaseDecorator();
	int addDecorator(Map& location);
	void removeDecorator(Map& location);
		
};

static vector<Player*> allPlayers;
static int bonus = 0;
static int counter = 0;
static int i = 0;
