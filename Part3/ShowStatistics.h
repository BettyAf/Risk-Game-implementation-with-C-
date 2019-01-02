#pragma once
#include "Observer.h"
#include "Player.h"

//Concrete observer ShowStatics inherits Observer
class ShowStatistics : public Observer
{
public:
	ShowStatistics();
	ShowStatistics(Player* p);
	~ShowStatistics();
	void display();
	void update(string message);
	void update();

public:
	Player* _subjects;
	
};

