//Assignment 3_Part2_ Team 17                                     
//Comp 345_fall 2017 

#pragma once
#include "Observer.h"

class Observer;

class Subject {

public:
	Subject();
	~Subject();

	void attach(Observer *);
	void detach(Observer *);
	void notify(string message);
	void notify();
private:
	list<Observer*>* _observers;
};


