/* Assignment 1-Part1(Map)-Fall 2017
Comp345- Team 17
*/
#include "stdafx.h"
#include "Country.h"
#include "Continent.h"
#include "Edge.h"
#include "Map.h"
#include <iterator>
#include <unordered_set>
#include <iostream>
using namespace std;

int main()
{
	cout << "Assignment 1_Part 1_ Map" << endl;
	cout << "Team 17" << endl;
	Country canada;
	canada.setPlayer("Anahita");
	canada.setName("Canada");

	Country usa;
	usa.setPlayer("Cody");
	usa.setName("United States of America");

	Country mexico;
	mexico.setPlayer("Neven");
	mexico.setName("Mexico");

	Country germany;
	germany.setName("Germany");
	germany.setPlayer("Betty");

	Country france;
	france.setName("France");
	france.setPlayer("Felix");

	Country poland;
	poland.setName("Poland");
	poland.setPlayer("Sara");

	Country denmark;
	denmark.setName("Denmark");
	denmark.setPlayer("James");


	Continent america;
	america.setContinent_Name("America");
	canada.setContinent(america);
	usa.setContinent(america);
	mexico.setContinent(america);

	Continent europe;
	europe.setContinent_Name("Europe");
	germany.setContinent(europe);
	france.setContinent(europe);
	poland.setContinent(europe);
	denmark.setContinent(europe);

	Continent asia;
	asia.setContinent_Name("Asia");
	//france.setContinent(asia);


	Map newmap;
	newmap.addNode_country(canada);
	newmap.addNode_country(usa);
	newmap.addNode_country(mexico);

	Edge border1;
	border1.setCountry1(canada);
	border1.setCountry2(usa);

	Edge border2;
	border2.setCountry1(usa);
	border2.setCountry2(canada);

	Edge border3;
	border3.setCountry1(usa);
	border3.setCountry2(mexico);

	newmap.addAdjacencies(border1);
	newmap.addAdjacencies(border2);
	newmap.addAdjacencies(border3);



	
	//cout << "connected countries:" << newmap.connected() << "   " << endl;


	std::cout << "" << endl;
	std::cout << "" << endl;
	std::cout << "List of players, their country and continent:" << endl;
	std::cout << canada.getPlayer() << "  " << canada.getName() << "  " << canada.getContinent().getContinent_Name()
		<< endl;
	std::cout << usa.getPlayer() << " " << usa.getName() << "  " << usa.getContinent().getContinent_Name() << endl;

	std::cout << mexico.getPlayer() << " " << mexico.getName() << "  " << mexico.getContinent().getContinent_Name() << endl;
	std::cout << germany.getPlayer() << " " << germany.getName() << "  " << germany.getContinent().getContinent_Name() << endl;
	std::cout << poland.getPlayer() << " " << poland.getName() << "  " << poland.getContinent().getContinent_Name() << endl;
	std::cout << denmark.getPlayer() << " " << denmark.getName() << "  " << denmark.getContinent().getContinent_Name() << endl;
	std::cout << france.getPlayer() << " " << france.getName() << "  " << france.getContinent().getContinent_Name() << endl;


	vector<Edge> canada_adj = newmap.getAdjacencies();



	newmap.addNode_country(germany);
	newmap.addNode_country(poland);
	newmap.addNode_country(denmark);
	newmap.addNode_country(france);

	Edge border5;
	border5.setCountry1(denmark);
	border5.setCountry2(germany);

	Edge border6;
	border6.setCountry1(germany);
	border6.setCountry2(denmark);

	Edge border7;
	border7.setCountry1(germany);
	border7.setCountry2(france);

	Edge border8;
	border8.setCountry1(germany);
	border8.setCountry2(poland);

	Edge border_dummy;
	border_dummy.setCountry1(germany);
	border_dummy.setCountry2(usa);


	newmap.addAdjacencies(border5);
	newmap.addAdjacencies(border6);
	newmap.addAdjacencies(border7);
	newmap.addAdjacencies(border8);
	//dummy border for invalid map
	//newmap.addAdjacencies(border_dummy);

	cout << "number of continents: " << newmap.numberOfContinent() << endl;


	cout << "The connectivity of graph of map is like below:" << endl;
	vector<Edge> german_adj = newmap.getAdjacencies();
	for (vector<Edge>::size_type i = 0; i != german_adj.size() - 1; ++i)
		cout << "   " << german_adj[i].getCountry1().getName() << " ----> " << german_adj[i].getCountry2().getName() << endl;

	newmap.getCountryInformation();
	newmap.TestNeighborhood();
	//newmap.connectedContinent();

};

