using namespace std;

#include "Card.hpp"
using namespace guanpokergame;

string suitNames[] = { "Spades", "Hearts", "Clubs", "Diamonds", "Unknown Suit" };

Card::Card(int rank, Suit suit) {
	this -> suit = suit;
	this -> rank = rank;
}

Card::Card() //creates invalid card
{
	this->rank = -1;
	this->suit = UNKNOWNSUIT;
}

int Card::getRank() {
	return rank;
}

void Card::setRank(int value) {
	this->rank = value;
}

Suit Card::getSuit() {
	return suit;
}

void Card::setSuit(Suit suit) {
	this->suit = suit;
}

int Card::toEvalIndex() {
	//(rank-1)*4 is the number of cards before you get to
	//the correct rank
	//ex: 2s2h2c2d3s3h3c3d...etc
	return (rank - 1) * 4 - (4 - suit);
}

string Card::toFilePath() {
	string suitFileName = "";
	string rankFileName = "";

	if (suit == SPADES) {
		suitFileName = "S";
	} else if (suit == HEARTS) {
		suitFileName = "H";
	} else if (suit == CLUBS) {
		suitFileName = "C";
	} else if (suit == DIAMONDS) {
		suitFileName = "D";
	} else if (suit == UNKNOWNSUIT) {
		suitFileName = "";
	}

	if (rank <= 13) {
		rankFileName = to_string(rank);
	} else if (rank == 14) {
		rankFileName = "A";
	}

	return "images/" + rankFileName + suitFileName + ".png";
	
}

string Card::to_String() {
	return to_string(rank) + " of " + suitNames[suit];
}

int compare(const Card& a, const Card& b) {
	if (a.rank > b.rank) return 1;
	if (a.rank < b.rank) return -1;
	else return 0;
}
