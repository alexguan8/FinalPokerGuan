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

	loadCardImages();

	//gui stuff below
	gui = new ofxDatGui(ofxDatGuiAnchor::TOP_RIGHT);

	// add some components //
	gui->addTextInput("message", "# open frameworks #");

	gui->addFRM();
	gui->addBreak();

	// add a folder to group a few components together //
	ofxDatGuiFolder* folder = gui->addFolder("white folder", ofColor::white);
	folder->addTextInput("** input", "nested input field");
	folder->addSlider("** slider", 0, 100);
	folder->addToggle("** toggle");
	folder->addColorPicker("** picker", ofColor::fromHex(0xFFD00B));
	// let's have it open by default. note: call this only after you're done adding items //
	folder->expand();

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
	//player 1
	backgroundTable.draw(0, 0, 2560, 1920);
	p1holeCard1.draw(2000,800, 120, 200);
	p1holeCard2.draw(1880, 800, 120, 200);
	ofDrawBitmapString("Player 1", 1950, 1050);


	//player 2
	p2holeCard1.draw(600, 800, 120, 200);
	p2holeCard2.draw(480, 800, 120, 200);
	ofDrawBitmapString("Player 2", 550, 1050);

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
	
	//betting chips
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
			engine.initialize();
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
