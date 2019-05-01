#pragma once
using namespace std;

#include <vector>

#include "Table.hpp"

/*
#include "omp/HandEvaluator.h"
#include <iostream>
using namespace omp;*/

namespace guanpokergame {
	enum Round { R_PREFLOP, R_FLOP, R_TURN, R_RIVER, R_SHOWDOWN };
	enum Action { A_CHECK, A_FOLD, A_CALL, A_BET };
	class GameEngine {

		//by default members are private
		
	public:
		//getter methods

		//game logic methods

		Table myTable;

		Round round;

		vector <Card> getHoleCardsOfPlayer(int player);

		/** Resets round and deals. */
		void initialize();

		string getUserInput();

		Action getUserAction();

		void performAction(Action act, int amount);

		void playRound();

		void goNextRound();
	};
}