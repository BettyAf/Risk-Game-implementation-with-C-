#pragma once
#include "BasicDecoratorObserver.h"


class PlayerDominationDecorator :public BasicDecoratorObserver {
public:
	PlayerDominationDecorator(BasicDecoratorObserver* decoratedC) :BasicDecoratorObserver(p) {
	}
	~PlayerDominationDecorator() {
	}
	
	double percentOfCountry() {
		return BasicDecoratorObserver::percentOfCountry();
	}

	void display() {
		cout << "\n***Pecentage of countries owned by player " << player->getPlayerName() << " is: " << to_string(percentOfCountry()) << "%" << endl;
		
	}
private:
	Player* p;
};
