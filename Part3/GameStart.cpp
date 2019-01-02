#include "GameStart.h"

//default constructor
Start::Start(Map& location){

	// PART 1: map selection
	cout << "Game is staring ..." << endl;

	bool mapCheck;
	do {
		std::ifstream mapList;
		mapList.open("mapList.txt");
		vector<string> mapNames;
		while (!mapList.eof()) {
			string name;
			mapList >> name;
			mapNames.push_back(name);
		}
		mapList.close();

		cout << "Map list: " << endl;
		for (int i = 0; i < mapNames.size(); i++) {
			cout << i << " -> " << mapNames[i] << endl;
		}
		cout << "Enter map number of selected map file: ";
		int mapChoice;
		cin >> mapChoice;

		cout << "Map is now loading ..." << endl;
		MapLoader mapL;
		mapCheck = mapL.LoadMap(mapNames[mapChoice], location);
	} while (!mapCheck);

	// PART 2: number of player selection

	int numberOfPlayers = 0;
	while (true) {
		cout << "Enter number of players: ";
		cin >> numberOfPlayers;
		if (numberOfPlayers < 2 || numberOfPlayers > 6){
			cerr << "Invalid number of players try again" << endl;
		}
		else{
			break;
		}
	}

	vector<string> playerNames;
	for (int i = 0; i < numberOfPlayers; i++){
		cout << "Player " << i + 1 << " name: ";
		string name;
		cin >> name;
		playerNames.push_back(name);
	}

	// PART 3: creating everything

	cout << "Players are being created ..." << endl;
	for (int i = 0; i < playerNames.size(); i++)
	{
		char bot;
		cout << "Should " << playerNames[i] << " be a human (h), an agressive bot (a) or a benevolent bot (b): ";
		cin >> bot;
		Player* tempPlayer = new Player(playerNames[i], new Hand, new Dice, bot);
		tempPlayer->addPlayer(tempPlayer);
		players.push_back(tempPlayer);
	}

	cout << "Deck of " << location.getNumberOfNodes() << " cards is being created ..." << endl;

	gameDeck = new Deck(location.getNumberOfNodes());

}

void Start::Startup(Map& location) {

	cout << "Shuffling players ..." << endl;
	random_shuffle(players.begin(), players.end());

	// ASSIGN COUNTRIES
	cout << "Assigning players random countries..." << endl;
	vector<Node> nodes = location.getNodes();
	random_shuffle(nodes.begin(), nodes.end());
	for (int i = 0; i < location.getNumberOfNodes(); i++){
		cout << players[(i % players.size())]->getPlayerName() << " is now the owner of " << nodes.back().getName() << endl;
		players[(i % players.size())]->addCountry(nodes.back().getName());
		location.replaceOwner(players[(i % players.size())]->getPlayerName(), nodes.back().getName());
		nodes.pop_back();
	}

	// ASSIGN STARTING ARMIES
	cout << "Players will now assign starting armies ..." << endl;
	
	int A = 50 - players.size() * 5;

	for (int j = 0; j < A; j++) {
		for (int i = 0; i < players.size(); i++) {
			do {
				string sending = players[i]->setupCountryChoice(location);
				if (location.checkOwner(players[i]->getPlayerName(), sending)) {
					location.addArmies(sending, 1);
					cout << sending << " now has " << location.getArmies(sending) << " armies. " << players[i]->getPlayerName() << " now has "  << A - j - 1  << " armies left to place."<< endl;
					break;
				}
				else {
					cerr << "Invalid country, it does not exist or you do not own it." << endl;
				}
			} while (true);
		}
	}
}

vector<Player*> Start::getPlayers(){
	return players;
}

Deck* Start::getDeck(){
	return gameDeck;
}




