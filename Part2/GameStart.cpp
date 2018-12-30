#include "stdafx.h"
#include "GameStart.h"

//default constructor
GameStart::GameStart()
{
}

// User select a map from a list of map files
string GameStart::selectMap() {
	string inputFilename;
	ifstream inputfile;
	do {
		cout << "Please enter a file name" << endl;
		getline(cin, inputFilename);

		// Open the file
		inputfile.open(inputFilename.c_str());

		// Check for successful opening
		if (inputfile.fail())
		{
			cerr << "\nError Opening File" << endl;
			
		}
		else {
			cout << "\nThe file has been successfully opened for reading.\n" <<endl;
			break;
		}
	} while (true);
	
	return inputFilename;
	inputfile.close();
}

//Load the map and create a deck of card
int GameStart::loadMap(MapLoader& myMap) {
	Map myM;
	//MapLoader loads the selected map and check if it is a valid map file or not
	myMap = MapLoader(selectMap(), myM);
		
	int numberOfCountries;
	numberOfCountries = myMap.getcountrySize();

	return numberOfCountries;
}



// create all the players, assign dice rolling facilities and empty hand of cards to the players.
void GameStart::setPlayers() {
	// user select number of player 
	int numPalyer;
	do {
		cout << "\nPlaese enter number of player between 2 to 6: " << endl;
		cin >> numPalyer;
		// check if the user enetr valid input
		if (numPalyer < 2 || numPalyer > 6)
			cout << "\nInvalid input!" << endl;
		else {
			numberPlayer = numPalyer;
			break;
		}

	} while (true);

	cout << "\n Players are creating ..." << endl;
	
	// create players with a dice and empty hand
	for (int i = 0; i < numberPlayer; i++) {
		Hand* myHand = new Hand;
		Dice* myDice = new Dice;
		string pl = "Player ";
		Player myPlayer(pl, myHand, myDice);
		cout << "Player " << i+1 <<" is created.";
		cout << " Player " << i+1 << " assigned to a dice and empty hand" << endl;

	}
}

void GameStart::setDeck() {
	MapLoader myMap;
	int numCountries = loadMap(myMap);
	std::cout << "\n Creation of valid deck of cards ...." << std::endl;
	// create an deck of card which takes number of countries as  a number of cards
	Deck myDeck = Deck(numCountries);
	std::vector<card_t> myCards = myDeck.getCards();
	std::vector<std::string> myCountries = myMap.getCountries();

	//show card of countries
	for (int i = 0; i < numCountries; i++) {
		std::cout << myCountries[i] << " has the card " << myCards[i] << std::endl;
	}
}

int GameStart::getPalyer() {
	return numberPlayer;
}





