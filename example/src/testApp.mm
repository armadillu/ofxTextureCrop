#include "testApp.h"


void testApp::setup(){

	//ofxiPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);

	// register touch events
	ofRegisterTouchEvents(this);
		
	ofBackground(0,0,0);
	ofEnableAlphaBlending();

	ofDisableArbTex();
	ofEnableArbTex();
	
	tex = new ofTexture();
	ofLoadImage( *tex, "tex.png" );

	//ofSetRectMode(OF_RECTMODE_CENTER);
}


void testApp::draw(){

	//define a rect where our texture drawing will be constrained into
	int inset = 300;
	ofRectangle bounds = ofRectangle(
									 inset,
									 inset,
									 ofGetWidth() - 2 * inset,
									 ofGetHeight() - 2 * inset
									 );

	//draw our texture, constraining  the drawing to only inside the bounds
	float sx = 1.5 * sinf(ofGetElapsedTimef());
	float sy = 1.5 * sinf( 0.5 * ofGetElapsedTimef());

	ofSetColor(255);
	((ofxCropTexture *)tex)->drawInsideBounds(
												pos.x,						//draw position x
												pos.y,						//draw position y
												sx * tex->getWidth(),		//texture width, can be negative too
												sy * tex->getHeight(),		//tex height, can be negative too
												bounds,						//crop all your drawing into this rect
												true						//debug
											   );

	


	//draw current "rect mode"
	ofSetColor(255);
	ofDrawBitmapString( (ofGetRectMode() == OF_RECTMODE_CORNER ) ? "OF_RECTMODE_CORNER" : "OF_RECTMODE_CENTER",
						20,
						20
					   );

	//draw bounds
	glLineWidth(3);
	ofSetColor(255, 0, 0);
	ofNoFill();
	ofRect(bounds);
	ofFill();
	glLineWidth(1);
}


void testApp::touchMoved(ofTouchEventArgs &touch){
	pos.x = touch.x * 1.5 - ofGetWidth() * 0.5;
	pos.y = touch.y * 1.5 - ofGetHeight() * 0.5;
}


void testApp::touchDoubleTap(ofTouchEventArgs &touch){

	if ( ofGetRectMode() == OF_RECTMODE_CORNER ){
		ofSetRectMode(OF_RECTMODE_CENTER);
	}else{
		ofSetRectMode(OF_RECTMODE_CORNER);
	}
}