#pragma once
using namespace std;

#include <vector>

#include "Card.hpp"
#include "Player.hpp"
#include "Deck.hpp"

#include "omp/HandEvaluator.h"
#include <iostream>
using namespace omp;

namespace guanpokergame {
	class Table {

		//by default members are private
	public:
		/** Default constructor. */
		Table();
		/** Vector of players. */
		vector <Player> players;
		Deck deck;
		void addPlayer(Player p);
		/** Index of dealer. */
		int dealer;
		/** Index of current player making decision. */
		int currentIndex;
		/** The amount in the pot. */
		int pot;
		/** The community cards dealt on the board. */
		vector <Card> communityCards;

		void drawCard(Card card);

		int getHandEvaluation(int playerIndex);

		int getWinner(vector <int> players);

		int getPot();
		/** Gets the highest wager in the current round. */
		int getHigh();
		/** Gets index of big blind. */
		int getBBIndex();
		/** Gets index of small blind. */
		int getSBIndex();
		/** Gets the true index wrapped for multiple cycles. */
		int wrap(int index);

		void clear();
		void init();

		void dealHoleCards();
		void dealCommunityCards();
		void deal();
	};
}