//Assignment 2_ Team 17                                     
//Comp 345_fall 2017   


#include "Player.h"

using namespace std;

//Player class methods

	//Default constructor
	Player::Player(std::string name) {
		playerName = name;
	}
	//parameterized constructor
	Player::Player(string player, Hand* hand, Dice* facility, char strategy) {
		playerName = player;
		myHand = hand;
		myDice = facility;
		if (strategy == 'a') {
			myStrategy = new StrategyAggressive();
		}
		else if (strategy == 'b') {
			myStrategy = new StrategyBenevolent();
		}
		else{
			myStrategy = new StrategyHuman();
		}
	}

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
		cout << "\nDisplaying collection of countries for " << playerName << ": ";
		if (myCountries.size() > 0) {
			cout << myCountries[0];
		}
		if (myCountries.size() > 1) {
			for (int i = 1; i < myCountries.size(); i++) {
				cout << ", " << myCountries[i];
			}
		}
		cout << endl;
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

	void Player::reinforce(Map& location) {
		myStrategy->reinforce(location, myCountries, myHand, playerName);
	}

	void Player::attack(Map& location) {
		myStrategy->attack(location, myCountries, myDice, playerName);
	}

	void Player::fortify(Map& location) {
		myStrategy->fortify(location, playerName, myCountries);
	}

	int Player::defend(string defending, Map& location) {
		return myStrategy->defend(defending, location, playerName);
	}
	string Player::setupCountryChoice(Map& location) {
		return myStrategy->setupCountryChoice(location, myCountries, playerName);
	}

	//reinforcement phase
	void StrategyHuman::reinforce(Map& site, vector<string> myCountries, Hand* myHand, string playerName) {
		//Number of armies is number of countries owned on the map, divided by 3
		int army = floor(static_cast<double>(myCountries.size()) / 3);

		if (army < 3){
			army = 3;
		}

		//Countries which are owned by player
		vector<Continent> theContinents = site.getContinent();
		//Check if all countries are a continent to give the continent value to player
		for (int i = 0; i<theContinents.size(); i++) {
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
				army += theContinents[i].getValue();
			}
		}


		//Exchange cards with armies If a player owns more than 5 cards
		do {
			if (myHand->getNumberInHand() > 5) {
				cout << "You own these cards: ";
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
						cerr << "Incorrect value, try agina" << endl;
						break;
					}
				}
				else if (n == 1){
					army += myHand->trade(n);
				}

			}
			else {
				break;
			}
		} while (true);

		//set number of armies to owned country
		while (army > 0){
			int numArmy;
			cout << "You have " << army << " armies to place" << endl;
			string theCountry = setupCountryChoice(site, myCountries, playerName);
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
				cout << theCountry << " now has " << site.getArmies(theCountry) <<" armies" << endl;
			}
			else {
				cerr << "Invalid something" << endl;
			}
		}
		
	}
	

	void StrategyHuman::attack(Map&location, vector<string>& myCountries, Dice* myDice, string playerName) {
		
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

			while (true) {
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
				}
			}

			if (location.getArmies(defending) <= 0) {
				cout << playerName << " has won the war over " << defending << endl;
				allPlayers[i]->removeCountry(defending);
				location.replaceOwner(defending, playerName);
				myCountries.push_back(defending);

				int number;
				do {
					cout << "How many troops are you sending to the new land: ";
					cin >> number;

					// MOVE ARMIES
					if (number > 0 && location.getArmies(attacking) > number) {
						location.removeArmies(attacking, number);
						location.addArmies(defending, number);
						break;
					}
					else {
						cerr << "Invalid number of armies, or not enough armies in " << attacking << endl;
					}

				} while (true);
			}
		} while (true);
	}

	void StrategyHuman::fortify(Map& location, string playerName, vector<string> myCountries) {
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
					break;
				}
				else {
					cerr << "Invalid number of armies, or not enough armies in " << sending << endl;
				}
			} while (true);
		}
	}
	//end of reinforce, attack, and fortify methods

	int StrategyHuman::defend(string defending, Map& location, string playerName) {
		cout << playerName << ", how many dice do you want to use in order to defend yourself: ";
		int numberOfArmies;
		cin >> numberOfArmies;
		return numberOfArmies;
	}

	string StrategyHuman::setupCountryChoice(Map& location, vector<string> myCountries, string playerName) {
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

//end of Player.cpp

// START OF AGGRESSIVE STRATEGY
	void StrategyAggressive::reinforce(Map& site, vector<string> myCountries, Hand* myHand, string playerName) {
		//Number of armies is number of countries owned on the map, divided by 3
		int army = floor(static_cast<double>(myCountries.size()) / 3);

		if (army < 3) {
			army = 3;
		}

		//Countries which are owned by player
		vector<Continent> theContinents = site.getContinent();
		//Check if all countries are a continent to give the continent value to player
		for (int i = 0; i<theContinents.size(); i++) {
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
				army += theContinents[i].getValue();
			}
		}

		bool choice = true;
		int tradeType = 1;

		//Exchange cards with armies If a player owns more than 5 cards
		do {
			if (myHand->getNumberInHand() > 5) {
				int n;
				//trade one kind of cards of different types
				cout << "Aggressive is trading cards ... ";
				if (choice) {
					n = 1;
				}
				else {
					n = 3;
				}
				int c;
				if (n == 3) {
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
						cerr << "Incorrect value, try agina" << endl;
						break;
					}

					if (tradeType == 1) {
						tradeType = 5;
					}
					else
					{
						tradeType = 10;
					}
				}
				else if (n == 1){
					army += myHand->trade(n);
				}
				// Choose other opiton
				bool choice = false;
			}
			else {
				break;
			}
		} while (true);

		//set number of armies to owned country
		while (army > 0) {
			int numArmy;
			cout << "Aggressive player has " << army << " armies to place" << endl;
			string theCountry = strongestCountry(site, myCountries);
			// put most populated in theCountry
			numArmy = army;
			site.addArmies(theCountry, numArmy);
			army -= numArmy;
			cout << theCountry << " now has " << site.getArmies(theCountry) << " armies" << endl;
		}
	}
	
	void StrategyAggressive::attack(Map& location, vector<string>& myCountries, Dice* myDice, string playerName) {

		do {
			string attacking = "none", defending = "none";
			bool action = false;
			attacking = strongestCountry(location, myCountries);
			if (location.getArmies(attacking) > 2) {
				vector<Node*> neighbors = location.getNode(attacking).getNeighbors();
				for (int i = 0; i < neighbors.size(); i++) {
					if (!location.checkOwner(playerName, neighbors[i]->getName())) {
						action = true;
						defending = neighbors[i]->getName();
						break;
					}
				}
			}
			if (!action) {
				cout << "Aggressive player couldnt attack this time" << endl;
				break;
			}

			cout << "Aggressive player will be attacking from "  << attacking << " with "<< location.getArmies(attacking) << " armies to "<< defending << " with " << location.getArmies(defending) << " armies" <<endl;

			int numberOfDice = location.getArmies(attacking);
			if (numberOfDice > 3) {
				numberOfDice = 3;
			}
			else {
				numberOfDice = numberOfDice - 1;
			}

			// ENEMY REPLY
			int i = 0;
			for (; i < allPlayers.size(); i++) {
				if (allPlayers[i]->getPlayerName() == location.getNode(defending).getCountry()->getPlayer()) {
					break;
				}
			}
			int numberOfDiceDefending;

			do {
				numberOfDiceDefending = allPlayers[i]->defend(defending, location);
				if (numberOfDiceDefending > 2 || numberOfDiceDefending < 1) {
					cerr << "Invalid number of dice " << defending << endl;
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
				}
			}

			cout << attacking << " with " << location.getArmies(attacking) << " armies to " << defending << " with " << location.getArmies(defending) << " armies" << endl;

			if (location.getArmies(defending) == 0) {
				cout << playerName << " has won the war over " << defending << endl;
				allPlayers[i]->removeCountry(defending);
				location.replaceOwner(defending, playerName);
				myCountries.push_back(defending);

				int number;
				do {
					number = location.getArmies(attacking) - 1;

					// MOVE ARMIES
					if (number > 0 && location.getArmies(attacking) > number) {
						location.removeArmies(attacking, number);
						location.addArmies(defending, number);
						cout << playerName << " has put " << location.getArmies(defending) << " armies in his new territory" << endl;
						break;
					}
					else {
						cerr << "Invalid number of armies, or not enough armies in " << attacking << endl;
					}

				} while (true);
			}
		} while (true);
	}

	
	void StrategyAggressive::fortify(Map& location, string playerName, vector<string> myCountries) {
		string receiving = strongestCountry(location, myCountries);
		vector<Node*> neighbors = location.getNode(receiving).getNeighbors();
		string sending = "none";
		for (int i = 0; i < neighbors.size(); i++) {
			if (neighbors[i]->getCountry()->getPlayer() == playerName && neighbors[i]->getCountry()->getArmies() > 1) {
				// if none selected
				if (sending == "none") {
					string sending = neighbors[i]->getName();
				}
				// if neighbor armies is more than previous neighbor
				else if (location.getArmies(sending) < neighbors[i]->getCountry()->getArmies()){
					string sending = neighbors[i]->getName();
				}
			}
		}

		// MOVE ARMIES
		if (sending != "none") {
			cout << "Aggressive player is fortitfying ... "<< endl;
			int number = location.getArmies(sending) - 1;
			if (number > 0 && location.getArmies(sending) > number) {
				location.removeArmies(sending, number);
				location.addArmies(receiving, number);
			}
			else {
				cerr << "Invalid number of armies, or not enough armies in " << sending << endl;
			}
		}
		else {
			cout << "Aggressive didnt fortify this turn" << endl;
		}
	}

	int StrategyAggressive::defend(string defending, Map& location, string playerName) {
		return 1;
	}

	string StrategyAggressive::setupCountryChoice(Map& location, vector<string> countries, string playerName) {
		string result = countries[0];
		location.getArmies(result);

		for (int i = 1; i < countries.size(); i++) {
			if (location.getArmies(result) > location.getArmies(countries[i])) {
				result = countries[i];
			}
		}

		return result;
	}

	string StrategyAggressive::strongestCountry(Map& location, vector<string> countries) {
		string result = countries[0];
		location.getArmies(result);

		for (int i = 1; i < countries.size(); i++) {
			if (location.getArmies(result) < location.getArmies(countries[i])) {
				result = countries[i];
			}
		}

		return result;
	}

