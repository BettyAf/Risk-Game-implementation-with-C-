#pragma once

#include "Observer.h"
#include "Player.h"



class BasicDecoratorObserver : public Observer{
public:
	Player* player;
		

	BasicDecoratorObserver(Player* p) : Observer(), player(p){
		player->attach(this);
	}
	~BasicDecoratorObserver() {
		player->detach(this);
	}

	int getTurn() {
		static int i = 0;
		i += 1;
		return i ;	
	}
	
	string display() {
		string s = "\n\n***Turn " + to_string(getTurn()) + "***";
		return s;
	}
	void update(string message) {
		cout << message << endl;
	}
	//Update changes of obervers
	void update() {
		cout << display();
	}

	
	void displayCards() {
		player->getHand()->showHand();
	}

	double percentOfCountry() {
		int numCountries = player->getCountries().size();
		double percentage = (static_cast<double>(numCountries) / 8) * 100;
		return percentage;
	}

	string conquerContinent(Map& theMap) {
		//Countries which are owned by player
		vector<Continent> theContinents = theMap.getContinent();
		string output;

		//Check if all countries are a continent to give the continent value to player
		for (int i = 0; i < theContinents.size(); i++) {
			vector<Node> temp = theContinents[i].getContries();
			int count = temp.size();
			for (int j = 0; j < temp.size(); j++) {
				bool check = false;
				for (int k = 0; k < player->getCountries().size(); k++) {
					if (temp[j].getName() == player->getCountries()[k]) {
						check = true;
						break;
					}
				}
				if (!check) {
					break;
				}
				else {
					count--;
				}
			}
			//give the continent to the player because he contains all contries in the continent
			if (count == 0) {
				output = player->getPlayerName() + " own all countries of " + theContinents[i].getName();
				counter++;
			}
			else
				output = "***" + player->getPlayerName() + " has owned no continent";
		}
		return output;
	}

	string loseContinent(Map& map) {
		string output;
		if (counter > 0 && conquerContinent(map) == "") {
			output == " but " + player->getPlayerName() + " loses control of the continent";
		}
		else
			output = "";
		return output;
	}


};
