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

string GameEngine::getUserInput() {
	string input;
	cin >> input;

	return input;
}

void GameEngine::goNextRound() {
	if (round == R_PREFLOP) {
		round = R_FLOP;
	}
	else if (round == R_FLOP) {
		round = R_TURN;
	}
	else if (round == R_TURN) {
		round = R_RIVER;
	}
	else if (round == R_RIVER) {
		initialize();
	}
}

void GameEngine::performAction(Action act, int amount) {
	int current = myTable.currentIndex;

	//if player is out, move on
	if (!myTable.players[current].canDecide()) {
		myTable.currentIndex++;
		return;
	}

	if (act == A_CHECK) {
		myTable.players[current].bet(0);
	}
	else if (act == A_FOLD) {
		myTable.players[current].folded = true;
	}
	else if (act == A_CALL) {	//d o something
		myTable.players[current].bet(myTable.getHigh() - myTable.players[current].wager);
	}
	else if (act == A_BET) {
		myTable.players[current].bet(amount);
	}


	myTable.currentIndex++;
}

void GameEngine::playRound() {
	//while we have not gone through everyone
	//and the largest wager is greater than the current players wager
	while (myTable.currentIndex < myTable.players.size()
		|| myTable.getHigh() > myTable.players[myTable.currentIndex].wager) {
		Player currentPlayer = myTable.players[myTable.currentIndex];
		//if player is out, then move on
		if (!currentPlayer.canDecide()) {
			myTable.currentIndex++;
			continue;
		}
		cout << "Hello Player " + myTable.currentIndex + 1;
		//if playing from behind
		if (myTable.getHigh() > currentPlayer.wager) {
			cout << "Will you fold, call or raise?" << endl;
			string response = getUserInput();

			if (response == "fold") {
				performAction(A_FOLD, 0);
			}
			if (response == "call") {
				performAction(A_CALL, 0);
			}
			if (response == "raise") {
				cout << "Raise by how much?" << endl;
				string raiseAmt = getUserInput();
				
				performAction(A_BET, myTable.getHigh() + stoi(raiseAmt));
			}
		}

		//if playing ahead
		if (myTable.getHigh() <= currentPlayer.wager) {
			cout << "Will you fold, check or bet?" << endl;
			string response = getUserInput();

			if (response == "fold") {
				performAction(A_FOLD, 0);
			}
			if (response == "check") {
				performAction(A_CHECK, 0);
			}
			if (response == "bet") {
				cout << "Bet how much?" << endl;
				string betAmt = getUserInput();

				performAction(A_BET, stoi(betAmt));
			}
		}
	}

	goNextRound();
}