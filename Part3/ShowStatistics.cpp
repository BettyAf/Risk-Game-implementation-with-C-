#include "ShowStatistics.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;

//Default constructor
ShowStatistics::ShowStatistics() : Observer(){
}

//Constructor which attach new observers
ShowStatistics::ShowStatistics(Player* p) :Observer(), _subjects(p) {
	_subjects->attach(this);
}

//Destructor of the class
ShowStatistics::~ShowStatistics() {
	_subjects->detach(this);
}

//Display changes of obervers
void ShowStatistics::display() {
	int numCountries = _subjects->getCountries().size();
	double percentage = (static_cast<double>(numCountries) / 42) * 100;
	cout << _subjects->getPlayerName();
	printf(" ( %.2f %% ) ", percentage);
	
	for (int i = 0; i < numCountries; i++) {
		cout << "* ";
	}
	cout << endl;
}
void ShowStatistics::update(string message) {
	cout << message << endl;
}
//Update changes of obervers
void ShowStatistics::update() {
	display();
}