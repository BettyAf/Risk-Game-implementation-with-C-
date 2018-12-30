//Assignment 2_ Team 17                                     
//Comp 345_fall 2017    

#pragma once

#include "Map.h"
#include "DiceRollingFacility.h"
#include "Pack.h"


using namespace std;

// Player.h
class Player {
	//These are what the player class will contain
private:
	string playerName;
	vector<string> myCountries; //this will be a vectored array that map class returns
	Hand *myHand;
	Dice *myDice;

	//Public methods to be used by the player class
public:
	Player();
	Player(string);
	Player(string, Hand*, Dice*);
	void reinforce(Map&);
	bool attack(string, string, int, Map&); 
	bool fortify(string, string, int, Map&);
	string getPlayerName();
	void setPlayerName(string);
	vector<string> getCountries();
	void getCountryList();
	void addCountry(string);
	void removeCountry(string);
	Hand* getHand();
	Dice* getDice();
	void addPlayer(Player&);

};

static vector<Player*> allPlayers;