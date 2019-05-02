#include "Player.hpp"

using namespace guanpokergame;

const int BUY_IN = 1000;

Player::Player() {
	this->stack = BUY_IN;
	this->wager = 0;
	this->folded = false;
}

void Player::setCards(Card card1, Card card2)
{
	holeCards.clear();
	holeCards.push_back(card1);
	holeCards.push_back(card2);
}

bool Player::canDecide() {
	return stack > 0 && !folded;
}

bool Player::isAllIn() {
	return stack <= 0 && wager > 0;
}

bool Player::isCleaned() {
	if (stack < 0) {
		return true;
	}
	else {
		return stack == 0 && wager <= 0;
	}
	
}

void Player::clearCards() {
	holeCards.clear();
}

void Player::bet(int amount) {
	wager += amount;
	stack -= amount;
}


