#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGlutWindow.h"
//========================================================================
int main( ){
	ofSetupOpenGL(500,1000,OF_WINDOW);			// <-------- setup the GL context
    ofAppGlutWindow window;
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
