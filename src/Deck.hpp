#pragma once
using namespace std;

#include <vector>

#include "Card.hpp"

namespace guanpokergame {
	class Deck {

		//by default members are private
	public:
		//add getter methods

		vector <Card> cards;
		int index;

		Deck();
		void shuffle();
		Card next();

		Card getCurrentCard();
	};
}