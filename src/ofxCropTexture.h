
//
//  CropTexture.h
//  emptyExample
//
//  Created by Oriol Ferrer Mesià on 17/01/13.
//
//

#ifndef emptyExample_CropTexture_h
#define emptyExample_CropTexture_h

#include "ofMain.h"
#include "ofTexture.h"

#if ( OF_VERSION == 6 ) // OF pre007 no bueno
#error This Addon requires at least OF_007
#endif

class ofxCropTexture: public ofTexture{

	public:

		ofxCropTexture& operator=(const ofTexture & mom);

		void drawInsideBounds(float x, float y, float w, float h, ofRectangle bounds = ofRectangle(0,0, ofGetWidth(), ofGetHeight()), bool debug = false);

	#if ( OF_VERSION == 7 ) && (OF_VERSION_MINOR == 0) //OF_0070 doesnt have drawSubsection
		void drawSubsection(float x, float y, float w, float h, float sx, float sy);
		void drawSubsection(float x, float y, float w, float h, float sx, float sy, float _sw, float _sh);
		void drawSubsection(float x, float y, float z, float w, float h, float sx, float sy);
		void drawSubsection(float x, float y, float z, float w, float h, float sx, float sy, float sw, float sh);
	#endif

};


#endif


