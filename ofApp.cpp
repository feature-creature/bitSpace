#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    

    ofBackground(155);
    
    // initialize eightBit settings
    mutationRate = 0.25;
    popmax = 8;
    bitSpace.setup(mutationRate, popmax);

    boxWidth = 16;
    boxHeight = 11;
    boxWidthNum = boxWidth/160;
    boxHeightNum = boxHeight/110; //115;
}

//--------------------------------------------------------------
void ofApp::update(){
    // needs new source for args
    for(int i = 0; i < m.getNumArgs(); i++){
        // turn it on and generate next generation
        if(m.getArgAsFloat(i) == 2 && bitSpace.bitStates[i] != true){
            bitSpace.bitStates[i] = true;
            bitSpace.flip(i);
            bitSpace.select();
            bitSpace.generate();
        }else{
            if(m.getArgAsFloat(i) == 1 && bitSpace.bitStates[i]!= false){
                bitSpace.bitStates[i] = false;
                bitSpace.flip(i);
                bitSpace.select();
                bitSpace.generate();
            }   
        } 
    }

}

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
    
    if (key=='1');
    if (key=='2');
    if (key=='3');
    if (key=='4');
    if (key=='5');
    if (key=='6');
    if (key=='7');
    if (key=='8');
}
