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
//	Edge();
//	Edge(Country c1, Country c2);
	void setCountry1(Country);
	void setCountry2(Country);
	Country getCountry1(); 
	Country getCountry2();

	

};

