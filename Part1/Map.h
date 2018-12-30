/* Assignment 1-Part1(Map)-Fall 2017
Comp345- Team 17
*/
#pragma once
#include "Country.h"
#include "Edge.h"
#include"Continent.h"
#include<list>
#include<vector>
#include<unordered_set>
using namespace std;

class Map
{
private:
	vector<Country> countries;
	vector<Edge> adjacencies;
	unordered_set<string> connectedContinents;


public:
	Edge* ed;
	void addNode_country(Country);
	void addNode_continent(Continent);
	vector<Country> getCounries();
	vector<Country> getNeighbors(Country);
	unordered_set<string> getNeighborsName(Country);
	vector<Edge> getAdjacencies();

	void addAdjacencies(Edge);
	bool connected();
	unordered_set<string> continentList();
	int numberOfContinent();
	bool connectedContinent();

	void getCountryInformation();
	Country getCountryByName();
	void TestNeighborhood();
	
	
	
};




