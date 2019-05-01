/*using namespace std;

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "GameEngine.hpp"
using namespace guanpokergame;

#include "omp/HandEvaluator.h"
#include <iostream>
using namespace omp;

Card testCard;
Deck testDeck;
Player testPlayer;
Table testTable;

HandEvaluator testEval;

TEST_CASE("tests for card class") {
	testCard = Card(5, DIAMONDS);
	REQUIRE(testCard.getSuit() == 3);
}

TEST_CASE("tests for deck constructor") {
	testDeck = Deck();
	REQUIRE(testDeck.cards.size() == 52);
}

TEST_CASE("tests for deck next()") {
	testDeck = Deck();
	REQUIRE(testDeck.cards.size() == 52);
	REQUIRE(testDeck.next().getRank() == 2);
	REQUIRE(testDeck.next().getRank() == 3);
}

TEST_CASE("tests for deck shuffle") {
	testDeck = Deck();
	testDeck.shuffle();
	Card temp = testDeck.next();
	bool firstCardTest = temp.getRank() != 2 || temp.getSuit() != 0;
	REQUIRE(firstCardTest);
	REQUIRE(testDeck.cards.size() == 52);
}

TEST_CASE("tests for player methods") {
	testPlayer = Player();
	REQUIRE(testPlayer.isCleaned());
}

TEST_CASE("tests for cardToIndex() method") {
	testCard = Card(14, DIAMONDS);
	REQUIRE(testCard.toEvalIndex() == 51);

	testCard = Card(14, SPADES);
	REQUIRE(testCard.toEvalIndex() == 48);

	testCard = Card(2, HEARTS);
	REQUIRE(testCard.toEvalIndex() == 1);

	testCard = Card(4, HEARTS);
	REQUIRE(testCard.toEvalIndex() == 9);
}

TEST_CASE("tests for ompEval library") {
	Hand h = Hand::empty(); // Final hand must include empty() exactly once!
	Hand h2 = Hand::empty();
	h += Hand(51) + Hand(48) + Hand(0) + Hand(1) + Hand(2); // AdAs2s2h2c
	h2 += Hand(0) + Hand(1) + Hand(2);
	REQUIRE(testEval.evaluate(h) == 28684);
}

TEST_CASE("tests for ompEval library comparison") {
	Hand h = Hand::empty(); // Final hand must include empty() exactly once!
	Hand h2 = Hand::empty();
	h += Hand(51) + Hand(48) + Hand(0) + Hand(1) + Hand(2); // AdAs2s2h2c
	h2 += Hand(0) + Hand(1) + Hand(2);
	REQUIRE(testEval.evaluate(h) > testEval.evaluate(h2));
}

TEST_CASE("test for player hand eval") {
	testTable = Table();

	Card holeCard1 = Card(14, DIAMONDS);
	Card holeCard2 = Card(14, SPADES);
	Card flopCard1 = Card(2, SPADES);
	Card flopCard2 = Card(2, CLUBS);
	Card flopCard3 = Card(2, HEARTS);

	testTable.players[0].setCards(holeCard1, holeCard2);
	testTable.drawCard(flopCard1);
	testTable.drawCard(flopCard2);
	testTable.drawCard(flopCard3);

	REQUIRE(testTable.getHandEvaluation(0) == 28684);
}

TEST_CASE("test getting small blind") {
	testTable = Table();
	testPlayer = Player();
	Player testPlayer2 = Player();
	Player testPlayer3 = Player();

	testTable.addPlayer(testPlayer);
	testTable.addPlayer(testPlayer2);
	testTable.addPlayer(testPlayer3);

	REQUIRE(testTable.getSBIndex() == 1);
}

TEST_CASE("test getting big blind") {
	testTable = Table();
	testPlayer = Player();
	Player testPlayer2 = Player();
	Player testPlayer3 = Player();

	testTable.addPlayer(testPlayer);
	testTable.addPlayer(testPlayer2);
	testTable.addPlayer(testPlayer3);

	REQUIRE(testTable.getBBIndex() == 2);
}

TEST_CASE("test getting file name from Card") {
	testCard = Card(3, DIAMONDS);
	REQUIRE(testCard.toFilePath() == "images/3D.png");
}

TEST_CASE("test getting file name from card -- ACE") {
	testCard = Card(14, CLUBS);
	REQUIRE(testCard.toFilePath() == "images/AC.png");
}*/