#include "GameEngine.hpp"

using namespace guanpokergame;

void GameEngine::initialize() {
	this->round = R_PREFLOP;

	myTable = Table();
	myTable.deal();
}

vector <Card> GameEngine::getHoleCardsOfPlayer(int player) {
	return myTable.players[player].holeCards;
}

int GameEngine::getUserInput() {
	int input;
	cin >> input;

	return input;
}

void GameEngine::startRound() {
	
}

void GameEngine::performAction(Action act, int amount) {
	int current = myTable.currentIndex;
	if (act == A_CHECK) {
		myTable.players[current].bet(0);
	}
	else if (act == A_FOLD) {
		myTable.players[current].folded = true;
	}
	else if (act == A_CALL) {
		myTable.players[current].bet(myTable.getHigh() - myTable.players[current].wager);
	}
	else if (act == A_BET) {
		myTable.players[current].bet(amount);
	}


	myTable.currentIndex++;
}