/*using namespace std;

#include <iostream>
#include "GameEngine.hpp"
#include "ofMain.h"
#include "ofApp.h"

using namespace guanpokergame;

#include "omp/HandEvaluator.h"
#include <iostream>
using namespace omp;


int main() {

	HandEvaluator eval;
	Hand h = Hand::empty(); // Final hand must include empty() exactly once!
	h += Hand(51) + Hand(48) + Hand(0) + Hand(1) + Hand(2); // AdAs2s2h2c
	std::cout << eval.evaluate(h) << std::endl; // 28684 = 7 * 4096 + 12


	//default shit
	ofSetupOpenGL(2560, 1920, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}*/