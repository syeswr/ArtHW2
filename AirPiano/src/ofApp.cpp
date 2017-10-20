#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    doS.load(ofFilePath::getAbsolutePath( ofToDataPath("")) + "do.wav");
    riS.load(ofFilePath::getAbsolutePath( ofToDataPath("")) + "ri.wav");
    miS.load(ofFilePath::getAbsolutePath( ofToDataPath("")) + "mi.wav");
    faS.load(ofFilePath::getAbsolutePath( ofToDataPath("")) + "fa.wav");
    soS.load(ofFilePath::getAbsolutePath( ofToDataPath("")) + "so.wav");
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    openNIDevice.setup();
    openNIDevice.addImageGenerator();
    openNIDevice.addDepthGenerator();
    openNIDevice.setRegister(true);
    openNIDevice.setMirror(true);
    
    // setup the hand generator
    openNIDevice.addHandsGenerator();
    
    // add all focus gestures (ie., wave, click, raise arm)
    openNIDevice.addAllHandFocusGestures();
    
    // or you can add them one at a time
    //vector<string> gestureNames = openNIDevice.getAvailableGestures(); // you can use this to get a list of gestures
    // prints to console and/or you can use the returned vector
    //openNIDevice.addHandFocusGesture("Wave");
    
    openNIDevice.setMaxNumHands(4);
    
    for(int i = 0; i < openNIDevice.getMaxNumHands(); i++){
        ofxOpenNIDepthThreshold depthThreshold = ofxOpenNIDepthThreshold(0, 0, false, true, true, true, true);
        // ofxOpenNIDepthThreshold is overloaded, has defaults and can take a lot of different parameters, eg:
        // (ofxOpenNIROI OR) int _nearThreshold, int _farThreshold, bool _bUsePointCloud = false, bool _bUseMaskPixels = true,
        // bool _bUseMaskTexture = true, bool _bUseDepthPixels = false, bool _bUseDepthTexture = false,
        // int _pointCloudDrawSize = 2, int _pointCloudResolution = 2
        openNIDevice.addDepthThreshold(depthThreshold);
    }
    openNIDevice.start();
    //Color theme
    backColors.push_back(ofColor(44,99,145));
    backColors.push_back(ofColor(31,75,109));
    backColors.push_back(ofColor(67,145,204));
    backColors.push_back(ofColor(223,108,100));
    backColors.push_back(ofColor(237,209,72));
    //Push london brigde to the notes
    notes.push_back(5);
    notes.push_back(5);
    notes.push_back(5);
    notes.push_back(4);
    notes.push_back(3);
    notes.push_back(4);
    notes.push_back(5);
    notes.push_back(2);
    notes.push_back(3);
    notes.push_back(4);
    notes.push_back(3);
    notes.push_back(4);
    notes.push_back(5);
    notes.push_back(5);
    notes.push_back(5);
    notes.push_back(5);
    notes.push_back(4);
    notes.push_back(3);
    notes.push_back(4);
    notes.push_back(5);
    notes.push_back(2);
    notes.push_back(5);
    notes.push_back(3);
    notes.push_back(1);
    verdana.loadFont(ofToDataPath("verdana.ttf"), 24);
}

