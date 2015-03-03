
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

#if ( OF_VERSION == 6 ) // OF pre007 no bueno
#error This Addon requires at least OF_007
#endif



void drawTextureCropInsideRect(ofTexture * tex,
					  float x, float y, float w, float h,
					  const ofRectangle & bounds,
					  bool debug = false
					  );

ofRectangle getIntersection(const ofRectangle & r1, const ofRectangle & r2);

	#if ( OF_VERSION == 7 ) && (OF_VERSION_MINOR == 0) //OF_0070 doesnt have drawSubsection
		void drawSubsection(float x, float y, float w, float h, float sx, float sy);
		void drawSubsection(float x, float y, float w, float h, float sx, float sy, float _sw, float _sh);
		void drawSubsection(float x, float y, float z, float w, float h, float sx, float sy);
		void drawSubsection(float x, float y, float z, float w, float h, float sx, float sy, float sw, float sh);
	#endif


#endif


