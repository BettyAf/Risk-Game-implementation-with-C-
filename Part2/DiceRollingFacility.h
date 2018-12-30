//Assignment 2_ Team 17                                     
//Comp 345_fall 2017                                   

#pragma once
#include <iostream>
#include <vector>
#include <time.h>
using namespace std;


//class Dice with its construction and methods
class Dice{
public:
	Dice();
	int diceRoll();

	void percentageOfDiceValue();
	void getPercentage();
	
private:
	vector<int> diceRollHistory;
	double percentVal[6];
	bool didPercentage = false;
};

