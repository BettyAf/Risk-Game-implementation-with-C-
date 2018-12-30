#pragma once
#include <iostream>
#include <string>
#include "Continent.h"
#include "Player.h"
#include <list>

using namespace std; 

class Country
{
private:
	string name;
	Player player;
	Continent continent;
	int numberOfArmies;

public:
		
	void setName(string);
	void setPlayer(Player);
	string getName();
	Player getPlayer();
	void setContinent(Continent);
	Continent getContinent();
	void setNumberOfArmies(int);
	int getNumberOfArmies();
};

