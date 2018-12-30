#ifndef PACK_H
#define PACK_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

enum card_t{
	infantry = 1,
	cavalry = 5,
	artillery = 10
};

//hand.h
class Hand{
public:
	Hand();											// player owned cards
	void addToHand(card_t card);					// allow draw to work with player
	void Exchange(card_t card1, card_t card2);		// trade cards for cards (see rule set)
	void showHand();								// visual of results
protected:
private:
	int numberInHand;
	std::vector<card_t> inHand;
};

//Deck.h
class Deck{
public:
	Deck(int numberOfCountries);					// contains card (infantry, artillery, cavalry)
	void Draw(Hand* myHand);						// draw a card remove 1 to numberOfCards
protected:
private:
	std::vector<card_t> cards;
	int numberOfCards;
};

#endif