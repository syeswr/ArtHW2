#pragma once

#include "ofMain.h"
#include "ofxOpenNI.h"

class ofApp : public ofBaseApp{
	private:
		ofxOpenNI kinect;

	public:
		void setup();
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
    private:
    
        void handEvent(ofxOpenNIHandEvent & event);
        int initialCounter = 0;
        bool ballFalling = false;
        int startFallTime = 0;
        int time = 0;
        int ballX = 0;
        int ballY = 0;
        int prevBallFall = 0;
        bool initialScreen = true;
        ofPoint leftHandPos;
        ofPoint rightHandPos;
        ofxOpenNI openNIDevice;
        ofTrueTypeFont verdana;
		vector<ofColor> backColors;
        vector<int> notes;
        int hitting = 0;
        int s0 = 0;
        int s1 = 0;
        int s2 = 0;
        int s3 = 0;
        int s4 = 0;
        int c0 = 0;
        int c1 = 0;
        int c2 = 0;
        int c3 = 0;
        int c4 = 0;
        int next = -1;
        int playing  = -1;
        ofSoundPlayer doS;
        ofSoundPlayer riS;
        ofSoundPlayer miS;
        ofSoundPlayer faS;
        ofSoundPlayer soS;
};
