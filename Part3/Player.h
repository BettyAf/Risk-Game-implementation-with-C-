//Assignment 2_ Team 17                                     
//Comp 345_fall 2017    

#pragma once

#include <time.h>
#include "Map.h"
#include "DiceRollingFacility.h"
#include "Pack.h"


using namespace std;

class Strategy {
public:
	virtual void reinforce(Map&, vector<string>, Hand*, string) = 0;
	virtual void attack(Map&, vector<string>&, Dice*, string) = 0;
	virtual void fortify(Map&, string, vector<string>) = 0;
	virtual int defend(string, Map&, string) = 0;
	virtual string setupCountryChoice(Map&, vector<string>, string) = 0;
};

class StrategyAggressive : public Strategy {
private:

public:
	void reinforce(Map&, vector<string>, Hand*, string);
	void attack(Map&, vector<string>&, Dice*, string);
	void fortify(Map&, string, vector<string>);
	int defend(string, Map&, string);
	string setupCountryChoice(Map&, vector<string>, string);
	string strongestCountry(Map&, vector<string>);
};

class StrategyBenevolent : public Strategy {
private:

public:
	void reinforce(Map&, vector<string>, Hand*, string);
	void attack(Map&, vector<string>&, Dice*, string);
	void fortify(Map&, string, vector<string>);
	int defend(string, Map&, string);
	string setupCountryChoice(Map&, vector<string>, string);
	string weakestCountry(Map&, vector<string>);
};

class StrategyHuman : public Strategy {
private:

public:
	void reinforce(Map&, vector<string>, Hand*, string);
	void attack(Map&, vector<string>&, Dice*, string);
	void fortify(Map&, string, vector<string>);
	int defend(string, Map&, string);
	string setupCountryChoice(Map&, vector<string>, string);
};

// Player.h
class Player {
	//These are what the player class will contain
private:
	string playerName;
	vector<string> myCountries; //this will be a vectored array that map class returns
	Hand *myHand;
	Dice *myDice;
	Strategy *myStrategy;

	//Public methods to be used by the player class
public:
	Player(string);
	Player(string, Hand*, Dice*, char);
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
	int defend(string, Map&);
	string setupCountryChoice(Map&);

};

static vector<Player*> allPlayers;
