#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//game logic
	engine.initialize();

	//audio
	backgroundMusic.load("music.mp3");
	backgroundMusic.setLoop(true); //Sound will loop
	backgroundMusic.play();

	//images
	backgroundTable.load("images/table.png");
	p1WagerImg.load("images/chips.png");
	p2WagerImg.load("images/chips.png");
	potImg.load("images/pot.png");
	turnImg.load("images/turn.png");

	loadCardImages();

	//gui stuff below
	gui = new ofxDatGui(ofxDatGuiAnchor::TOP_RIGHT);
	gui->addHeader(":: Drag Me To Reposition ::");

	// add some components //
	gui->addTextInput("Bet/Raise Amount", "# open frameworks #");
	gui->addButton("Check");
	gui->addButton("Fold");
	gui->addButton("Call");

	gui->addFRM();
	gui->addBreak();

	// once the gui has been assembled, register callbacks to listen for component specific events //
	gui->onTextInputEvent(this, &ofApp::onTextInputEvent);
	gui->onButtonEvent(this, &ofApp::onButtonEvent);
	

	gui->setOpacity(gui->getSlider("datgui opacity")->getScale());
}

void ofApp::onTextInputEvent(ofxDatGuiTextInputEvent e)
{
	cout << "onTextInputEvent: " << e.target->getLabel() << " " << e.target->getText() << endl; 
	string out = e.target->getText();
	if (out.size() > 0) {
		engine.performAction(A_BET, stoi(out));
	}
}

void ofApp::onButtonEvent(ofxDatGuiButtonEvent e)
{
	cout << "onButtonEvent: " << e.target->getLabel() << endl;
	if (e.target->getLabel() == "Check") {
		engine.performAction(A_CHECK, 0);
	}
	else if (e.target->getLabel() == "Call") {
		engine.performAction(A_CALL, 0);
	}
	else if (e.target->getLabel() == "Fold") {
		engine.performAction(A_FOLD, 0);
	}
}

void ofApp::loadCardImages() {
	p1holeCard1.load(engine.getHoleCardsOfPlayer(0)[0].toFilePath());
	cout << "Loading " + engine.getHoleCardsOfPlayer(0)[0].toFilePath();
	p1holeCard2.load(engine.getHoleCardsOfPlayer(0)[1].toFilePath());
	cout << "Loading " + engine.getHoleCardsOfPlayer(0)[1].toFilePath();

	p2holeCard1.load(engine.getHoleCardsOfPlayer(1)[0].toFilePath());
	cout << "Loading " + engine.getHoleCardsOfPlayer(1)[0].toFilePath();
	p2holeCard2.load(engine.getHoleCardsOfPlayer(1)[1].toFilePath());
	cout << "Loading " + engine.getHoleCardsOfPlayer(1)[1].toFilePath();

	communityCard1.load(engine.myTable.communityCards[0].toFilePath());
	communityCard2.load(engine.myTable.communityCards[1].toFilePath());
	communityCard3.load(engine.myTable.communityCards[2].toFilePath());
	communityCard4.load(engine.myTable.communityCards[3].toFilePath());
	communityCard5.load(engine.myTable.communityCards[4].toFilePath());
}

//--------------------------------------------------------------
void ofApp::update(){
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	for (int i = 0; i < engine.myTable.players.size(); i++) {
		if (engine.myTable.players[i].isCleaned()) {
			ofDrawBitmapString("Player " + to_string(i + 1) + "has lost", 1240, 500);
		}
	}

	//player 1
	backgroundTable.draw(0, 0, 2560, 1920);
	p1holeCard1.draw(2000,800, 120, 200);
	p1holeCard2.draw(1880, 800, 120, 200);
	ofDrawBitmapString("Player 1", 1950, 1050);

	int p1Stack = engine.myTable.players[0].stack;
	ofDrawBitmapString("Stack: $" + to_string(p1Stack), 1950, 1100);


	//player 2
	p2holeCard1.draw(600, 800, 120, 200);
	p2holeCard2.draw(480, 800, 120, 200);
	ofDrawBitmapString("Player 2", 550, 1050);

	int p2Stack = engine.myTable.players[1].stack;
	ofDrawBitmapString("Stack: $" + to_string(p2Stack), 550, 1100);

	//pot drawing logic
	int pot = engine.myTable.pot;
	if (pot > 0) {
		potImg.draw(1200, 1100, 120, 120);
		ofDrawBitmapString("$" + to_string(pot), 1250, 1250);
	}


	//community card logic
	if (engine.round == R_FLOP) {
		communityCard1.draw(1000, 800, 120, 200);
		communityCard2.draw(1120, 800, 120, 200);
		communityCard3.draw(1240, 800, 120, 200);
	}
	else if (engine.round == R_TURN) {
		communityCard1.draw(1000, 800, 120, 200);
		communityCard2.draw(1120, 800, 120, 200);
		communityCard3.draw(1240, 800, 120, 200);
		communityCard4.draw(1360, 800, 120, 200);
	}
	else if (engine.round == R_RIVER) {
		communityCard1.draw(1000, 800, 120, 200);
		communityCard2.draw(1120, 800, 120, 200);
		communityCard3.draw(1240, 800, 120, 200);
		communityCard4.draw(1360, 800, 120, 200);
		communityCard5.draw(1480, 800, 120, 200);
	}
	else if (engine.round == R_SHOWDOWN) {
		communityCard1.draw(1000, 800, 120, 200);
		communityCard2.draw(1120, 800, 120, 200);
		communityCard3.draw(1240, 800, 120, 200);
		communityCard4.draw(1360, 800, 120, 200);
		communityCard5.draw(1480, 800, 120, 200);
	}
	
	//betting chips drawing
	int p1wager = engine.myTable.players[0].wager;
	if (p1wager > 0) {
		p1WagerImg.draw(1700, 800, 120, 200);
		ofDrawBitmapString(to_string(p1wager), 1750, 800);
	}
	int p2wager = engine.myTable.players[1].wager;
	if (p2wager > 0) {
		p2WagerImg.draw(740, 800, 120, 200);
		ofDrawBitmapString(to_string(p2wager), 800, 800);
	}

	//draw whos turn it is
	if (engine.myTable.wrap(engine.myTable.currentIndex) == 0) {
		turnImg.draw(1950, 580, 120, 200);
		ofDrawBitmapString("Player 1 turn", 1240, 450);
	}
	if (engine.myTable.wrap(engine.myTable.currentIndex) == 1) {
		turnImg.draw(520, 580, 120, 200);
		ofDrawBitmapString("Player 2 turn", 1240, 450);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == ' ') {
		if (engine.round == R_PREFLOP) {
			engine.round = R_FLOP;
		}
		else if (engine.round == R_FLOP) {
			engine.round = R_TURN;
		}
		else if (engine.round == R_TURN) {
			engine.round = R_RIVER;
		}
		else if (engine.round == R_RIVER) {
			engine.resetGame();
			loadCardImages();
		}
	}

	/*
	if (key == 's') {
		engine.playRound();
	}*/
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
