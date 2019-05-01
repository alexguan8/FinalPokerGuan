#include "Deck.hpp"

using namespace guanpokergame;

#include <algorithm>
#include <ctime>
#include <iostream>

const string suitNames[] = { "Spades", "Hearts", "Clubs", "Diamonds", "Unknown Suit" };

Deck::Deck() {
	for (int i = 0; i < 4; i++) {
		for (int r = 2; r <= 14; r++) {
			if (i == 0) {
				Card temp = Card(r, SPADES);
				cards.push_back(temp);
			}
			else if (i == 1) {
				Card temp = Card(r, HEARTS);
				cards.push_back(temp);
			}
			else if (i == 2) {
				Card temp = Card(r, CLUBS);
				cards.push_back(temp);
			}
			else if (i == 3) {
				Card temp = Card(r, DIAMONDS);
				cards.push_back(temp);
			}
		}
	}
	this->index = 0;
}

void Deck::shuffle() {
	this->index = 0;
	srand(time(0));	//sets seed to current time
	random_shuffle(cards.begin(), cards.end());

	for (int i = 0; i < cards.size(); i++) {
		Card temp = cards[i];
		cout << to_string(temp.getRank()) + " of " + suitNames[temp.getSuit()] << endl;
	}
}

Card Deck::next()
{
	if (index >= 52) return Card();

	Card result = cards[index];
	index++;
	return result;
}

Card Deck::getCurrentCard() {
	return cards[index];
}


