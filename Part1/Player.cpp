//Group 17:  Neven, Anahita, Felix, Betty
//Assignment 1: Part 4, Player
//September 27, 2017
//
//The following .cpp file will define classes and methods declared in Player.h file.
//The main object is the Player object;  each player contains Hand and DiceRollingFacility
//objects, as well as a list of countries that belong to them.  The Hand and DiceRollingFacility
//classes have also been created as place holders for the time being in order to demonstrate
//how the Player class will function.

#include "Player.h"
#include "stdafx.h"
#include <string>

using namespace std;

//Hand default constructor
//The hand object is empty for now
Hand::Hand() {
	cout << "\t\tEvoking constructor for new Hand object..." << endl;
};

//DiceRollingFacility default constructor
//The DiceRollingFacility is empty for now
DiceRollingFacility::DiceRollingFacility() {
	cout << "\t\tEvoking constructor for new DiceRollingFacility object..." << endl;
};

//Country object constructor
//This merely holds the name of the country for the time being
Country::Country(string country) {

	countryName = country;
	cout << "\t"<<country << " created successfully" << endl;
};

//get/set methods for Country class to obtain name
string Country::getCountryName() {
	return countryName;
};

void Country::setCountryName(string newName) {
	countryName = newName;
};
//end of get/set method

//Player class methods
	//Default constructor
	Player::Player(std::string name) {
		playerName = name;
		cout << "\tNew player " << playerName << " created successfully." << endl;
		cout << "\tCreating a new Hand for " << playerName << endl;
		*myHand = Hand();
		cout << "\tCreating a new DiceRollingFacility for..."<< playerName << endl;
		*myDice = DiceRollingFacility();
	}
	//parameterized constructor
	Player::Player(string player, Hand hand, DiceRollingFacility facility) {
		playerName = player;
		*myHand = hand;
		*myDice = facility;
	}


	//reinforce, attack and fortify methods
	//these will be implemended later, for now merely shows a message to show the player class contains these
	void Player::reinforce() {
		cout << "\t" << playerName << " is executing reinforce method (this message is a placeholder)" << endl;
	}

	void Player::attack() {
		cout<<"\t"<<playerName << " is executing attack method (this message is a placeholder)" << endl;
	}

	void Player::fortify() {
		cout << "\t" << playerName<< " is executing fortify method (this message is a placeholder)" << endl;
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
	vector<Country> Player::getCountries() {
		return myCountries;
	}

	//this prints the names of the countries owned by the player
	void Player::getCountryList() {
		cout << "\nDisplaying collection of countries for " << playerName << ": " << endl;
		for (int i = 0; i < myCountries.size(); i++) {
			cout << "\t" << myCountries.at(i).getCountryName() << endl;
		}
	}

	//For now, while this does return the hand object, the hand object contains nothing
	//So it will display a placeholder message
	Hand Player::getHand(){
		cout << "\tReturning hand for " << playerName << endl <<
			"\tThis message is just a placeholder for the time being..." << endl;;
		return *myHand;
	}


	//adds a country to the vector
	void Player::addCountry(Country addMe) {
		myCountries.push_back(addMe);
	}

	//returns the dice rolling faciliy
	//for now, while it does return an object, the object is empty, hence the placeholder message
	DiceRollingFacility Player::getDice() {
		cout << "\tReturning dice rolling facility object for " << playerName << endl <<
			"\tThis message is just a placeholder for the time being..." << endl;
		return *myDice;
	}

//end of Player.cpp

