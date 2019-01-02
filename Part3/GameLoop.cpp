/* Assignment2_COMP345_Team 17*/
#include <iostream>
#include <string>
#include <vector>
#include "Map.h"
#include "Player.h"
#include "GameLoop.h"
using namespace std;

/* the game finished when all countries belong to one player*/
bool GameLoop::gameFinished(Map& location){
	vector<Node> nodes = location.getNodes();
	string playerName = nodes[0].getCountry()->getPlayer();

	for (int i = 1; i < nodes.size(); ++i){
		if (nodes[i].getCountry()->getPlayer() != playerName) {
			return false;
		}
	}
	return true;
}

void GameLoop::startTheGame(vector<Player*> players, Map& location){

	int i = 0;

	while (!gameFinished(location)){
		int index = i % players.size();
		cout << endl << "Player " << players[index]->getPlayerName() << " round :" << endl;
		
		players[index]->reinforce(location);
		players[index]->attack(location);
		players[index]->fortify(location);
		i++;
	}

}