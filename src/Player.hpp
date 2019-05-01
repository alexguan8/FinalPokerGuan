#pragma once
using namespace std;

#include <vector>

#include "Card.hpp"

namespace guanpokergame {
	class Player {

		//by default members are private

	public:
		/** Default constructor. */
		Player();
		/** Constructor for player controlled by smart strategy. */
		//Player(Strategy strat);
		/** The cards that the player begins with. */
		vector <Card> holeCards;
		/** The amount of chips that this player has. */
		int stack; 
		/** The amount put into the current pot. */
		int wager;
		/**whether the player has folded this round*/
		bool folded; 
		/** Is out of money and has no wager. */
		bool isCleaned();
		/** Stack is 0 because of wager. */
		bool isAllIn();
		/** If they still have a stack and have not folded. */
		bool canDecide();

		void setCards(Card card1, Card card2);

		void clearCards();

		void bet(int amount);
	};
}