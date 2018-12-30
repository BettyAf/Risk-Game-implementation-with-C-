#include "stdafx.h"
#include "GameStart.h"

using namespace std;

int main() {
	MapLoader map;
	GameStart game;
	//game.loadMap(map);
	game.setDeck();
	game.setPlayers();
		
	return 0;
}; 