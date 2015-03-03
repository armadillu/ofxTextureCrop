#pragma once

#include "ofMain.h"
#include "ofxCropTexture.h"

class testApp : public ofBaseApp {
	
public:
	void setup();
	void update(){};
	void draw();


	ofTexture * tex;
	ofVec2f pos;
};


