#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"
#include <iostream>
#include "GameEngine.hpp"

using namespace guanpokergame;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void loadCardImages();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		//Game Logic stuff
		GameEngine engine;

		//SPRITES AND IMAGES
		ofImage p1holeCard1;
		ofImage p1holeCard2;
		ofImage p2holeCard1;
		ofImage p2holeCard2;

		ofImage communityCard1;
		ofImage communityCard2;
		ofImage communityCard3;
		ofImage communityCard4;
		ofImage communityCard5;

		ofImage p1WagerImg;
		ofImage p2WagerImg;

		ofImage potImg;
		ofImage turnImg;

		ofImage backgroundTable;

		//AUDIO
		ofSoundPlayer backgroundMusic;

		//datxgui
		ofxDatGui* gui;
		ofxDatGuiTextInput* myInput;

		void onTextInputEvent(ofxDatGuiTextInputEvent e);
		void onButtonEvent(ofxDatGuiButtonEvent e);
};

class CustomTheme : public ofxDatGuiTheme {
public:
	CustomTheme() {
		font.size = 12;
		layout.height = 35;
		layout.width = 400;
		layout.upperCaseLabels = false;
		init();
	}
};