//Assignment 3_Part2_ Team 17                                     
//Comp 345_fall 2017 

#pragma once
#include "Observer.h"
#include "Player.h"

class ShowPhase : public Observer
{
public:
	ShowPhase();
	ShowPhase(Player* p);
	~ShowPhase();
	void display();
	void update(string massage);
	void update();

public:
	Player* _subjects;
	
};

