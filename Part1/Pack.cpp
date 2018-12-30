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
void Hand::Exchange(card_t card1, card_t card2){

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
	//delete card1
	//add card2 card1/card2 times
	else if (card1 > card2){
		for (int i = numberInHand-1; i >= 0; i--){
			if (inHand[i] == card1){
				inHand.erase(inHand.begin()+i);
				--numberInHand;
				for (int j = card1/card2; j > 0; j--){
					addToHand(card2);
				}
				break;
			}
			else{
				if (i == 0){
					std::cerr << "Error: There are no " << card1 << " Available for Trade" << std::endl;
				}
			}
		}
	}
	else{
		std::cerr << "Error: Exchange of Two Cards of Same Value" << std::endl;
	}
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