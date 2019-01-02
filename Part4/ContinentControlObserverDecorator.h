#pragma once
#include "BasicDecoratorObserver.h"

class ContinentControlDecorator :public BasicDecoratorObserver {
public:
	Player* p;
	Map& map;
public:
	ContinentControlDecorator(BasicDecoratorObserver* decoratedC, Map& m) : BasicDecoratorObserver(p), map(m) {
	}

	~ContinentControlDecorator(){
	}

	string conquerContinent() {
		return BasicDecoratorObserver::conquerContinent(map) + BasicDecoratorObserver::loseContinent(map) ;
	}

	void display() {
		conquerContinent();
	}
	
};
