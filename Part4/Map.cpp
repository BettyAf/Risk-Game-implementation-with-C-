//Assignment 2_ Team 17                                     
//Comp 345_fall 2017   


#include "Map.h";


//Country.cpp

// Constructor
Country::Country(string countryName) {
	name = countryName;
	numberOfArmies = 0;
	owner = "none";
}

// Change player + update player
void Country::setPlayer(string playerName) {
	owner = playerName;
}

// Derived methods
void Country::addArmies(int add) {
	numberOfArmies += add;
}

void Country::removeArmies(int remove) {
	numberOfArmies -= remove;
}

int Country::getArmies() {
	return numberOfArmies;
}

// Accessor
string Country::getName() {
	return name;
}

string Country::getPlayer() {
	return owner;
}

//Node.cpp

//Constructor
Node::Node(Country& countryName) {
	country = &countryName;
}

// Accessor/Mutator
void Node::addNeighbor(Node& countryName) {
	neighbors.push_back(&countryName);
}

string Node::getName() {
	return country->getName();
}

Country* Node::getCountry() {
	return country;
}

// Ensure it is a neighbor
bool Node::checkNeighbor(string countryName) {
	for (int i = 0; i < neighbors.size(); i++) {
		if (neighbors[i]->getName() == countryName) {
			return true;
		}
	}
	return false;
}
vector <Node*> Node::getNeighbors() {
	return neighbors;
}


// FOR TESTING
void Node::showNeighbors() {
	for (int i = 0; i < neighbors.size() - 1; i++) {
		std::cout << neighbors[i]->getName() << ", ";
	}
	std::cout << neighbors[neighbors.size() - 1]->getName() << "." << endl;
}

//Continent.cpp

// Constructor
Continent::Continent(string continentName) {
	name = continentName;
}

void Continent::continentValue(int val) {
	value = val;
}

// Accessor/Mutator
void Continent::addCountry(Node addCountry) {
	countries.push_back(addCountry);
}

string Continent::getName() {
	return name;
}

int Continent::getValue() {
	return value;
}

void Continent::showCountries() {
	for (int i = 0; i < countries.size(); i++) {
		std::cout << countries[i].getName() << std::endl;
	}
}

vector<Node> Continent::getContries() {
	return countries;
}

//Map.cpp

// Accessor/Mutator
void Map::addNode(string countryName) {
	Country* c1 = new Country(countryName);
	Node* n1 = new Node(*c1);
	nodes.push_back(*n1);
}

void Map::addCountryNeighbor(string countryName, string neighbors) {
	int i = 0;
	for (; i < nodes.size(); i++) {
		if (nodes[i].getName() == countryName) {
			break;
		}
	}
	int j = 0;
	for (; j < nodes.size(); j++) {
		if (nodes[j].getName() == neighbors) {
			break;
		}
	}
	nodes[i].addNeighbor(nodes[j]);
}

void Map::addContinent(string continentName) {
	Continent* cc1 = new Continent(continentName);
	continents.push_back(*cc1);
}

void Map::setValueContinent(string cont, int val) {
	int i = 0;
	for (; i < continents.size(); i++) {
		if (continents[i].getName() == cont)
			break;
	}
	continents[i].continentValue(val);
}


void Map::addContinentCountry(string continentName, string coutryName) {
	int i = 0;
	for (; i < continents.size(); i++) {
		if (continents[i].getName() == continentName) {
			break;
		}
	}
	int j = 0;
	for (; j < nodes.size(); j++) {
		if (nodes[j].getName() == coutryName) {
			break;
		}
	}
	continents[i].addCountry(nodes[j]);
	//cout << "continent " << continents[i].getName() << " has country " << nodes[j].getName() << endl;
}

vector<Node> Map::getContriesOfcontinent(string continentName) {
	int j = 0;
	for (; j < continents.size(); j++) {
		if (continents[j].getName() == continentName) {
			break;
		}
	}
	vector<Node> theCountries = continents[j].getContries();

	return theCountries;
}

// Access to lower methods
void Map::replaceOwner(string p, string countryName) {
	for (int i = 0; i < nodes.size(); i++) {
		if (nodes[i].getName() == countryName) {
			nodes[i].getCountry()->setPlayer(p);
			break;
		}
	}
}

