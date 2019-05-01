#include "Table.hpp"

using namespace guanpokergame;

const int NUM_PLAYERS = 2;
const int ANTE = 50;

Table::Table() {
	this->dealer = 0;
	this->currentIndex = 1;
	this->pot = 0;
	this->deck = Deck();

	//adds the players
	this->init();

	//puts in the ante
	for (int i = 0; i < players.size(); i++) {
		players[i].bet(ANTE);
	}
}

void Table::addPlayer(Player p) {
	this->players.push_back(p);
}

void Table::drawCard(Card card) {
	this->communityCards.push_back(card);
}

int Table::getHandEvaluation(int playerIndex) {
	if (playerIndex < 0 || playerIndex > players.size() - 1) {
		return -1;
	}
	
	vector <int> fullHand;
	//add hole cards
	for (int i = 0; i < players[playerIndex].holeCards.size(); i++) {
		fullHand.push_back(players[playerIndex].holeCards[i].toEvalIndex());
	}
	//add community cards
	for (int i = 0; i < communityCards.size(); i++) {
		fullHand.push_back(communityCards[i].toEvalIndex());
	}

	HandEvaluator eval;
	Hand h = Hand::empty();

	for (int i = 0; i < fullHand.size(); i++) {
		h += Hand(fullHand[i]);
	}

	return eval.evaluate(h);
}

void Table::init() {
	for (int i = 0; i < NUM_PLAYERS; i++) {
		Player temp = Player();
		addPlayer(temp);
	}
}

void Table::dealHoleCards() {
	for (int i = 0; i < players.size(); i++) {
		cout << "Player " + to_string(i) + " Hole Card added: " + deck.getCurrentCard().to_String() << endl;
		players[i].holeCards.push_back(deck.next());
		cout << "Player " + to_string(i) + " Hole Card added: " + deck.getCurrentCard().to_String() << endl;
		players[i].holeCards.push_back(deck.next());
	}
}

void Table::dealCommunityCards() {
	for (int i = 0; i < 5; i++) {
		communityCards.push_back(deck.next());
	}
}

void Table::deal() {
	clear();
	deck.shuffle();
	dealHoleCards();
	dealCommunityCards();
}

int Table::getHigh() {
	int max = 0;
	for (int i = 0; i < players.size(); i++)
	{
		if (players[i].wager > max) {
			max = players[i].wager;
		}
	}
	return max;
}

int Table::wrap(int index) {
	int high = players.size();

	if (high == 0) {
		return 0;
	}

	if (index < 0) {
		index += ((long)((-index) / high) + 1) * (high);
	}

	if (index >= high) {
		index -= ((long)((index - high) / high) + 1) * (high);
	}

	return index;
}

int Table::getSBIndex() {
	if (players.size() == 2)
	{
		return dealer;
	}
	else
	{
		return wrap(dealer + 1);
	}
}

int Table::getBBIndex() {
	if (players.size() == 2)
	{
		return wrap(dealer + 1);
	}
	else
	{
		return wrap(dealer + 2);
	}
}

void Table::clear() {
	for (int i = 0; i < players.size(); i++) {
		players[i].clearCards();
	}
}

void Table::progress() {
	this->currentIndex = 1;

	for (int i = 0; i < players.size(); i++) {
		pot += players[i].wager;
		players[i].wager = 0;
	}
}


