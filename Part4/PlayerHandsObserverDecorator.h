#pragma once
#include "BasicDecoratorObserver.h"
#include "Player.h"

class PlayerHandDecorator :public BasicDecoratorObserver {
public:
	PlayerHandDecorator(BasicDecoratorObserver* decoratedC) :BasicDecoratorObserver(p) {
	}
	~PlayerHandDecorator() {
	}

	void displayCards() {
		BasicDecoratorObserver::displayCards();
	}

	void display() {
		displayCards();
	}

private:
	Player* p;
};
