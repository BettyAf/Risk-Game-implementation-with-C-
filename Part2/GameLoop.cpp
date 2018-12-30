/* Assignment2_COMP345_Team 17*/
#include <iostream>
#include <string>
#include <vector>
#include "Startup.h"
#include "GameLoop.h"
using namespace std;
 
void GameLoop::setStartUp(Startup myStartUp){
	startup = myStartUp;
}

/* reinforcement, attack and fortification methods*/
void GameLoop::reinforcement(Player p){
	cout << p.getName() << " reinforced !" << endl;
}
void GameLoop::attack(Player p){
	cout << p.getName() << " attacked !" << endl;
}

void GameLoop::fortification(Player p){
	cout << p.getName() << " fortificated !" << endl;
}

/* the game finished when all countries belong to one player*/
bool GameLoop::gameFinished(){
	vector <Country> countries = startup.getMap().getCounries();
	string playerName = countries[0].getPlayer().getName();
	bool thereIsOnePlayer = true;
	for (vector<Country>::size_type i = 1; i != countries.size(); ++i){
		if (countries[i].getPlayer().getName() != playerName){
			thereIsOnePlayer = false;
			return thereIsOnePlayer;
		}
	}
	return thereIsOnePlayer;
}


void GameLoop::dummyFinish(){
	vector <Country> countries = startup.getMap().getCounries();
	Player player = countries[0].getPlayer();
	for (vector<Country>::size_type i = 1; i != countries.size(); ++i){
		countries[i].setPlayer(player);
	}
	Map map;
	map = startup.getMap();
	map.setCountries(countries);
	startup.setMap(map);
}

/* start the game 
assign armies to countries and call reinforcement, attack and fortification methods

*/
void GameLoop::startTheGame(){

	vector<Player> players = startup.getPlayers();
	int i = 0;

	while (!gameFinished()){
		int index = i % players.size();
		cout << endl << "Player " << players[index].getName() << " round :" << endl;
		reinforcement(players[index]);
		attack(players[index]);
		fortification(players[index]);
		i++;

		//dummy finish after 10 iteration
		if (i > 9){
			dummyFinish();
			cout << endl << endl << "Game Finsihed !" << endl;
			for (vector<Country>::size_type j = 1; j != startup.getMap().getCounries().size(); ++j){
				cout << startup.getMap().getCounries()[j].getName() << "'s player is " << startup.getMap().getCounries()[j].getPlayer().getName() << endl;
			}
			cout << endl << "Player " << startup.getMap().getCounries()[0].getPlayer().getName() << " Won !" << endl;
		}
	}

}