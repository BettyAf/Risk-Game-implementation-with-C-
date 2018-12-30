/* Assignment 1-Part1(Map)-Fall 2017
Comp345- Team 17
*/
#pragma once
#include <iostream>
#include <string>
#include "Continent.h"

#include <list>

using namespace std;

class Country
{
private:
	string name;
	string player;
	Continent continent;


public:
	void setName(string);
	void setPlayer(string);
	string getName();
	string getPlayer();
	void setContinent(Continent);
	Continent getContinent();

};
