/* Assignment 1-Part1(Map)-Fall 2017
Comp345- Team 17
*/
#include "stdafx.h"
#include <string>
#include "Country.h"
#include "Edge.h"

using namespace std;

//Edge creat a border(adjacency between two countries: country 1 and country 2
void Edge::setCountry1(Country c1){
	country1 = c1;
}

void Edge::setCountry2(Country c2){
	country2 = c2;
}

Country Edge::getCountry1(){
	return country1;
}

Country Edge::getCountry2(){
	return country2;
}

