#include "Pack.h"


int main(int argc, char *argv[]){
	// Creating a deck
	Deck myDeck(42);
	// Drawing cards and adding to hand
	Hand myHand;
	Hand *PHand = &myHand;

	// Drawing and showing results (full deck)
	for (int i = 0; i<43; i++){
		myDeck.Draw(PHand);
		myHand.showHand();
	}
	
	// Trying every exchange possible
	myHand.Exchange(cavalry, artillery);
	myHand.showHand();

	myHand.Exchange(artillery, infantry);
	myHand.showHand();

	myHand.Exchange(cavalry, cavalry);

	myHand.Exchange(artillery, cavalry);
	myHand.showHand();

	myHand.Exchange(infantry, cavalry);
	myHand.showHand();

	myHand.Exchange(cavalry, artillery);
	myHand.showHand();

	myHand.Exchange(cavalry, infantry);
	myHand.showHand();

	myHand.Exchange(infantry, artillery);
	myHand.showHand();

	return 0;
}