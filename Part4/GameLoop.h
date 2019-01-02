#include <iostream>
#include <string>
#include <vector>
#include "Player.h"
using namespace std;

class GameLoop {

public:
	void startTheGame(vector<Player*> players, Map& location);
	bool gameFinished(Map& location);
};
