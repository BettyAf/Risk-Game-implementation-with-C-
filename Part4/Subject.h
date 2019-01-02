#pragma once
#include <string>
#include "Observable.h"

class Observer;

class Subject :public Observaerable {

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


