/* Assignment 1-Part1(Map)-Fall 2017
Comp345- Team 17
*/
#include "stdafx.h"
#include "Country.h"
#include "Continent.h"
#include <string>
#include "Edge.h"
#include <list>
using namespace std;


void Country::setName(string newName){
	name = newName;
}


void Country::setPlayer(string newPlayer){
	player = newPlayer;
}

string Country::getName() {
	return name;
}

string Country::getPlayer() {
	return player;
}


void Country::setContinent(Continent newcontinent){
	continent = newcontinent;
}

Continent Country::getContinent(){
	return continent;
}


