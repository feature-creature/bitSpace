#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    

    ofBackground(155);
    
    // initialize eightBit settings
    mutationRate = 0.25;
    popmax = 8;
    bitSpace.setup(mutationRate, popmax);
}

//--------------------------------------------------------------
void ofApp::update(){}

//--------------------------------------------------------------
void ofApp::draw(){
    // show bitSpace
    ofPushMatrix();
    ofPushStyle();
    ofTranslate(0, ofGetHeight()-30, 0);
    bitSpace.draw(flipper);
    ofPopStyle();
    ofPopMatrix();
}

//--------------------------------------------------------------
// increase or decrease the distance threshold for the current color target
// to determine match boundaries between a pixel's color and the target color
void ofApp::keyPressed(int key){
    if (key=='1'){flip(0);};
    if (key=='2'){flip(1);};
    if (key=='3'){flip(2);};
    if (key=='4'){flip(3);};
    if (key=='5'){flip(4);};
    if (key=='6'){flip(5);};
    if (key=='7'){flip(6);};
    if (key=='8'){flip(7);};
}

void ofApp::flip(int bit){
    if(bitSpace.bitStates[bit] == false){
        bitSpace.bitStates[bit] = true;
    }else{
        bitSpace.bitStates[bit] = false;
    }
    bitSpace.flip(bit);
    bitSpace.select();
    bitSpace.generate();
}

