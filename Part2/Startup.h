#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Player.h"
#include "Map.h"
using namespace std;

class Startup
{
private:
	vector<Player> players;
	Map map;
public:
	void createPlayers();
	void setMap(Map);
	void setOrder();
	vector<Player> getPlayers();
	void Startup::assignCountries();
	Map getMap();
	void placeArmy();
	int numberOfArmies();
	void printArmies();
	void test();
};

