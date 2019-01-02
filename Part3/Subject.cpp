//Assignment 3_Part2_ Team 17                                     
//Comp 345_fall 2017   

#include "Subject.h"
#include "Observer.h"

Subject::Subject() {
	_observers = new list<Observer*>;
}
Subject::~Subject() {
	delete _observers;
}
void Subject::attach(Observer* o) {
	_observers->push_back(o);
};
void Subject::detach(Observer* o) {
	_observers->remove(o);
};
void Subject::notify(string message) {
	list<Observer *>::iterator i = _observers->begin();
	for (; i != _observers->end(); ++i)
		(*i)->update(message);
};

void Subject::notify() {
	list<Observer *>::iterator i = _observers->begin();
	for (; i != _observers->end(); ++i)
		(*i)->update();
};
