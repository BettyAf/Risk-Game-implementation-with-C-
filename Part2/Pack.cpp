//Assignment 2_ Team 17                                     
//Comp 345_fall 2017   

#include "Pack.h"

// Hand constructor
Hand::Hand(){
	inHand;
	numberInHand = 0;
}

// adds a card to hand (see draw function)
void Hand::addToHand(card_t card){
	inHand.push_back(card);
	++numberInHand;
}

// iterate over inHand to show number of each cards
void Hand::showHand(){

	int infantry = 0;
	int cavalry = 0;
	int artillery = 0;

	for (int i = 0; i<numberInHand; i++){
		if (inHand[i] == 1){
			infantry++;
		}
		else if (inHand[i] == 5){
			cavalry++;
		}
		else{
			artillery++;
		}

	}
	std::cout << "Infantry: " << infantry << " Cavalry: " << cavalry << " Artillery: " << artillery <<std::endl;
}

// Trade card1 to card2
void Hand::exchange(card_t card1, card_t card2){

	//delete card1 card2/card1 times
	//add card2
	if (card1 < card2){

		int count = card2/card1;

		// test if there is enough cards
		for (int i = numberInHand-1; i >= 0; i--){
			if (inHand[i] == card1){
				count--;
				if (count == 0)
					break;
			}
		}

		if (count == 0){
			for (int i = card2/card1; i > 0; --i){
				for (int j = numberInHand - 1; j >= 0; j--){
					if (inHand[j] == card1){
						inHand.erase(inHand.begin() + j);
						--numberInHand;
						break;
					}
				}
			}
			addToHand(card2);
		}
		else{
			std::cerr << "Error: Not Enough " << card1 << " Available for Trade" << std::endl;
		}
	}
	// Error checks
	else if (card1 > card2){
		std::cerr << "Error: Exchange Wrong Way" << std::endl;
	}
	else{
		std::cerr << "Error: Exchange of Two Cards of Same Value" << std::endl;
	}
}

int Hand::trade(int number, card_t card){
	int count = 3;

	// Trade 3 of a kind
	if (number == 3){

		//Verify cards
		for (int i = numberInHand - 1; i >= 0; i--){
			if (inHand[i] == card){
				count--;
				if (count == 0)
					break;
			}
		}

		// Remove + add
		if (count == 0){
			for (int i = number; i > 0; --i){
				for (int j = numberInHand - 1; j >= 0; j--){
					if (inHand[j] == card){
						inHand.erase(inHand.begin() + j);
						--numberInHand;
						break;
					}
				}
			}
			if (tradeCount < 12){
				tradeCount += 2;
			}
			else if (tradeCount == 12){
				tradeCount += 3;
			}
			else{
				tradeCount += 5;
			}
			// To replace addint soldiers
			return tradeCount;
		}
		else{
			std::cerr << "Error: Not Enough " << card << " Available for Trade" << std::endl;
		}
	}
	// Trade 1 of each
	else if (number == 1){
		std::vector<int> pos;

		// Verify cards
		for (int i = numberInHand - 1; i >= 0; i--){
			if (inHand[i] == infantry){
				pos.push_back(i);
				count--;
				break;
			}
		}
		for (int i = numberInHand - 1; i >= 0; i--){
			if (inHand[i] == cavalry){
				pos.push_back(i);
				count--;
				break;
			}
		}
		for (int i = numberInHand - 1; i >= 0; i--){
			if (inHand[i] == artillery){
				pos.push_back(i);
				count--;
				break;
			}
		}

		// Remove + add
		if (count == 0){
			std::sort(pos.begin(), pos.end());
			for (int i = 2; i >= 0; i--){
				inHand.erase(inHand.begin() + pos[i]);
				--numberInHand;
			}

			if (tradeCount < 12){
				tradeCount += 2;
			}
			else if (tradeCount == 12){
				tradeCount += 3;
			}
			else{
				tradeCount += 5;
			}
			// To replace adding soldiers
			return tradeCount;
		}
		else{
			std::cerr << "Error: Not Enough of One Type of Card Available for Trade" << std::endl;
		}
	}

	else{
		std::cerr << "Error: Unknown Exchange Value" << std::endl;
	}
	return 0;
}

int Hand::getNumberInHand() {
	return numberInHand;
}

// Deck constructor
Deck::Deck(int numberOfCountries){

	numberOfCards = numberOfCountries;

	// Place cards in deck
	for (int i = numberOfCards / 3; i > 0; i--){
		cards.push_back(infantry);
	}
	if ((numberOfCards % 3) >= 1){
		cards.push_back(infantry);
	}

	for (int i = numberOfCards / 3; i > 0; i--){
		cards.push_back(artillery);
	}
	if ((numberOfCards % 3) >= 2){
		cards.push_back(cavalry);
	}

	for (int i = numberOfCards / 3; i > 0; i--){
		cards.push_back(cavalry);
	}

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(cards.begin(), cards.end(), std::default_random_engine(seed));
}

// Delete drawn card and add it to hand
void Deck::Draw(Hand* myHand){
	if (numberOfCards > 0){
		card_t temp = cards.back();
		myHand->Hand::addToHand(temp);
		cards.pop_back();
		--numberOfCards;
	}
	else{
		std::cerr << "Error: Deck of Cards is Empty" << std::endl;
	}
}