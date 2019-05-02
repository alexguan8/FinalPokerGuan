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
		myTable.progressRound();
	}
	else if (round == R_FLOP) {
		round = R_TURN;
		myTable.progressRound();
	}
	else if (round == R_TURN) {
		round = R_RIVER;
		myTable.progressRound();
	}
	else if (round == R_RIVER) {
		resetGame();
	}

}

void GameEngine::resetGame() {
	myTable.progressGame();
	this->round = R_PREFLOP;
}

void GameEngine::performAction(Action act, int amount) {
	int current = myTable.currentIndex;
	int currentWrapped = myTable.wrap(current);

	//if player is out, move on
	if (!myTable.players[currentWrapped].canDecide()) {
		myTable.currentIndex++;
		return;
	}

	if (act == A_CHECK) {
		if (myTable.players[currentWrapped].wager < myTable.getHigh()) {
			return;
		}
		myTable.players[currentWrapped].bet(0);
	}
	else if (act == A_FOLD) {
		myTable.players[currentWrapped].folded = true;
		resetGame();
		return;
	}
	else if (act == A_CALL) {
		myTable.players[currentWrapped].bet(myTable.getHigh() - myTable.players[currentWrapped].wager);
	}
	else if (act == A_BET) {
		//if invalid bet sizing, return
		if (myTable.players[currentWrapped].wager + amount < myTable.getHigh()) {
			return;
		}
		myTable.players[currentWrapped].bet(amount);
	}

	//if we've gone through everyone and everyone's either
	//limped or folded, then we continue
	int nextPlayer = myTable.wrap(current + 1);
	if (current >= myTable.players.size()
		&& myTable.getHigh() <= myTable.players[nextPlayer].wager) {
		goNextRound();
	}
	else {
		myTable.currentIndex++;
	}
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