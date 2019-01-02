/* Assignment2_COMP345_Team 17*/
#include <iostream>
#include <string>
#include <vector>
#include "GameLoop.h"
#include "BasicDecoratorObserver.h"
#include "ContinentControlObserverDecorator.h"
#include "PlayerDominationObserverDecorator.h"
#include "PlayerHandsObserverDecorator.h"
using namespace std;

/* the game finished when all countries belong to one player*/
bool GameLoop::gameFinished(Map& location) {
	vector<Node> nodes = location.getNodes();
	string playerName = nodes[0].getCountry()->getPlayer();

	for (int i = 1; i < nodes.size(); i++) {
		if (location.checkOwner(playerName, nodes[i].getName())) {
			return false;
		}
	}
	return true;
}

//start the game
void GameLoop::startTheGame(vector<Player*> players, Map& location) {
	int i = 0;
	int count1 = 0, count2 = 0, count3 = 0;

	BasicDecoratorObserver* decoratedPlayer = new BasicDecoratorObserver(players[0]);
	//while game is not finished do the loop
	while (!gameFinished(location)) {
		int index = i % players.size();
		//notify the turn
		if (index == 0) {
			players[index]->addBaseDecorator();
		}

		if (players[index]->getCountries().size() > 0) {
			//let's user to choose the decorator
			int s = players[index]->addDecorator(location);
			
			
			if (s == 1) {
				//notify the player domination
				decoratedPlayer = new PlayerDominationDecorator(decoratedPlayer);
				players[index]->addBaseDecorator();
				if (count1 > 0) {
					cout << "You have already added this decorator" << endl;
					break;
				}
				count1++;
			}
			else if (s == 2) {
				decoratedPlayer = new PlayerHandDecorator(decoratedPlayer);
				players[index]->addBaseDecorator();

				if (count2 > 0) {
					cout << "You have already added this decorator" << endl;
					break;
				}
				count2++;
			}
			else if (s == 3) {
				decoratedPlayer = new ContinentControlDecorator(decoratedPlayer, location);
				players[index]->addBaseDecorator();
				if (count3 > 0) {
					cout << "You have already added this decorator" << endl;
					break;
				}
				count3++;
			}

			
				cout << endl << "Player " << players[index]->getPlayerName() << " round :" << endl;

				players[index]->reinforce(location);
				players[index]->attack(location);
				players[index]->fortify(location);
				i++;
		}
	}

}
