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
	Player::Player(string player, Hand* hand, Dice* facility) {
		playerName = player;
		myHand = hand;
		myDice = facility;
	}

	//reinforcement phase
	void Player::reinforce(Map& site) {
		//Number of armies is number of countries owned on the map, divided by 3
		int army = floor(static_cast<double>(myCountries.size()) / 3);

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
						break;
					}
				}
				else {
					army += myHand->trade(n);
				}

			}
			else {
				break;
			}
		} while (true);

		//set number of armies to owned country
		while (army != 0){
			int numArmy;
			string theCountry;
			cout << "You have " << army << " armies to place" << endl;
			cout << "Enter the name of a country to put in armies: ";
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
				cout << theCountry << " now has " << site.getArmies(theCountry) <<" armies" << endl;
			}
			else {
				cerr << "Invalid something" << endl;
			}
		}
		
	}
	

	bool Player::attack(string attacking, string defending, int numberOfDice, Map&location) {
		cout << "It will implement later" << endl;
		return true;
	}

	bool Player::fortify(string sending, string receiving, int number, Map& location) {
		cout << "It will implement later" << endl;
		return true;
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
	Hand* Player::getHand(){
		return myHand;
	}


	//adds a country to the vector
	void Player::addCountry(string addMe) {
		myCountries.push_back(addMe);
	}

	void Player::removeCountry(string removeMe) {
		for (int i = 0; i < myCountries.size(); i++){
			if (myCountries[i] == removeMe){
				myCountries.erase(myCountries.begin()+i);
				break;
			}
		}
	}

	//returns the dice rolling faciliy
	//for now, while it does return an object, the object is empty, hence the placeholder message
	Dice* Player::getDice() {
		return myDice;
	}

	void Player::addPlayer(Player& player) {
		allPlayers.push_back(&player);
	}

//end of Player.cpp

