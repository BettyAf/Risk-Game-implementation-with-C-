#include <iostream>
#include <string>
#include <vector>
using namespace std;

class GameLoop{
private:

public:
		void startTheGame(vector<Player*> players, Map& location);
		bool gameFinished(Map& location);

};