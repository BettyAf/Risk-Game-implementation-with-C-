//Assignment 3_ Team 17                                     
//Comp 345_fall 2017   


#include "DiceRollingFacility.h"
#include "Pack.h"
#include "Map.h"
#include "MapLoader.h"
#include "Player.h"
#include "ShowStatistics.h"
#include <ctime>
#include <iostream>
using namespace std;

int main()
{
	Map myMap;
	MapLoader load("world.map", myMap);
	
	//Initialize players
	Hand* myHand = new Hand;
	srand(time(NULL));
	Dice* myDice = new Dice;
	Player player;
	Player myPlayer1("Betty", myHand, myDice);
	Player* player1 = &myPlayer1;

	Hand* otherHand = new Hand;
	srand(time(NULL));
	Dice* otherDice = new Dice;
	Player myPlayer2("Anna ", otherHand, otherDice);
	Player* player2 = &myPlayer2;

	Hand* theHand = new Hand;
	srand(time(NULL));
	Dice* theDice = new Dice;
	Player myPlayer3("Felix", theHand, theDice);
	Player* player3 = &myPlayer3;

	player.addPlayer(myPlayer1);
	myPlayer1.addPlayer(myPlayer2);
	myPlayer2.addPlayer(myPlayer3);
	
	//add Observers
	ShowStatistics* statics1 = new ShowStatistics (player1);
	ShowStatistics* statics2 = new ShowStatistics(player2);
	ShowStatistics* statics3 = new ShowStatistics(player3);
	
	
	//test general
	myMap.replaceOwner(myPlayer1.getPlayerName(), "Venezuala");
	myPlayer1.addCountry("Venezuala");
	myMap.replaceOwner(myPlayer1.getPlayerName(), "Peru");
	myPlayer1.addCountry("Peru");
	myMap.replaceOwner(myPlayer1.getPlayerName(), "Argentina");
	myPlayer1.addCountry("Argentina");
	myPlayer1.getCountries();
	

	myMap.replaceOwner(myPlayer2.getPlayerName(), "Alaska");
	myPlayer2.addCountry("Alaska");
	myMap.replaceOwner(myPlayer2.getPlayerName(), "Brazil");
	myPlayer2.addCountry("Brazil");
	myMap.replaceOwner(myPlayer2.getPlayerName(), "Alberta");
	myPlayer2.addCountry("Alberta");
	myMap.replaceOwner(myPlayer2.getPlayerName(), "India");
	myPlayer2.addCountry("India");
	myPlayer2.getCountries();
	

	myMap.replaceOwner(myPlayer3.getPlayerName(), "Madagascar");
	myPlayer3.addCountry("Madagascar");
	myMap.replaceOwner(myPlayer3.getPlayerName(), "Congo");
	myPlayer3.addCountry("Congo");
	myMap.replaceOwner(myPlayer3.getPlayerName(), "Egypt");
	myPlayer3.addCountry("Egypt");
	myMap.replaceOwner(myPlayer3.getPlayerName(), "China");
	myPlayer3.addCountry("China");
	myPlayer3.getCountries();
	


	myHand->addToHand(infantry);
	myHand->addToHand(infantry);
	myHand->addToHand(cavalry);
	myHand->addToHand(cavalry);
	myHand->addToHand(artillery);
	myHand->addToHand(artillery);

	
	otherHand->addToHand(infantry);
	otherHand->addToHand(cavalry);
	otherHand->addToHand(cavalry);
	otherHand->addToHand(cavalry);
	otherHand->addToHand(artillery);
	otherHand->addToHand(artillery);

	
	theHand->addToHand(infantry);
	theHand->addToHand(infantry);
	theHand->addToHand(infantry);
	theHand->addToHand(cavalry);
	theHand->addToHand(cavalry);
	theHand->addToHand(artillery);

	start(myMap);
	
	
}