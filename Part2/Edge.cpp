#include <string>
#include "Country.h"
#include "Edge.h"

using namespace std;

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
