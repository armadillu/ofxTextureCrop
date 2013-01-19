#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "ofxCropTexture.h"

class testApp : public ofxiPhoneApp {
	
public:
	void setup();
	void update(){};
	void draw();

	void touchDown(ofTouchEventArgs &touch){};
	void touchMoved(ofTouchEventArgs &touch);
	void touchUp(ofTouchEventArgs &touch){};
	void touchDoubleTap(ofTouchEventArgs &touch);
	void touchCancelled(ofTouchEventArgs &touch){};

	ofTexture * tex;
	ofVec2f pos;
};


