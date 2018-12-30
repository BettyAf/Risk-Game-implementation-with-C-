#include "Startup.h"
#include <iostream>
#include <string>
#include <vector>
#include "Player.h"
#include <unordered_set>
#include <ctype.h>
#include "Map.h"
using namespace std;


void Startup::setMap(Map thisMap){
	map = thisMap;
}

vector<Player> Startup::getPlayers(){
	return players;
}

/* Creat palyer (1-6 players)*/
void Startup::createPlayers(){
	
	int numberOfPlayers;
	bool flag = true;
	while (flag)
	{
		cout << "Please Enter the Number of Players:" << endl;
		cin >> numberOfPlayers;
		if (numberOfPlayers> 6 || numberOfPlayers < 2){
			cout << "Enterd Number in not valid - Enter a number between 2 - 6." << endl;
		}
		else{
			flag = false;
		}
	}
	/* Enter the name of players*/
	vector<Player> inputPlayers(numberOfPlayers);
	 
	for (int i = 0; i < numberOfPlayers; i++){
		string name;
		Player player;
		
		cout << "Please Enter the Name of Player " << (i+1) << " :" << endl;
		cin >> name;
		cout << endl;
		player.setName(name);
		inputPlayers[i] = player;
	}
	
	players = inputPlayers;

}
/* set the order of players( the order they play will be a random order)*/
void Startup::setOrder(){
	int size = players.size();
	cout << "number of players are :" << size << endl;
	vector<Player> tempPlayers = players;
	unordered_set<int> track;
	int pick;

	while (track.size() < size){
		pick = rand() % size;
		const bool is_in = track.find(pick) != track.end();
		if (!is_in){
			players[track.size()] = tempPlayers[pick];
			track.insert(pick);
		}
	}
}

/* Assign countries to each player in a round robin fashion*/
void Startup::assignCountries(){
	Map newMap = map;
	vector<Country> newCounties= newMap.getCounries();
	for (vector<Country>::size_type i = 0; i != newCounties.size(); i++){
		newCounties[i].setPlayer(players[i % players.size()]);
	 
	}
	newMap.setCountries(newCounties);
	map = newMap;
}

Map Startup::getMap(){
	return map;
}


/* place armies on countries */
void Startup::placeArmy(){

	int n = numberOfArmies();
	
	for (int i = 1; i < n + 1; i++){
		for (vector<Player>::size_type j = 0; j != players.size(); j++){
			Player currentP = players[j];
			cout << endl << "Player " << currentP.getName() << " turn." << endl;
			vector<Country> playerCountries = map.getCounriesByPlayer(currentP);
			cout << "Your 'counties are :" << endl;

			for (vector<Country>::size_type k = 0; k != playerCountries.size(); k++){
				cout << k << " - " << playerCountries[k].getName() << " number of armies :" << playerCountries[k].getNumberOfArmies() << endl;
			}

			cout << "You want to assign one army to which Country ?(by number)" << endl;
			int countryIndex;
			//error handling for input
			cin >> countryIndex;
			string countryName = playerCountries[countryIndex].getName();
			vector<Country> tempCountries = map.getCounries();
			for (vector<Country>::size_type t = 0; t != tempCountries.size(); t++){
				if (tempCountries[t].getName() == countryName){
					cout << "current number of armies for " << countryName << " is " << tempCountries[t].getNumberOfArmies() << endl;
					cout << "One Army is assgiend to " << countryName << endl;
					tempCountries[t].setNumberOfArmies(tempCountries[t].getNumberOfArmies() + 1);
					cout << "new number of armies for " << countryName << " is " << tempCountries[t].getNumberOfArmies() << endl;

				}
			}

			map.setCountries(tempCountries);

		}

	}


}


void Startup::test(){
	for (vector<Country>::size_type p = 0; p != map.getCounries().size(); p++){
		Country *c;
		c = &map.getCounries()[p];
		cout << "pointer : " << c->getName() << endl;
	}
}

/* for any number of players in the game, we have a number of armies */
int Startup::numberOfArmies(){
	int playersSize = players.size();
	int numberOfArmies;
	switch (playersSize){
	case 2: numberOfArmies = 3;
		break;
	case 3: numberOfArmies = 35;
		break;
	case 4: numberOfArmies = 30;
		break;
	case 5: numberOfArmies = 25;
		break;
	case 6: numberOfArmies = 20;
		break;
	default:
		break;
	}
	return numberOfArmies;
}

/* print the number of armies assigned to each country*/
void Startup::printArmies(){

	for (vector<Player> ::size_type i = 0; i != players.size(); i++){
		cout << "number of assigned countries to " << players[i].getName() << " is " << map.numberOFAssignedArmies(players[i]) << endl;
		vector<Country> countriesOfPlayer = map.getCounriesByPlayer(players[i]);
		for (vector<Country>::size_type j = 0; j != countriesOfPlayer.size(); j++){
			cout << countriesOfPlayer[j].getName() << " --> " << countriesOfPlayer[j].getNumberOfArmies() << endl;
		}
		
	}

}