#include "GameStart.h"
#include "ContinentControlObserverDecorator.h"
#include "PlayerDominationObserverDecorator.h"
#include "PlayerHandsObserverDecorator.h"

//default constructor
Start::Start(Map& location) {

	// add 8 countries to play the game faster
	cout << "Game is staring ..." << endl;
	
	location.addNode("Quebec");
	location.addNode("Ontario");
	location.addNode("Alaska");
	location.addNode("Alberta");
	location.addNode("Brazil");
	location.addNode("Peru");
	location.addNode("Argentina");
	location.addNode("Venezuala");

	location.addCountryNeighbor("Quebec","Ontario");
	location.addCountryNeighbor("Quebec", "Venezuala");
	location.addCountryNeighbor("Ontario", "Quebec");
	location.addCountryNeighbor("Ontario", "Alberta");
	location.addCountryNeighbor("Alberta", "Ontario");
	location.addCountryNeighbor("Alberta", "Alaska");
	location.addCountryNeighbor("Alaska", "Alberta");
	location.addCountryNeighbor("Brazil", "Peru");
	location.addCountryNeighbor("Brazil", "Argentina");
	location.addCountryNeighbor("Brazil", "Venezuala");
	location.addCountryNeighbor("Peru", "Brazil");
	location.addCountryNeighbor("Peru", "Argentina");
	location.addCountryNeighbor("Peru", "Venezuala");
	location.addCountryNeighbor( "Argentina" , "Peru");
	location.addCountryNeighbor("Argentina", "Brazil");
	location.addCountryNeighbor("Venezuala", "Peru");
	location.addCountryNeighbor("Venezuala", "Brazil");
	location.addCountryNeighbor("Venezuala", "Quebec");

	location.addContinent("North America");
	location.addContinent("South America");
	location.setValueContinent("North America", 5);
	location.setValueContinent("South America", 2);
	location.addContinentCountry("North America", "Quebec");
	location.addContinentCountry("North America", "Ontario");
	location.addContinentCountry("North America", "Alaska");
	location.addContinentCountry("North America", "Alberta");
	location.addContinentCountry("South America", "Brazil");
	location.addContinentCountry("South America", "Peru");
	location.addContinentCountry("South America", "Argentina");
	location.addContinentCountry("South America", "Venezuala");
	
	// PART 2: number of player selection

	int numberOfPlayers = 0;
	while (true) {
		cout << "Enter number of players: ";
		cin >> numberOfPlayers;
		if (numberOfPlayers < 2 || numberOfPlayers > 6) {
			cerr << "Invalid number of players try again" << endl;
		}
		else {
			break;
		}
	}

	vector<string> playerNames;
	for (int i = 0; i < numberOfPlayers; i++) {
		cout << "Player " << i + 1 << " name: ";
		string name;
		cin >> name;
		playerNames.push_back(name);
	}

	// PART 3: creating everything
	
	cout << "Players are being created ..." << endl;
	
	for (int i = 0; i < playerNames.size(); i++)
	{
		Player* tempPlayer = new Player(playerNames[i], new Hand, new Dice);
		tempPlayer->addPlayer(tempPlayer);
		allPlayers.push_back(tempPlayer);
	}

	cout << "Deck of " << location.getNumberOfNodes() << " cards is being created ..." << endl;

	gameDeck = new Deck(location.getNumberOfNodes());
//	decoratorPlayer = new PlayerHandDecorator(decoratorPlayer);
}

void Start::Startup(Map& location) {

	cout << "Shuffling players ..." << endl;
	random_shuffle(allPlayers.begin(), allPlayers.end());

	// ASSIGN COUNTRIES
	cout << "Assigning players random countries..." << endl;
	vector<Node> nodes = location.getNodes();
	random_shuffle(nodes.begin(), nodes.end());
	for (int i = 0; i < location.getNumberOfNodes(); i++) {
		cout << allPlayers[(i % allPlayers.size())]->getPlayerName() << " is now the owner of " << nodes.back().getName() << endl;
		allPlayers[(i % allPlayers.size())]->addCountry(nodes.back().getName());
		location.replaceOwner(allPlayers[(i % allPlayers.size())]->getPlayerName(), nodes.back().getName());
		nodes.pop_back();
	}


	// ASSIGN STARTING ARMIES
	cout << "\nPlayers will now assign starting armies ..." << endl;

	int A = 15 - allPlayers.size() * 5;
	
	for (int j = 0; j < A; j++) {
		for (int i = 0; i < allPlayers.size(); i++) {
			do {
				string sending = allPlayers[i]->setupCountryChoice(location);
				if (location.checkOwner(allPlayers[i]->getPlayerName(), sending)) {
					location.addArmies(sending, 1);
					cout << sending << " now has " << location.getArmies(sending) << " armies. " << allPlayers[i]->getPlayerName() << " now has " << A - j - 1 << " armies left to place." << endl;
					break;
				}
				else {
					cerr << "Invalid country, it does not exist or you do not own it." << endl;
				}
			} while (true);
		}
	}
}

vector<Player*> Start::getPlayers() {
	return allPlayers;
}

Deck* Start::getDeck() {
	return gameDeck;
}




