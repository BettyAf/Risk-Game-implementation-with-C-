/* Assignment 1-Part1(Map)-Fall 2017
Comp345- Team 17
*/
#include "stdafx.h"
#include "Continent.h"
#include <string>
using namespace std;


void Continent::setContinent_Name(string continent)
{
	continent_name = continent;
}

string Continent::getContinent_Name(){
	return continent_name;
}

