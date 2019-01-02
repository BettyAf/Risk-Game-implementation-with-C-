//Assignment 3_Part2_ Team 17                                     
//Comp 345_fall 2017 

#include "ShowPhase.h"
#include "Player.h"
#include <iostream>
#include <string>
using namespace std;

//showPhase(concreteObserver) is derived from observer class and attach the subject(our player inherited from subject) to observer 
ShowPhase::ShowPhase() : Observer(){
}

ShowPhase::ShowPhase(Player* p) : Observer(), _subjects(p) {
	_subjects->attach(this);
}


ShowPhase::~ShowPhase() {
	_subjects->detach(this);
}

void ShowPhase::display() {
	
}

void ShowPhase::update(string message) {
	cout << message << endl;
}
void ShowPhase::update() {
	display();
}