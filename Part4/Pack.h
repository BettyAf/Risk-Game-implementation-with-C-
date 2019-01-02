//Assignment 2_ Team 17                                     
//Comp 345_fall 2017   


#ifndef PACK_H
#define PACK_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

enum card_t {
	default = 0,
	infantry = 1,
	cavalry = 5,
	artillery = 10
};

static int tradeCount = 0;

//hand.h
class Hand {
public:
	Hand();											// player owned cards
	void addToHand(card_t card);					// allow draw to work with player
	void exchange(card_t card1, card_t card2);		// trade cards for cards (see rule set)
	int trade(int number, card_t card = default);	// trade 3 of the same card or 1 of each for soldiers
	void showHand();								// visual of results
	int getNumberInHand();
protected:
private:
	int numberInHand;
	std::vector<card_t> inHand;
};

//Deck.h
class Deck {
public:
	Deck(int numberOfCountries);					// contains card (infantry, artillery, cavalry)
	void Draw(Hand* myHand);						// draw a card remove 1 to numberOfCards
protected:
private:
	std::vector<card_t> cards;
	int numberOfCards;
};

#endif