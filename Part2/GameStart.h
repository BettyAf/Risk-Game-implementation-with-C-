#pragma once;

#include <iostream>
#include <fstream>
#include "Map.h"
#include "Player.h"
#include "MapLoader.h"
#include "DiceRollingFacility.h"
#include <string>

using namespace std;

class GameStart
{
private:
	int numberPlayer;

public:
	GameStart();

	string selectMap();
	void setPlayers();
	int getPalyer();
	int loadMap(MapLoader&);
	void setDeck();
};




