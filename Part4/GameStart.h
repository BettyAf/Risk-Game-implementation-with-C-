#pragma once;

#include <iostream>
#include <fstream>
#include "Map.h"
#include "Player.h"
#include "MapLoader.h"
#include "DiceRollingFacility.h"
#include <string>

using namespace std;

class Start
{
private:
	vector<Player*> players;
	Deck* gameDeck;
public:
	Start(Map& location);
	void Startup(Map& location);
	vector<Player*> getPlayers();
	Deck* getDeck();
};



