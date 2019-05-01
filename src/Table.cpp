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

	//put in ante
	for (int i = 0; i < players.size(); i++) {
		players[i].bet(ANTE);
	}

	pot = 0;
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
		players[i].folded = false;
	}
}

void Table::progressRound() {
	this->currentIndex = 1;

	for (int i = 0; i < players.size(); i++) {
		pot += players[i].wager;
		players[i].wager = 0;
	}
}

int Table::getWinner() {
	int p1Eval = getHandEvaluation(0);
	int p2Eval = getHandEvaluation(1);

	if (p1Eval > p2Eval) {
		return 0;
	}
	else if (p1Eval == p2Eval) {
		return -1;
	}
	else {
		return 1;
	}
}

void Table::progressGame() {
	//check if game is progressing bc of folds
	int playerFolded = -1;
	for (int i = 0; i < players.size(); i++) {
		if (players[i].folded) {
			playerFolded = i;
		}
	}

	int winner = getWinner();

	//the person who did not fold collects all the wagers and the pot
	if (playerFolded >= 0) {
		players[wrap(playerFolded + 1)].stack += pot + players[playerFolded].wager + players[wrap(playerFolded + 1)].wager;
	} 
	else if (winner == -1) {	//split pot if no winner (same hand)
		int split = pot / players.size();
		for (int i = 0; i < players.size(); i++) {
			players[i].stack += split;
		}
	}	//otherwise winner takes entire pot
	else {
		players[winner].stack += pot;
	}

	this->currentIndex = 1;

	for (int i = 0; i < players.size(); i++) {
		pot += players[i].wager;
		players[i].wager = 0;
	}

	deal();

}

