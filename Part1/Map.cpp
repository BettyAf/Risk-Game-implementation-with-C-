/* Assignment 1-Part1(Map)-Fall 2017
Comp345- Team 17
*/
#include "stdafx.h"
#include "Map.h"
#include "Edge.h"
#include <list>
#include "Country.h"
#include "Continent.h"
#include <queue>
#include<vector>
#include <algorithm>
#include <unordered_set>
#include<string>

using namespace std;



void Map::addNode_country(Country newcountry){
	countries.push_back(newcountry);
}
vector<Country>  Map::getCounries(){
	return countries;
}

vector<Edge>  Map::getAdjacencies(){
	return adjacencies;
}

void Map::addAdjacencies(Edge edge){
	adjacencies.push_back(edge);
}
//creat adjacency between two countries,returns the neighbors of a country as a vector of country objects
vector<Country> Map::getNeighbors(Country country){
	vector<Country> neighbors;
	for (vector<Edge>::size_type i = 0; i != adjacencies.size(); ++i){
		if (adjacencies[i].getCountry1().getName() == country.getName()){
			neighbors.push_back(adjacencies[i].getCountry2());
		}
		if (adjacencies[i].getCountry2().getName() == country.getName()){
			neighbors.push_back(adjacencies[i].getCountry1());
		}
	}
	return neighbors;
}

/* function that get the name of a country as input and returns the name of country's neighbors as output*/
    unordered_set<string> Map::getNeighborsName(Country countryNeighbor){
	unordered_set<string> neighborhood;
	vector<Country> neighbors = Map::getNeighbors(countryNeighbor);

	for (vector<Country>::size_type i = 0; i != neighbors.size(); ++i){
		neighborhood.insert(neighbors[i].getName());
	}
	return neighborhood;
}



/*Check that countries in the map are connected*/

bool Map::connected(){

	int size = countries.size();
	vector<Country> v;   //visited
	queue<Country> q;    //queue of curent visiting nodes
	unordered_set<string> connectedContinents;
	connectedContinents.size();

	v.push_back(countries.front());
	connectedContinents.insert(countries.front().getContinent().getContinent_Name());
	q.push(countries.front());
	while (!q.empty()){
		Country current;
		current = q.front();
		q.pop();
		vector<Country> adjacents = Map::getNeighbors(current);

		for (vector<Country>::size_type j = 0; j != adjacents.size(); ++j){
			connectedContinents.insert(adjacents[j].getContinent().getContinent_Name());
			bool found = false;

			for (vector<Country>::size_type k = 0; k != v.size(); ++k){
				if (v[k].getName() == adjacents[j].getName())
					found = true;
			}

			if (!found) {
				v.push_back(adjacents[j]);
				q.push(adjacents[j]);
			}
		}

	}
	
	return (v.size() == size);
}

//return list of continents in the map, we used unordered_set because set does not save repeated value
unordered_set<string> Map::continentList(){
	unordered_set<string> CL;
	cout << "countries in Map:" << endl;
	for (std::vector<Country>::size_type y = 0; y != countries.size(); ++y){
		CL.insert(countries[y].getContinent().getContinent_Name());
		cout << "  " << countries[y].getName() << endl;
	}
	return CL;
}
//return number of continents in the map
int Map::numberOfContinent(){
	int size;
	size = continentList().size();
	return size;
}

//Function that checks if continents are connected as a subgraph
bool Map::connectedContinent(){

	int size = numberOfContinent();
	vector<Country> v;   //visited continent
	queue<Country> q;    //queue of curent visiting nodes
	unordered_set<string> visitedContinents;

	v.push_back(countries.front());
	visitedContinents.insert(countries.front().getContinent().getContinent_Name());
	q.push(countries.front());
	while (!q.empty()){
		Country current;
		current = q.front();
		q.pop();
		vector<Country> adjacents = Map::getNeighbors(current);

		for (vector<Country>::size_type j = 0; j != adjacents.size(); ++j){
			visitedContinents.insert(adjacents[j].getContinent().getContinent_Name());
			bool found = false;

			for (vector<Country>::size_type k = 0; k != v.size(); ++k){
				if (v[k].getName() == adjacents[j].getName())
					found = true;
			}

			if (!found) {
				v.push_back(adjacents[j]);
				q.push(adjacents[j]);
			}
		}

	}

	return (visitedContinents.size() == size);
}

//Function that check if such a country exist in the map
Country  Map::getCountryByName(){
	cout << "enter the name of country:" << endl;
	string countryName;
	cin >> countryName;
	for (vector<Country>::size_type i = 0; i != countries.size(); ++i){
		if (countries[i].getName() == countryName)
			return countries[i];
	}
	cout << "no such a country exists" << endl;
	return Country();
}
//Function that gets the name of a country as input and  returns the information of that country : Continent, player name and neighbors of country

void Map::getCountryInformation(){
	Country country = getCountryByName();
	if (country.getName() != ""){
		unordered_set<string> neigborsname;
		neigborsname = getNeighborsName(country);
		unordered_set<string>::iterator  iter;
		cout  << country.getName() << " is in continent : " << country.getContinent().getContinent_Name() << endl;
		cout <<"Player of "<< country.getName() << "  is : " << country.getPlayer() << endl;
		cout << "Neighbors of " << country.getName() << "  are: " << endl;
		for (iter = neigborsname.begin(); iter != neigborsname.end(); ++iter){
			cout << "  - " << *iter << endl;
		}
		cout << endl;
	}
}

//Function to check if two countries are neighbors or not
void Map::TestNeighborhood(){
	bool foundNeighbor = false;
	cout << "check neighborhood of two country," << endl;
	//cout << "1.Enter first country name  ";
	Country country1 = getCountryByName();
	//cout << "2.Enter second country name  ";
	Country country2 = getCountryByName();
	unordered_set<string> neigborsname1;
	unordered_set<string>::iterator  iter;
	neigborsname1 = getNeighborsName(country1);
	for (iter = neigborsname1.begin(); iter != neigborsname1.end(); ++iter){
		if (*iter == country2.getName()){
			foundNeighbor = true;
		}
	}
	if (foundNeighbor){
		cout << "two countries are neighbors" << endl;
	}
	else{
		cout << "two countries are not neighbors" << endl;
	}

}