Node Map::getNode(string countryName) {
	int j = 0;
	for (; j < nodes.size(); j++) {
		if (nodes[j].getName() == countryName) {
			break;
		}
	}
	return nodes[j];
}

vector<Node> Map::getNodes() {

	return nodes;
}

int Map::getNumberOfNodes() {
	return nodes.size();
}

vector<Continent> Map::getContinent() {
	return continents;
}

bool Map::checkNeigbor(string countryName1, string countryName2) {
	int i = 0;
	for (; i < nodes.size(); i++) {
		if (nodes[i].getName() == countryName1) {
			break;
		}
	}
	return nodes[i].checkNeighbor(countryName2);
}

bool Map::checkOwner(string p, string countryName) {
	for (int i = 0; i < nodes.size(); i++) {
		if (nodes[i].getName() == countryName) {
			if (nodes[i].getCountry()->getPlayer() == p) {
				return true;
			}
			return false;
		}
	}
	return false;
}

int Map::getArmies(string countryName) {
	for (int i = 0; i < nodes.size(); i++) {
		if (nodes[i].getName() == countryName) {
			return nodes[i].getCountry()->getArmies();
		}
	}
	return 0;
}

void Map::addArmies(string countryName, int number) {
	for (int i = 0; i < nodes.size(); i++) {
		if (nodes[i].getName() == countryName) {
			nodes[i].getCountry()->addArmies(number);
		}
	}
}

void Map::removeArmies(string countryName, int number) {
	for (int i = 0; i < nodes.size(); i++) {
		if (nodes[i].getName() == countryName) {
			nodes[i].getCountry()->removeArmies(number);
		}
	}
}


// FOR TESTING
void Map::showNodes() {
	for (int j = 0; j < nodes.size(); j++) {
		std::cout << nodes[j].getName() << std::endl;
	}
}

void Map::showNeighbors(string countryName) {
	int j = 0;
	for (; j < nodes.size(); j++) {
		if (nodes[j].getName() == countryName) {
			break;
		}
	}
	cout << "Neighbor of country " << countryName << " are: ";
	nodes[j].showNeighbors();
}

void Map::showContinents() {
	for (int j = 0; j < continents.size(); j++) {
		std::cout << continents[j].getName() << std::endl;
	}
}

void Map::showContinentsCountries(string continentName) {
	int j = 0;
	for (; j < continents.size(); j++) {
		if (continents[j].getName() == continentName) {
			break;
		}
	}
	continents[j].showCountries();
}
/*
int Map::getTurn() {
	return 0;
}

void Map::displayCards() {
	p->getHand()->showHand();
}

void Map::percentOfCountry(){
	int numCountries = p->getCountries().size();
	double percentage = (static_cast<double>(numCountries) / 8) * 100;
	cout << "\n***Pecentage of countries owned by player " << p->getPlayerName() << " is: " << percentage << "%" << endl;
}

string Map::conquerContinent() {
	//Countries which are owned by player
	vector<Continent> theContinents = getContinent();
	string output;

	//Check if all countries are a continent to give the continent value to player
	for (int i = 0; i < theContinents.size(); i++) {
		vector<Node> temp = theContinents[i].getContries();
		int count = temp.size();
		for (int j = 0; j < temp.size(); j++) {
			bool check = false;
			for (int k = 0; k < p->getCountries().size(); k++) {
				if (temp[j].getName() == p->getCountries()[k]) {
					check = true;
					break;
				}
			}
			if (!check) {
				break;
			}
			else {
				count--;
			}
		}
		//give the continent to the player because he contains all contries in the continent
		if (count == 0) {
			output = p->getPlayerName() + " own all countries of " + theContinents[i].getName();
			counter++;
		}
		else
			output = "***" + p->getPlayerName() + " has owned no continent";
	}
	return output;
}

string Map::loseContinent() {
	string output;
	if (counter > 0 && conquerContinent() == "") {
		output == " but " + p->getPlayerName() + " loses control of the continent";
	}
	else
		output = "";
	return output;
}
*/

