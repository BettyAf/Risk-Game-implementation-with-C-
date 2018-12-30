#include <iostream>
#include <string>
#include <vector>
#include "Country.h"
#include <vector>
#include "Player.h"
#include "Startup.h"
using namespace std;

int main(){

	Startup myStart;
	myStart.createPlayers();
	myStart.setOrder();

	for (vector<Player>::size_type i = 0; i != myStart.getPlayers().size(); ++i){
		cout << i << " player :" << myStart.getPlayers()[i].getName() << endl;
	}

	Map map;
	vector<Country> countries;

	Country canada;
	canada.setName("Canada");
	canada.setNumberOfArmies(0);
	map.addNode_country(canada);

	Country usa;
	usa.setName("USA");
	usa.setNumberOfArmies(0);
	map.addNode_country(usa);

	Country mexico;
	mexico.setName("Mexico");
	mexico.setNumberOfArmies(0);
	map.addNode_country(mexico);

	Country germany;
	germany.setName("Germany");
	germany.setNumberOfArmies(0);
	map.addNode_country(germany);

	Country france;
	france.setName("France");
	france.setNumberOfArmies(0);
	map.addNode_country(france);

	Country sweden;
	sweden.setName("Sweden");
	sweden.setNumberOfArmies(0);
	map.addNode_country(sweden);

	Country denmark;
	denmark.setName("Denmark");
	denmark.setNumberOfArmies(0);
	map.addNode_country(denmark);;


	myStart.setMap(map);
	myStart.assignCountries();



	for (vector<Country>::size_type i = 0; i != myStart.getMap().getCounries().size(); ++i){
		cout << " Country :" << myStart.getMap().getCounries()[i].getName() << " player is :" 
			<< myStart.getMap().getCounries()[i].getPlayer().getName() << endl;
	}

	myStart.placeArmy();	

	myStart.printArmies();

	return 0;
}