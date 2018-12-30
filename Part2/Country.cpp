#include "Country.h"
#include "Continent.h"
#include <string>
#include <list>
using namespace std;


void Country::setName(string newName){
	name = newName;
}


void Country::setPlayer(Player newPlayer){
	player = newPlayer;
}

string Country::getName() {
	return name;
}

Player Country::getPlayer() {
	return player;
}


void Country::setContinent(Continent newcontinent){
	continent = newcontinent;
}

Continent Country::getContinent(){
	return continent;
}

void Country::setNumberOfArmies(int n){
	numberOfArmies = n;
}
int Country::getNumberOfArmies(){
	return numberOfArmies;
}