// START OF BENVOLENT STRATEGY
	void StrategyBenevolent::reinforce(Map& site, vector<string> myCountries, Hand* myHand, string playerName) {
		//Number of armies is number of countries owned on the map, divided by 3
		int army = floor(static_cast<double>(myCountries.size()) / 3);

		if (army < 3) {
			army = 3;
		}

		//Countries which are owned by player
		vector<Continent> theContinents = site.getContinent();
		//Check if all countries are a continent to give the continent value to player
		for (int i = 0; i<theContinents.size(); i++) {
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
				army += theContinents[i].getValue();
			}
		}

		bool choice = true;
		int tradeType = 1;

		//Exchange cards with armies If a player owns more than 5 cards
		do {
			if (myHand->getNumberInHand() > 5) {
				int n;
				//trade one kind of cards of different types
				cout << "Benevolent is trading cards ... ";
				if (choice) {
					n = 1;
				}
				else {
					n = 3;
				}
				int c;
				if (n == 3) {
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
						cerr << "Incorrect value, try agina" << endl;
						break;
					}

					if (tradeType == 1) {
						tradeType = 5;
					}
					else
					{
						tradeType = 10;
					}
				}
				else if (n == 1) {
					army += myHand->trade(n);
				}
				// Choose other opiton
				bool choice = false;
			}
			else {
				break;
			}
		} while (true);

		cout << "Benevolent player has " << army << " armies to place" << endl;
		//set number of armies to owned country
		while (army > 0) {
			int numArmy;
			string theCountry = weakestCountry(site, myCountries);
			numArmy = 1;
			site.addArmies(theCountry, numArmy);
			army -= numArmy;
			cout << theCountry << " now has " << site.getArmies(theCountry) << " armies" << endl;
		}
	}

	void StrategyBenevolent::attack(Map& location, vector<string>& myCountries, Dice* myDice, string playerName) {
		cout << "Player is benevolent and decided not to attack" << endl;
	}

	void StrategyBenevolent::fortify(Map& location, string playerName, vector<string> myCountries) {
		string receiving = weakestCountry(location, myCountries);
		vector<Node*> neighbors = location.getNode(receiving).getNeighbors();
		string sending = "none";
		for (int i = 0; i < neighbors.size(); i++) {
			if (neighbors[i]->getCountry()->getPlayer() == playerName && neighbors[i]->getCountry()->getArmies() > 1) {
				// if none selected
				if (sending == "none") {
					string sending = neighbors[i]->getName();
				}
				// if neighbor armies is more than previous neighbor
				else if (location.getArmies(sending) < neighbors[i]->getCountry()->getArmies()) {
					string sending = neighbors[i]->getName();
				}
			}
		}

		// MOVE ARMIES
		if (sending != "none") {
			cout << "Benevolent player is fortitfying ... " << endl;
			int number = location.getArmies(sending) - 1;
			if (number > 0 && location.getArmies(sending) > number) {
				location.removeArmies(sending, number);
				location.addArmies(receiving, number);
			}
			else {
				cerr << "Invalid number of armies, or not enough armies in " << sending << endl;
			}
		}
		else {
			cout << "Benevolent did not fortify this turn" << endl;
		}
	}

	int StrategyBenevolent::defend(string defending, Map& location, string playerName) {
		int defenseNumber = location.getArmies(defending);
		if (defenseNumber > 2) {
			defenseNumber = 2;
		}
		return defenseNumber;
	}

	string StrategyBenevolent::setupCountryChoice(Map& location, vector<string> myCountries, string playerName) {
		cout << playerName << " is choosing a country to insert a troop ..." << endl;
		return weakestCountry(location, myCountries);
	}

	string StrategyBenevolent::weakestCountry(Map& location, vector<string> countries) {
		string result = countries[0];
		location.getArmies(result);

		for (int i = 1; i < countries.size(); i++) {
			if (location.getArmies(result) > location.getArmies(countries[i])) {
				result = countries[i];
			}
		}

		return result;
	}

