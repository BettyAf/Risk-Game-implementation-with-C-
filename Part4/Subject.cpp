#include "Subject.h"
#include "Observer.h"

//Default constructor
Subject::Subject() {
	_observers = new list<Observer*>;
}

//Destructor
Subject::~Subject() {
	delete _observers;
}
//Add observer to end of observers' list
void Subject::attach(Observer* o) {
	_observers->push_back(o);
};
//Remove the observer from observers' list
void Subject::detach(Observer* o) {
	_observers->remove(o);
};
//Update the observers
void Subject::notify(string message) {
	list<Observer *>::iterator i = _observers->begin();
	for (; i != _observers->end(); ++i)
		(*i)->update(message);
};
//Update the observers
void Subject::notify() {
	list<Observer *>::iterator i = _observers->begin();
	for (; i != _observers->end(); ++i)
		(*i)->update();
};
