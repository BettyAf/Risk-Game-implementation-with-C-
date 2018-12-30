#include <iostream>
#include <string>
#include <vector>
#include "Startup.h"
using namespace std;

class GameLoop{
private:
	Startup startup;

public:
		void setStartUp(Startup);
		void startTheGame();
		void reinforcement(Player);
		void attack(Player);
		void fortification(Player);
		bool gameFinished();
		void dummyFinish();

};