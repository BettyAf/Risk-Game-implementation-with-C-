//Assignment 2_ Team 17                                     
//Comp 345_fall 2017   

#include "Map.h"
#include "Player.h"
#include "Subject.h"
#include "BasicDecoratorObserver.h"
#include "ContinentControlObserverDecorator.h"
#include "PlayerDominationObserverDecorator.h"
#include "PlayerHandsObserverDecorator.h"
using namespace std;

//Player class methods
//test observer
void Player::observer_test() {
	notify("This is a test for observer, if you see this message it means there is an observer attached to players");
}
Player::Player() : Subject(){
}

//Default constructor
Player::Player(std::string name) : Subject(), playerName(name) {
}
//parameterized constructor
Player::Player(string player, Hand* hand, Dice* facility) : Subject(), playerName(player), myHand(hand), myDice(facility) {
}

//reinforcement phase
void Player::reinforce(Map& site) {

	//Number of armies is number of countries owned on the map, divided by 3
	int army;
	int tempArmy = floor(static_cast<double>(myCountries.size()) / 3);
	if (tempArmy < 3)
		army = 3;
	else
		army = tempArmy;


	//Countries which are owned by player
	vector<Continent> theContinents = site.getContinent();
	
	//Check if all countries are a continent to give the continent value to player
	cout << "You own countries: " << displayCountries() << endl;
	cout <<"Reinforcement phase is started. You get " << army << " soldiers" << endl;
	for (int i = 0; i<theContinents.size(); i++) {
		if (bonus > 0) {
			i++;
			continue;
		}
		vector<Node> temp = theContinents[i].getContries();
		int count = temp.size();
		for (int j = 0; j < temp.size(); j++) {
			bool check = false;
			for (int k = 0; k < myCountries.size(); k++) {
				if (temp[j].getName() == myCountries[k]) {
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
			cout << "You own all countries of " << theContinents[i].getName() << " continent , so you will get " <<
				theContinents[i].getValue() << " soldiers as bonus." << endl;
			army += theContinents[i].getValue();
			bonus++;								
		}
	}


	//Exchange cards with armies If a player owns more than 5 cards
	do {
		if (myHand->getNumberInHand() > 5) {
			cout << "You have more than 5 cards; you own these cards: ";
			myHand->showHand();
			int n;
			//trade one kind of cards of different types
			cout << "Do you want to trade one kind or a set of cards (1 or 3): ";
			cin >> n;
			int c;

			if (n == 3) {
				cout << "Which type of cards do you want to trade? (1 infantry, 5 cavalry, 10 artillery): ";
				cin >> c;
				switch (c)
				{
				case 1:
					army += myHand->trade(n, infantry);
					break;
				case 5:
					army += myHand->trade(n, cavalry);
					break;
				case 10:
					army += myHand->trade(n, artillery);
					break;
				default:
					break;
				}
			}
			else if (n == 1) {
				army += myHand->trade(n);
			}
			else {
				cout << "Not valid entery" << endl;
				break;
			}

		}
		else {
			break;
		}
	} while (true);

	//set number of armies to owned country
	while (army != 0) {
		int numArmy;
		string theCountry;
		cout << "You have " << army << " armies to place" << endl;
		cout << "Enter the name of a country to put armies: ";
		cin >> theCountry;
		cout << "Enter the number of armies you desired to place in the country: ";
		cin >> numArmy;

		if (!site.checkOwner(playerName, theCountry)) {
			cerr << "Player is not owner of " << theCountry << endl;
		}
		else if (numArmy > army) {
			cerr << "Not enough armies" << endl;
		}
		// MOVE ARMIES
		else if (numArmy > 0) {
			site.addArmies(theCountry, numArmy);
			army -= numArmy;
			cout << theCountry << " now has " << site.getArmies(theCountry) << " armies" << endl;
		}
		else {
			cerr << "Invalid something" << endl;
		}
	}

}

//Attack
void Player::attack(Map&location) {

	bool action;
	do {
		cout << "Do you want to attack(1 or 0): ";
		cin >> action;
		if (!action)
			break;

		string attacking, defending;
		int numberOfDice;


		// ATTACKERS CHOICES
		while (true) {
			while (true) {
				int input;
				cout << "\nDisplaying collection of countries for " << playerName << ": ";
				if (myCountries.size() > 0) {
					cout << "0 ->" << myCountries[0] << "(" << location.getArmies(myCountries[0]) << ")";
				}
				if (myCountries.size() > 1) {
					for (int i = 1; i < myCountries.size(); i++) {
						cout << ", " << i << " -> " << myCountries[i] << "(" << location.getArmies(myCountries[i]) << ")";
					}
				}
				cout << endl;
				cout << "Input Attacking Country: ";
				cin >> input;
				attacking = myCountries[input];

				cout << "\nDisplaying neigbors of inputed country: ";
				vector<Node*> neighbors = location.getNode(attacking).getNeighbors();
				if (neighbors.size() > 0) {
					if (!location.checkOwner(playerName, neighbors[0]->getName())) {
						cout << "0 -> " << neighbors[0]->getName() << "(" << location.getArmies(neighbors[0]->getName()) << ")";;
					}
				}
				for (int i = 1; i < neighbors.size(); i++) {
					if (!location.checkOwner(playerName, neighbors[0]->getName())) {
						cout << ", " << i << " -> " << neighbors[i]->getName() << "(" << location.getArmies(neighbors[i]->getName()) << ")";
					}
				}
				cout << endl;
				cout << "Input Defending Country: ";
				cin >> input;
				defending = neighbors[input]->getName();

				if (!location.checkOwner(playerName, attacking)) {
					cerr << "Player is not owner of " << attacking << endl;
				}
				else if (location.checkOwner(playerName, defending) || location.checkOwner("none", defending)) {
					cerr << "Player is owner of " << defending << " or there are no owner of " << defending << endl;
				}
				else {
					break;
				}
			}

			if (location.checkNeigbor(attacking, defending)) {
				break;
			}
			else {
				cerr << "Countries are not neighbors try again" << endl;
			}
		}
		// get number of dice
		while (true) {
			cout << "Attacking country " << attacking << " has " << location.getArmies(attacking) << " armies." << endl;
			cout << "Defending country " << defending << " has " << location.getArmies(defending) << " armies." << endl;
			cout << "Input number of dice to use: ";
			cin >> numberOfDice;
			if (numberOfDice > 3 || numberOfDice < 1) {
				cerr << "Invalid number of dice " << attacking << endl;
			}
			else if (location.getArmies(attacking) < 2 || location.getArmies(attacking) < numberOfDice) {
				cerr << "Not enough armies in " << attacking << endl;
			}
			else {
				break;
			}
		}


		// ENEMY REPLY
		int i = 0;
		for (; i < allPlayers.size(); i++) {
			if (allPlayers[i]->getPlayerName() == location.getNode(defending).getCountry()->getPlayer()) {
				break;
			}
		}
		int numberOfDiceDefending;
		//get number of dice of defender
		do {
			numberOfDiceDefending = allPlayers[i]->defend(defending, location);
			if (numberOfDiceDefending > 2 || numberOfDiceDefending < 1) {
				cerr << "Invalid number of dice " << attacking << endl;
			}
			else if (numberOfDiceDefending > location.getArmies(defending)) {
				cerr << "Not enough armies in " << defending << endl;
			}
			else {
				break;
			}
		} while (true);

		//DICE FIGHTS
		vector<int> attack;
		for (int j = 0; j < numberOfDice; j++) {
			attack.push_back(myDice->diceRoll());
			cout << "Attack rolled: " << attack.back() << endl;
		}
		sort(attack.begin(), attack.begin() + numberOfDice);
		vector<int> defend;
		for (int j = 0; j < numberOfDiceDefending; j++) {
			defend.push_back(allPlayers[i]->getDice()->diceRoll());
			cout << "Defense rolled: " << defend.back() << endl;
		}
		sort(defend.begin(), defend.begin() + numberOfDiceDefending);

		cout << "Attack rolled: " << attack.back() << " Defense Rolled: " << defend.back() << endl;
		if (attack.back() > defend.back()) {
			cout << "Attack won" << endl;
			location.removeArmies(defending, 1);
			attack.pop_back();
			defend.pop_back();
		}
		else {
			cout << "Defense won" << endl;
			location.removeArmies(attacking, 1);
			attack.pop_back();
			defend.pop_back();
		}

		if (numberOfDice > 1 && numberOfDiceDefending > 1) {
			cout << "Attack rolled: " << attack.back() << " Defense Rolled: " << defend.back() << endl;
			if (attack.back() > defend.back()) {
				cout << "Attack won" << endl;
				location.removeArmies(defending, 1);
				attack.pop_back();
				defend.pop_back();
			}
			else {
				cout << "Defense won" << endl;
				location.removeArmies(attacking, 1);
				attack.pop_back();
				defend.pop_back();
				cout << "Now " << attacking << " owns " << location.getArmies(attacking) << " armies." << endl;
				cout << "Now " << defending << " owns " << location.getArmies(defending) << " armies." << endl;
			}
		}
		//attacker will get the country of defender if defender loose dice fight
		if (location.getArmies(defending) <= 0) {
			cout << playerName << " has won the war over " << defending << endl;
			allPlayers[i]->removeCountry(defending);
			location.replaceOwner(playerName, defending);
			addCountry(defending);
			gameDeck = new Deck(location.getNumberOfNodes());
			gameDeck->Draw(myHand);
			
			int number;
			do {
				cout << "\nHow many troops are you sending to the new land: ";
				cin >> number;

				// MOVE ARMIES
				if (number > 0 && location.getArmies(attacking) > number) {
					location.removeArmies(attacking, number);
					location.addArmies(defending, number);
					cout << "Now " << attacking << " owns " << location.getArmies(attacking) << " armies." << endl;
					cout << "Now " << defending << " owns " << location.getArmies(defending) << " armies." << endl;
					break;
				}
				else {
					cerr << "Invalid number of armies, or not enough armies in " << attacking << endl;
				}

			} while (true);
		}
	} while (true);
}

//fortify 
void Player::fortify(Map& location) {
	bool action;
	cout << "Do you want to fortify(1 or 0): ";
	cin >> action;

	if (action) {
		string sending, receiving;
		int number;

		while (true) {
			do {
				int input;
				cout << "\nDisplaying collection of countries for " << playerName << ": ";
				if (myCountries.size() > 0) {
					cout << "0 ->" << myCountries[0] << "(" << location.getArmies(myCountries[0]) << ")";
				}
				for (int i = 1; i < myCountries.size(); i++) {
					cout << ", " << i << " -> " << myCountries[i] << "(" << location.getArmies(myCountries[i]) << ")";
				}

				cout << "Input sending Country: ";
				cin >> input;
				sending = myCountries[input];
				if (!location.checkOwner(playerName, sending)) {
					cerr << "Player is not owner of " << sending << endl;
				}
				cout << "\nDisplaying neigbors of selected countries: ";
				vector<Node*> nodes = location.getNode(sending).getNeighbors();
				if (nodes.size() > 0) {
					if (nodes[0]->getCountry()->getPlayer() == playerName) {
						cout << "0 ->" << nodes[0]->getName() << "(" << location.getArmies(nodes[0]->getName()) << ")";
					}
				}
				for (int i = 1; i < nodes.size(); i++) {
					if (nodes[0]->getCountry()->getPlayer() == playerName) {
						cout << ", " << i << " -> " << nodes[i]->getName() << "(" << location.getArmies(nodes[i]->getName()) << ")";
					}
				}

				cout << "Input receiving Country: ";
				cin >> input;
				receiving = nodes[input]->getName();
				if (!location.checkOwner(playerName, sending)) {
					cerr << "Player is not owner of " << sending << endl;
				}
				else if (!location.checkOwner(playerName, receiving)) {
					cerr << "Player is not owner of " << receiving << endl;
					break;
				}
				else {
					break;
				}
			} while (true);

			if (location.checkNeigbor(sending, receiving)) {
				break;
			}
			else {
				cerr << "Countries are not neighbors try again" << endl;
			}
		}

		// MOVE ARMIES
		do {
			cout << "Input number of armies to move: ";
			cin >> number;
			if (number > 0 && number < location.getArmies(sending)) {
				location.removeArmies(sending, number);
				location.addArmies(receiving, number);
				cout << "Now " << sending << " has " << location.getArmies(sending) << " armies." << endl;
				cout << "Now " << receiving << " has " << location.getArmies(receiving) << " armies." << endl;
				break;
			}
			else {
				cerr << "Invalid number of armies, or not enough armies in " << sending << endl;
			}
		} while (true);
	} 
}
//end of reinforce, attack, and fortify methods

//get/set methods for player
string Player::getPlayerName() {
	return playerName;
}

void Player::setPlayerName(string newName) {
	playerName = newName;
}

//This will return the actual vector itself, while the method below prints the names to display
vector<string> Player::getCountries() {
	return myCountries;
}

//this prints the names of the countries owned by the player
void Player::getCountryList() {
	cout << "\nDisplaying collection of countries for " << playerName << ": " << endl;
	for (int i = 0; i < myCountries.size(); i++) {
		cout << "\t" << myCountries[i] << endl;
	}
}

//For now, while this does return the hand object, the hand object contains nothing
//So it will display a placeholder message
Hand* Player::getHand() {
	return myHand;
}


//adds a country to the vector
void Player::addCountry(string addMe) {
	myCountries.push_back(addMe);
}

void Player::removeCountry(string removeMe) {
	for (int i = 0; i < myCountries.size(); i++) {
		if (myCountries[i] == removeMe) {
			myCountries.erase(myCountries.begin() + i);
			break;
		}
	}
}

//returns the dice rolling faciliy
//for now, while it does return an object, the object is empty, hence the placeholder message
Dice* Player::getDice() {
	return myDice;
}

void Player::addPlayer(Player* player) {
	allPlayers.push_back(player);
}

//Show countries which are owned by the player
string Player::displayCountries() {
	string c = "";
	for (int i = 0; i < myCountries.size() - 1; i++) {
		c = c + myCountries[i] + ", ";
	}
	c = c + myCountries[myCountries.size() - 1] + ".";
	return c;
}

//defender define number of dice
int Player::defend(string defending, Map& location) {
	cout << playerName << ", how many dice do you want to use in order to defend yourself: ";
	int numberOfArmies;
	cin >> numberOfArmies;
	return numberOfArmies;
}


string Player::setupCountryChoice(Map& location) {
	int sending;
	do {
		cout << "\nDisplaying collection of countries for " << playerName << ": ";
		if (myCountries.size() > 0) {
			cout << "0 ->" << myCountries[0] << "(" << location.getArmies(myCountries[0]) << ")";
		}
		if (myCountries.size() > 1) {
			for (int i = 1; i < myCountries.size(); i++) {
				cout << ", " << i << " -> " << myCountries[i] << "(" << location.getArmies(myCountries[i]) << ")";
			}
		}
		cout << endl;
		cout << playerName << " select an owned country to place army(ies): ";
		cin >> sending;

		if (sending < myCountries.size()) {
			break;
		}
		else {
			cerr << "Invalid number, try again" << endl;
		}

	} while (true);
	return myCountries[sending];
}



void Player::addBaseDecorator() {
	notify();
	
}

int Player::addDecorator(Map& location) {
	bool action;
	int s;
	do {
		cout << "\nDo you want to add a decorator (1 or 0)? ";
		cin >> action;
		if (!action)
			break;
		do {
			cout << "Dispalying collection of decorators: " << endl;
			cout << "1 -> Player Domination Observer Decorator" << endl;
			cout << "2 -> Player Hands Observer Decorator" << endl;
			cout << "3 -> Continent Control Observer Decorator" << endl;
			cout << "Select a decorator to add: ";
			cin >> s;

			if (s != 1 && s != 2 && s != 3) {
				cout << "Invalid input" << endl;
			}
			else
				break;
		} while (true);
		return s;
	} while (true);
	
}
void Player::removeDecorator(Map& location) {

}
