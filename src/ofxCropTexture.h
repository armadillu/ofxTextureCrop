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


class ofxCropTexture: public ofTexture{

public:


	void drawInsideBounds(float x, float y, float w, float h, ofRectangle bounds, bool debug = false){

		ofRectangle tex = ofRectangle(x,y,w,h);
		ofRectangle intersection = bounds.getIntersection(tex);
		ofRectangle offset = ofRectangle( x, y, bounds.x - x, bounds.y - y );

		ofVec2f min, max;

		if(offset.width>0){
			min.x = -offset.width;
		}else{
			min.x = 0;
		}
		max.x = intersection.width;


		if(offset.height>0){
			min.y = -offset.height;
		}else{
			min.y = 0;
		}
		max.y = intersection.height ;


		if(debug){
			ofSetColor(255,96);
			draw(x, y, w, h);
			ofSetColor(255);
		}

		drawSubsection(
					   intersection.x, intersection.y,
					   intersection.width, intersection.height,
					   -min.x ,
					   -min.y ,
					   max.x,
					   max.y
					   );

		if(debug){

			ofNoFill();
			ofSetColor(255, 0, 0);
			ofRect(bounds);

			ofSetColor(0, 0, 255);
			ofRect(tex);

			ofSetColor(0, 255, 0);
			ofRect(intersection);

			ofSetColor(255, 255, 0);
			ofRect(offset);

			string ss = ofToString(offset.x) + ", " + ofToString(offset.y) + ", " +
			ofToString(offset.width) + ", " + ofToString(offset.height);

			ofFill();

			ofDrawBitmapString( ofToString(min.x) + ", " + ofToString(min.y) + ", " + ofToString(max.x) + ", " + ofToString(max.x),
							   bounds.x + 5, bounds.y - 5);
		}
	}

#if ( OF_VERSION == 7 ) && (OF_VERSION_MINOR == 0) //OF_0070 doesnt have drawSubsection


	//------------------------------------
	void drawSubsection(float x, float y, float w, float h, float sx, float sy){
		drawSubsection(x,y,0,w,h,sx,sy,w,h);
	}

	//------------------------------------
	void drawSubsection(float x, float y, float w, float h, float sx, float sy, float _sw, float _sh){
		drawSubsection(x,y,0,w,h,sx,sy,_sw,_sh);
	}

	//------------------------------------
	void drawSubsection(float x, float y, float z, float w, float h, float sx, float sy){
		drawSubsection(x,y,z,w,h,sx,sy,w,h);
	}


	//----------------------------------------------------------
	void drawSubsection(float x, float y, float z, float w, float h, float sx, float sy, float sw, float sh) {

		// make sure we are on unit 0 - we may change this when setting shader samplers
		// before glEnable or else the shader gets confused
		/// ps: maybe if bUsingArbTex is enabled we should use glActiveTextureARB?
		glActiveTexture(GL_TEXTURE0);

		// Enable texturing
		glEnable(texData.textureTarget);

		// bind the texture
		glBindTexture( texData.textureTarget, (GLuint)texData.textureID );

		GLfloat px0 = 0.0f;		// up to you to get the aspect ratio right
		GLfloat py0 = 0.0f;
		GLfloat px1 = w;
		GLfloat py1 = h;

		if (texData.bFlipTexture == true){
			GLint temp = (GLint)py0;
			py0 = py1;
			py1 = temp;
		}

		// for rect mode center, let's do this:
		if (ofGetRectMode() == OF_RECTMODE_CENTER){
			px0 = -w/2;
			py0 = -h/2;
			px1 = +w/2;
			py1 = +h/2;
		}

		//we translate our drawing points by our anchor point.
		//we still respect ofRectMode so if you have rect mode set to
		//OF_RECTMODE_CENTER your anchor will be relative to that.
		GLfloat anchorX;
		GLfloat anchorY;

		if(bAnchorIsPct){
			anchorX = anchor.x * w;
			anchorY = anchor.y * h;
		}else{
			anchorX = anchor.x;
			anchorY = anchor.y;
		}

		px0 -= anchorX;
		py0 -= anchorY;
		px1 -= anchorX;
		py1 -= anchorY;


		// -------------------------------------------------
		// complete hack to remove border artifacts.
		// slightly, slightly alters an image, scaling...
		// to remove the border.
		// we need a better solution for this, but
		// to constantly add a 2 pixel border on all uploaded images
		// is insane..

		GLfloat offsetw = 0.0f;
		GLfloat offseth = 0.0f;

		/*
		if (texData.textureTarget == GL_TEXTURE_2D && bTexHackEnabled) {
			offsetw = 1.0f / (texData.tex_w);
			offseth = 1.0f / (texData.tex_h);
		}
		*/
		// -------------------------------------------------

		ofPoint topLeft = getCoordFromPoint(sx, sy);
		ofPoint bottomRight = getCoordFromPoint(sx + sw, sy + sh);

		GLfloat tx0 = topLeft.x + offsetw;
		GLfloat ty0 = topLeft.y + offseth;
		GLfloat tx1 = bottomRight.x - offsetw;
		GLfloat ty1 = bottomRight.y - offseth;

		glPushMatrix();

		glTranslatef(x,y,z);

		GLfloat tex_coords[] = {
			tx0,ty0,
			tx1,ty0,
			tx1,ty1,
			tx0,ty1
		};
		GLfloat verts[] = {
			px0,py0,
			px1,py0,
			px1,py1,
			px0,py1
		};

		glEnableClientState( GL_TEXTURE_COORD_ARRAY );
		glTexCoordPointer(2, GL_FLOAT, 0, tex_coords );
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(2, GL_FLOAT, 0, verts );
		glDrawArrays( GL_TRIANGLE_FAN, 0, 4 );
		glDisableClientState( GL_TEXTURE_COORD_ARRAY );
		
		glPopMatrix();
		glDisable(texData.textureTarget);
		
	}

#endif
	
};

#endif
