#include "testApp.h"


void testApp::setup(){	
	// register touch events
	ofRegisterTouchEvents(this);
		
	ofBackground(0,0,0);
	ofEnableAlphaBlending();

	ofDisableArbTex();
	ofEnableArbTex();
	
	tex = new ofTexture();
	ofLoadImage( *tex, "tex.png" );
}


void testApp::draw(){

	ofSetColor(255);
	int off = 200;

	((ofxCropTexture *)tex)->drawInsideBounds(	pos.x, pos.y,
							tex->getWidth() * 0.6, tex->getHeight() * 0.6,
							ofRectangle(off,off, ofGetWidth() - 2 * off, ofGetHeight() - 2 * off),
							true
						  );

}


void testApp::touchMoved(ofTouchEventArgs &touch){
	pos.x = touch.x * 1.4 - 200;
	pos.y = touch.y * 1.4 - 200;
}
