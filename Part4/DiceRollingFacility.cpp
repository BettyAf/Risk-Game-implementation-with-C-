
//Assignment 1_ Team 17                                     
//Comp 345_fall 2017                                   

#include "DiceRollingFacility.h";

using namespace std;

Dice::Dice() {
	srand(time(NULL));
}
//diceValue() returns the  value of dice, and it has  an equal share of 1 - 6 values returned
int Dice::diceRoll()
{
	//no value outside of the 1-6
	int result;
	result = rand() % 6 + 1;
	diceRollHistory.push_back(result);
	return result;
}

//Method percentageOfDiceValue() keep track of the percentage of each value that has been rolled up to now
void Dice::percentageOfDiceValue()
{
	int countDices[6] = { 0, 0, 0, 0, 0, 0 };
	//Keep track of each values that has been rolled up to now
	for (int i = 0; i < diceRollHistory.size(); i++) {
		switch (diceRollHistory[i])
		{
		case 1:
			countDices[0] = countDices[0] + 1;
			break;
		case 2:
			countDices[1] = countDices[1] + 1;
			break;
		case 3:
			countDices[2] = countDices[2] + 1;
			break;
		case 4:
			countDices[3] = countDices[3] + 1;
			break;
		case 5:
			countDices[4] = countDices[4] + 1;
			break;
		case 6:
			countDices[5] = countDices[5] + 1;
			break;
		default:
			exit(1);
		}
	}
	//Calculate the percentage of each value of dice
	for (int i = 0; i < 6; i++)
	{
		percentVal[i] = ((double)countDices[i] / diceRollHistory.size()) * 100;
		cout << "The percentage of rolled number " << i + 1 << " is :" << percentVal[i] << "%" << endl;
	}
	didPercentage = true;
}

void Dice::getPercentage() {
	if (didPercentage) {
		for (int i = 0; i < 6; i++)
		{
			cout << "The percentage of rolled number " << i + 1 << " is :" << percentVal[i] << "%" << endl;
		}
	}
}
