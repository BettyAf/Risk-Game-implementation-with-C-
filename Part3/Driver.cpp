#include "GameStart.h"
#include "GameLoop.h"

using namespace std;

int main() {
	Map myMap;
	Start myStart(myMap);
	myStart.Startup(myMap);
	GameLoop game;
	game.startTheGame(myStart.getPlayers() , myMap);


	Deck* deck = myStart.getDeck();
}