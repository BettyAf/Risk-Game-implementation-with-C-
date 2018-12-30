//Group 17:  Neven, Anahita, Felix, Betty
//Assignment 1:Part 4, Player
//September 27, 2017
//
//This is the Player.h file while defines everything needed to create a Player object.
//This files also defines Hand, DiceRollingFacility, and Country objects, which the Player
//object uses.  For now, these are empty, but they will be taken from the other parts
//of the project.

#ifndef PLAYER_H
#define PLAYER_H
#pragma once

#include "targetver.h"
#include "stdafx.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//Hand class
class Hand {
public:
	Hand();
};

//DiceRollingFacility class
class DiceRollingFacility {
public:
	DiceRollingFacility();
};

//Country class (contains country name)
class Country {
private:
	string countryName;
public:
	Country(string);
	string getCountryName();
	void setCountryName(string);
};

//Player class
class Player {

	//These are what the player class will contain
private:
	string playerName;
	vector<Country> myCountries; //this will be a vectored array that map class returns
	Hand *myHand;
	DiceRollingFacility *myDice;

	//Public methods to be used by the player class
public:
	Player(string);
	Player(string, Hand, DiceRollingFacility);
	void reinforce(); //This will be implemented at a later date
	void attack();    //This will be implemented at a later date
	void fortify();   //This will be implemented at a later date
	string getPlayerName();
	void setPlayerName(string);
	vector<Country> getCountries();
	void getCountryList();
	void addCountry(Country);
	Hand getHand();
	DiceRollingFacility getDice();

};
#endif

//end of Player.h