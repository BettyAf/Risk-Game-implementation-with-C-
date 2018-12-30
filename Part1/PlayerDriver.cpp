//Group 17:  Neven, Anahita, Felix, Betty
//Assignment 1: Part 4, Player
//September 27, 2017
//
//The following program is a driver that demonstrates how the Player object will function.

#include "Player.h"
#include "stdafx.h"
#include <iostream>
using namespace std;

//The pause method below is a helper method that simply prints a message, whiile allowing the
//main code to look a little cleaner...
void pause() {
	cout << "------------------------------------------" << endl;
	system("PAUSE");
	cout << "------------------------------------------" << endl;
};

//Driver method
int main() {

	//i.  Introductory message for driver
	cout << "------------------------------" << endl << "Part 4:  Player Driver" << endl << "------------------------------" << endl;
	cout << "The Player object creates a risk player which has the following features: a collection of countries, " << endl
		<< "a hand of Risk cards, and their own Dice Rolling Facility.  The player class will also implement the" << endl
		<< "the following methods:  reinforce(), attack(), and fortify().  Placeholders have been created for the" << endl
		<< "purposes of the driver to demonstrate that the player does indeed contain these objects/methods..." << endl;
	pause();

	//ii.  Creating the player object
	cout << "Creating new player..." << endl;
	cout << "------------------------------------------" << endl;
	Player Neven("Neven");
	pause();

	//iii.  Creating new countries that can be given to the player
	cout <<"Creating new countries.."<<endl;
	cout << "------------------------------------------" << endl;

	Country Canada("Canada"), America("America"), Mexico("Mexico"), Denmark("Denmark"), Argentina("Argentina"),
		Brazil("Brazil"), Peru("Peru"), France("France"), England("England"), Germany("Germany");

	pause();

	//iv.  Adding the countries to the player's list of countries (stored as a vector)
	cout << "Allocating countries to player..." << endl<<endl;

	Neven.addCountry(Canada);
	Neven.addCountry(America);
	Neven.addCountry(Mexico);
	Neven.addCountry(Denmark);
	Neven.addCountry(Argentina);
	Neven.addCountry(Peru);
	Neven.addCountry(France);
	Neven.addCountry(England);
	Neven.addCountry(Germany);
	cout << "Allocation complete, displaying Player's collection of countries..." << endl;

	//v.  Displaying the vector of countries
	Neven.getCountryList();
	pause();

	//vi.  Displaying the Dice Rolling Facility object
	cout <<"Displaying Dice Rolling Facility object..."<<endl;
	Neven.getDice();

	pause();

	//vii.  Displaying Hand Object
	cout <<"Displaying Card Hand object..." << endl;
	Neven.getHand();

	pause();

	//viii.  Displaying reinforce, attack, and fortify methods (to be implemented later
	cout <<"Displaying reinforce, attack, and fortify methods for " <<Neven.getPlayerName()<< endl;

	Neven.reinforce();
	Neven.attack();
	Neven.fortify();
	
	pause();

	//ix.  End message
	cout << "This is the end of the Player driver.  The driver has demonstrated that the Player object contains a Hand object," << endl
		<< "a DiceRollingFacility object, a collection of countries, as well as reinforce, fortify, and attack methods which " << endl
		<< "will be used later." << endl;

	cout << "\nEND"<<endl;
	
	system("PAUSE");

	//must show also dice rolling facility

	return 0;

};//end of driver

