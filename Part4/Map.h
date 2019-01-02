//Assignment 2_ Team 17                                     
//Comp 345_fall 2017   


#pragma once

#include <vector>
#include <string>
#include "DiceRollingFacility.h"
#include "Pack.h"

// Country.h
class Country
{
public:

	Country(string countryName);

	void setPlayer(string playerName);
	void addArmies(int add);
	void removeArmies(int remove);
	int getArmies();
	string getName();
	string getPlayer();

private:
	string name;
	int numberOfArmies;
	string owner;
};

// Node.h
// node is a country + its neighbor nodes
class Node
{
public:
	Node(Country& countryName);
	void addNeighbor(Node& countryName);
	string getName();
	Country* getCountry();
	bool checkNeighbor(string countryName);
	vector <Node*> getNeighbors();

	//TEST FUNCTIONS
	void showNeighbors();

private:
	Country* country;
	vector<Node*> neighbors;
};

// Continent,h
class Continent {
public:
	Continent(string continentName);
	void continentValue(int);

	void addCountry(Node);
	string getName();
	int getValue();
	vector<Node> getContries();


	//TEST FUNCTIONS
	void showCountries();


private:
	string name;
	vector<Node> countries;
	int value;

};

// Map.h
// Uses functions from other classes so that in main we mainly use map
class Map 
{
public:
	void addNode(string countryName);
	void addCountryNeighbor(string countryName, string neighbors);
	void addContinent(string continentName);
	void setValueContinent(string, int);
	void addContinentCountry(string continentName, string countryName);
	vector<Node> getContriesOfcontinent(string continetName);
	void replaceOwner(string p, string countryName);

	Node getNode(string countryName);
	vector<Node> getNodes();
	int getNumberOfNodes();
	vector<Continent> getContinent();
	bool checkNeigbor(string countryName1, string countryName2);
	bool checkOwner(string p, string countryName);
	int getArmies(string CountryName);
	void addArmies(string CoutryName, int number);
	void removeArmies(string CountryName, int number);

	//TEST FUNCTIONS
	void showNodes();
	void showNeighbors(string countryName);
	void showContinents();
	void showContinentsCountries(string continentName);

private:
	vector<Node> nodes;
	vector<Continent> continents;
};




