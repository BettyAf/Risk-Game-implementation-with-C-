#include "stdafx.h"
#include "player.h"
#include "Map.h"
#include "MapLoader.h"

int main() {
	Map myMap;
	MapLoader load = MapLoader ("World.map", myMap);
	//Hand* myHand = new Hand;
	//Dice* myDice = new Dice;
	//Player myPlayer1("Betty", myHand, myDice);
	

	//myPlayer1.reinforce(load, myMap);




	return 0;
}