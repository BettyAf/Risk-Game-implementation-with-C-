//Assignment 3_ Team 17                                     
//Comp 345_fall 2017  

#pragma once
#include <list>
using namespace std;

class Observer;
//abstract class Observable
class Observaerable {
public:
	//Destructor 
	virtual ~Observaerable() {};
	//three virtual method attach, detach, notify
	virtual void attach(Observer *)=0;
	virtual void detach(Observer *)=0;
	virtual void notify()=0;

protected:
	//Constructor
	Observaerable() {};

private:
	list<Observer*> _observers;
};
