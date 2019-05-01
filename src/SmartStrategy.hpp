#pragma once
using namespace std;

#include <vector>

#include "Card.hpp"

namespace guanpokergame {
	class SmartStrategy {

		//by default members are private
		vector <Card*> cards;

		int heroPosition;

	public:
		//add getter methods

		void setCards(vector <Card> cards);

		void clearCards();

		void computePreflopProbs();

		bool shouldInitiateBluff();
	};
}