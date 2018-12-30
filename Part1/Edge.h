/* Assignment 1-Part1(Map)-Fall 2017
Comp345- Team 17
*/
#pragma once
#include <iostream>
#include <string>
#include "Country.h"
using namespace std;


class Edge
{
private:
	Country country1;
	Country country2;


public:
	void setCountry1(Country);
	void setCountry2(Country);
	Country getCountry1();
	Country getCountry2();



};



