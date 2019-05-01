#pragma once
using namespace std;

#include <string>

namespace guanpokergame {
	enum Suit { SPADES, HEARTS, CLUBS, DIAMONDS, UNKNOWNSUIT };
	class Card {
		//by default members are private
		
	public:
		Suit suit;
		int rank;
		
		Card(int rank, Suit suit);
		Card(); //initializes invalid card

		int getRank(); //between 2-14
		void setRank(int value); //between 2-14 (ace)

		/** Converts this card object to a eval index that opmEval can evaluate. */
		int toEvalIndex();
		/** Converts this card object to a file name. */
		string toFilePath();

		Suit getSuit();
		void setSuit(Suit suit);

		/** Overrides to_string to print a card. */
		string to_String();

	};

	int compare(const Card& a, const Card& b);
}