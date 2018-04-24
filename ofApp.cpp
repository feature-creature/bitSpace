#include "ofApp.h"
// ?? what is this for
#define FRAME_WIDTH 80
#define FRAME_HEIGHT 60

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255);
    
    // initialize eightBit settings
    popmax = 8;
    mutationRate = 0.025;
    bitSpace.setup(mutationRate, popmax);
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofTranslate(ofGetWidth()/20, ofGetHeight()-30);
    bitSpace.draw();
}

//--------------------------------------------------------------
void ofApp::displayInfo(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    // keys 0-7
    if (key>=47 || key <=56) {
        bitSpace.flip(ofToInt(ofToString(char(key))));
        bitSpace.select();
        bitSpace.generate();
    }

    //if (key == 'g' || key == 'G') {
    //}

}