//--------------------------------------------------------------
void ofApp::update(){
    openNIDevice.update();
    
    // reset all depthThresholds to 0,0,0
    for(int i = 0; i < openNIDevice.getMaxNumHands(); i++){
        ofxOpenNIDepthThreshold & depthThreshold = openNIDevice.getDepthThreshold(i);
        ofPoint leftBottomNearWorld = ofPoint(0,0,0);
        ofPoint rightTopFarWorld = ofPoint(0,0,0);
        ofxOpenNIROI roi = ofxOpenNIROI(leftBottomNearWorld, rightTopFarWorld);
        depthThreshold.setROI(roi);
    }
    
    // iterate through users
    for (int i = 0; i < openNIDevice.getNumTrackedHands(); i++){
        
        // get a reference to this user
        ofxOpenNIHand & hand = openNIDevice.getTrackedHand(i);
        
        // get hand position
        ofPoint & handWorldPosition = hand.getWorldPosition(); // remember to use world position for setting ROIs!!!
        
        // set depthThresholds based on handPosition
        ofxOpenNIDepthThreshold & depthThreshold = openNIDevice.getDepthThreshold(i); // we just use hand index for the depth threshold index
        ofPoint leftBottomNearWorld = handWorldPosition - 100; // ofPoint has operator overloading so it'll subtract/add 50 to x, y, z
        ofPoint rightTopFarWorld = handWorldPosition + 100;
        
        ofxOpenNIROI roi = ofxOpenNIROI(leftBottomNearWorld, rightTopFarWorld);
        depthThreshold.setROI(roi);
        
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255, 255, 255);
    time++;
    ofPushMatrix();
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    //baseBackground
    ofSetColor(backColors[0].r+c0,backColors[0].g+c0,backColors[0].b+c0);
    ofDrawRectangle(0, 0-s0/2, 500, 200+s0/2);
    ofSetColor(backColors[1].r+c1,backColors[1].g+c1,backColors[1].b+c1);
    ofDrawRectangle(0, 200-s1/2, 500,200+s1/2);
    ofSetColor(backColors[2].r+c2,backColors[2].g+c2,backColors[2].b+c2);
    ofDrawRectangle(0, 400-s2/2, 500,200+s2/2);
    ofSetColor(backColors[3].r+c3,backColors[3].g+c3,backColors[3].b+c3);
    ofDrawRectangle(0, 600-s3/2, 500,200+s3/2);
    ofSetColor(backColors[4].r+c4,backColors[4].g+c4,backColors[4].b+c4);
    ofDrawRectangle(0, 800-s4/2, 500,200+s4/2);
    //Highlight hind for next note
    if(next<notes.size()){
        if(notes[next]==1){
            c0 = 50;
        }
        if(notes[next]==2){
            c1 = 50;
        }
        if(notes[next]==3){
            c2 = 50;
        }
        if(notes[next]==4){
            c3 = 50;
        }
        if(notes[next]==5){
            c4 = 50;
        }
        
    }
    int handNum = openNIDevice.getNumTrackedHands();
    if ((handNum == 0) && (initialScreen == true)){
        string msg = "Put hand-in";
        verdana.drawString(msg, 20, 800 - 20);
        initialScreen = false;
    }

    else if(handNum == 2){
        // iterate through users
        for (int i = 0; i < openNIDevice.getNumTrackedHands(); i++){
            
            // get a reference to this user
            ofxOpenNIHand & hand = openNIDevice.getTrackedHand(i);
            // get hand position
            ofPoint & handPosition = hand.getPosition();
            if(i==0){
                leftHandPos = handPosition;
            }
            else{
                rightHandPos = handPosition;
            };
            ofSetColor(255,255,255);
            ofPopMatrix();
            
        }
    }
    //If not intialScreen
    if(initialScreen == false){
        if(next==-1){
            next++;
        }
        
        int lx = leftHandPos.x;
        int ly = leftHandPos.y/480*1400-200;
        int rx = rightHandPos.x;
        int ry = rightHandPos.y/480*1400-200;
        if(sqrt(abs(leftHandPos.x - rightHandPos.x)*abs(leftHandPos.x - rightHandPos.x)+abs(leftHandPos.y - rightHandPos.y)*abs(leftHandPos.y - rightHandPos.y))>100){
            ofSetColor(214, 162, 67);
            ofDrawCircle(lx,ly, 20);
            ofDrawCircle(rx,ry, 20);
            s1 = 0;s2 = 0;s3 = 0;s4 = 0;s0 = 0;
            playing = -1;
        }
        else{
            ofSetColor(223, 230, 234);
            int hx =(rx+lx)/2;
            int hy =(ry+ly)/2;
            ofDrawCircle(hx, hy, 50);
            hitting = hy/200;
            if(hitting==0){
                if(playing!=hitting){
                    doS.play();
                    if(c0!=0){
                        next++;
                    }
                }
                playing = hitting;
                s0 = s0 + 10;
            }
            if(hitting==1){
                s1 = s1 + 10;
                if(playing!=hitting){
                    riS.play();
                    if(c1!=0){
                        next++;
                    }
                }
                playing = hitting;
            }
            if(hitting==2){
                if(playing!=hitting){
                    miS.play();
                    if(c2!=0){
                        next++;
                    }
                }
                playing = hitting;
                s2 = s2 + 5;
            }
            if(hitting==3){
                s3 = s3 + 5;
                if(playing!=hitting){
                    faS.play();
                    if(c3!=0){
                        next++;
                    }
                }
                playing = hitting;
            }
            if(hitting==4){
                s4 = s4 + 5;
                if(playing!=hitting){
                    soS.play();
                    if(c4!=0){
                        next++;
                    }
                }
                playing = hitting;
            }
            c0 = 0;
            c1 = 0;
            c2 = 0;
            c3 = 0;
            c4 = 0;
            
        }
    }
    //Drawing of r
    ofDisableBlendMode();
    ofPopMatrix();
    ofSetColor(255, 255, 255);
    string msg;
    if(handNum<2 && playing == -1){
        msg = "Please show both hands";
    }
    if(handNum>2){
        msg = "Too many people in area";
    }
    verdana.drawString(msg, 50, 500);
    //verdana.drawString(msg, 20, 480 - 20);
    ofSetColor(0, 255, 0);
    //string msg = " MILLIS: " + ofToString(ofGetElapsedTimeMillis()) + " FPS: " + ofToString(ofGetFrameRate()) + " Device FPS: " + ofToString(openNIDevice.getFrameRate());
    
    //verdana.drawString(msg, 20, 480 - 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    //Press any key to reset
    next = -1;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
