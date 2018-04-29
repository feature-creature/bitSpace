#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(155);
    
    // initialize eightBit settings
    popmax = 8;
    mutationRate = 0.25;
    bitSpace.setup(mutationRate, popmax);

    // initialize computer vision video source
    vidGrabber.setDeviceID(0);
    vidGrabber.setDesiredFrameRate(30);
    vidGrabber.initGrabber(640,460);

    // initialize color tracking target and threshold
    rTarget = 28;
    gTarget = 39;
    bTarget = 23;
    threshold = 2;

}

//--------------------------------------------------------------
void ofApp::update(){

    // update current frame data from video source
    vidGrabber.update();

    // if current frame data is received and new
    if(vidGrabber.isFrameNew()){
        
        // clear the previous frame's data 
        // from the 5 global variables that store 
        // the current count of all pixels which have color 'close' to the target color, 
        // the current sums of those pixel's x and y coordinates, and
        // the subsequent current approximate average location (x and y coordinates)
        // of the target color in the frame.
        count = 0;
        sumCloseColorsX = 0;
        sumCloseColorsY = 0;
        closestColorX = 0;
        closestColorY = 0;

        // iterate through every pixel in the current frame
        // row by column - width by height - left to right, top to bottom
        // to store/not store the current pixel's data
        // in the previous global variables 
        int w = vidGrabber.getWidth();
        int h = vidGrabber.getHeight();
        for (int y=0; y<h; y++) {
            for (int x=0; x<w; x++) {
                // locally store the color data of the current pixel at x,y location
                ofColor colorAtXY = vidGrabber.getPixels().getColor(x, y);
                float rAtXY = colorAtXY.r;
                float gAtXY = colorAtXY.g;
                float bAtXY = colorAtXY.b;
           
                // calculate color distance between
                // the current pixel's RGB color values 
                // and the target color's RGB values
                // !!ofDist calculates 3D distance between points
                // via the pythagorean theorem, but instead of traditional x,y,z distance
                // we calculate r,g,b distance in the same way.
                // ofDist returns a float
                float colorDistance = ofDist(rAtXY, gAtXY, bAtXY, rTarget, gTarget, bTarget);
            
                // if distance between the two RGB colors
                // is shorter than the current distance threshhold 
                // then increase the global count of pixels which have 'close' color by 1
                // and add the current pixel's x and y coordinates to 
                // the globally stored sum of x and y coordinates 
                if(colorDistance < threshold){
                    count++;
                    sumCloseColorsX+= x;
                    sumCloseColorsY+= y;
                }
            }
        }
        //if pixels with 'close' color have been tracked
        // determine the approximate average coordinates of the target color
        // within the current frame.
        // then send the coordinates to the instance of the snake class
        // To reduce data noise, do not update the average if it equals 0;
        if (count>0) {
            if( sumCloseColorsX / count > 10 && sumCloseColorsY / count > 10){
                closestColorX = sumCloseColorsX / count;
                closestColorY = sumCloseColorsY / count;

                bitSpace.flip(0);
                bitSpace.select();
                bitSpace.generate();

            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    // show video
    if(sourceVisible == true){
        ofPushMatrix();
        vidGrabber.draw(0,0);
        ofDrawBitmapString(threshold,25,25); 
        ofPopMatrix();
    }
    // show tracked color
    if(closestColorX > 10 && closestColorY > 10){
        ofPushMatrix();
        ofPushStyle();
        ofSetColor(0);
        ofDrawEllipse(closestColorX,closestColorY,25,25);
        ofPopStyle();
        ofPopMatrix();
    }

    // show bitspace at bottom of window
    ofPushMatrix();
    ofPushStyle();
    ofTranslate(0, ofGetHeight()-30, 0);
    bitSpace.draw();
    ofPopStyle();
    ofPopMatrix();

}

//--------------------------------------------------------------
void ofApp::displayInfo(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    // keys 0-7 for flipping bit
    if (key>=47 && key <56) {
        bitSpace.flip(ofToInt(ofToString(char(key))));
        bitSpace.select();
        bitSpace.generate();
    }

    // increase or decrease the distance threshold
    // determining 'closeness'
    // between a pixel's color and the target color
    if (key == OF_KEY_UP) threshold+=1;//UP ARROW
    else if (key==OF_KEY_DOWN && threshold > 0) threshold-=1;//DOWN ARROW - prevent negatives
    else if (key=='v')sourceVisible=!sourceVisible;

}

//---------------------
// select the target color via mouse click
// (color of pixel under the mouse's x,y current coordinates) 
void ofApp::mousePressed(int x, int y, int button){
    ofColor tempColor = vidGrabber.getPixels().getColor(x, y);
    rTarget = tempColor.r;
    gTarget = tempColor.g;
    bTarget = tempColor.b;
}

