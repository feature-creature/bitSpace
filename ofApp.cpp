#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(155);
    
    // initialize eightBit settings
    mutationRate = 0.25;
    popmax = 8;
    bitSpace.setup(mutationRate, popmax);

    
    // initialize target colors to track
    targetColors.clear();
    for(int i = 0; i < popmax; i++){
        // local, temporary color object
        ofColor tempColor(255,182,193);
        // store in global vector
        targetColors.push_back(tempColor);
    }

    // initialize target thresholds for target colors
    targetThresholds.clear();
    for(int i = 0; i < popmax; i++){
        targetThresholds.push_back(1);
    }

    // initialize target
    target = 0;
    
    // initialize computer vision video source
    vidGrabber.setDeviceID(0);
    vidGrabber.setDesiredFrameRate(30);
    vidGrabber.initGrabber(640,460);
}

//--------------------------------------------------------------
void ofApp::update(){

    // update current frame data from video source
    vidGrabber.update();

    // if current frame data is received and new
    if(vidGrabber.isFrameNew()){
        
        
        int w = vidGrabber.getWidth();
        int h = vidGrabber.getHeight();
        
        // for each target color
        for(int i = 0; i < popmax; i++){

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
            // left to right, top to bottom (row by column)
            // to find and store pixels with 'close' color values to target colors
            for (int y=0; y<h; y++) {
                for (int x=0; x<w; x++) {
                    
                    // locally store the current pixel's color data 
                    ofColor colorAtXY = vidGrabber.getPixels().getColor(x, y);
                    float rAtXY = colorAtXY.r;
                    float gAtXY = colorAtXY.g;
                    float bAtXY = colorAtXY.b;
               
                    // calculate color distance between
                    // the current pixel's RGB color values 
                    // and the current target color's RGB values
                    //
                    // ofDist calculates 3D distance between points
                    // pythagorean theorem for r,g,b instead of x,y,z
                    // ofDist returns a float
                    float colorDistance = ofDist(rAtXY, gAtXY, bAtXY, targetColors[i].r, targetColors[i].g, targetColors[i].b);
                
                    // if distance between the two RGB colors
                    // is shorter than the current distance threshhold 
                    // then increase the global count of pixels which have 'close' color by 1
                    // and add the current pixel's x and y coordinates to 
                    // the globally stored sum of x and y coordinates 
                    if(colorDistance < targetThresholds[i]){
                        count++;
                        sumCloseColorsX+= x;
                        sumCloseColorsY+= y;
                    }
                }
            }


            // if pixels with 'close' color have been tracked within the current frame
            // exclude averages that return false positives
            if(count>0 && sumCloseColorsX / count > 10 && sumCloseColorsY / count > 10){
                // if this color's bit state was not already 'on'
                // turn it on and generate next generation
                if(bitSpace.bitStates[i] != true){
                    bitSpace.bitStates[i] = true;
                    // !! update 0
                    bitSpace.flip(i);
                    bitSpace.select();
                    bitSpace.generate();
                }
            }else{
                // if there are no pixels with 'close' colors in the current frame
                // if this color's bit state was not already 'off'
                // turn it off and generate next generation
                if(bitSpace.bitStates[i]!= false){
                    bitSpace.bitStates[i] = false;
                    // !! update 0
                    bitSpace.flip(i);
                    bitSpace.select();
                    bitSpace.generate();
                }
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    // show setup and debugging information
    if(sourceVisible == true){

        ofPushMatrix();

        // show video feed
        vidGrabber.draw(0,0);
        // show color information of current color tracking target
        ofDrawBitmapString("bit: ", 25, 25);
        // target color's bit index and state
        ofDrawBitmapString(target, 75, 25);
        ofDrawBitmapString(bitSpace.bitStates[target], 25, 50);
        // target color's RGB and threhold values
        ofDrawBitmapString((int)targetColors[target].r, 25, 75);
        ofDrawBitmapString((int)targetColors[target].g, 25, 100);
        ofDrawBitmapString((int)targetColors[target].b, 25, 125);
        ofDrawBitmapString(targetThresholds[target], 25, 150);

        ofPopMatrix();
    }


    // show bitSpace
    ofPushMatrix();
    ofPushStyle();
    ofTranslate(0, ofGetHeight()-30, 0);
    bitSpace.draw(flipper);
    ofPopStyle();
    ofPopMatrix();

}


//---------------------
// select a target color via mouse click
// (color of pixel under the mouse's x,y current coordinates) 
void ofApp::mousePressed(int x, int y, int button){
    ofColor tempColor = vidGrabber.getPixels().getColor(x, y);
    targetColors[target].r = tempColor.r;
    targetColors[target].g = tempColor.g;
    targetColors[target].b = tempColor.b;
}

//--------------------------------------------------------------
// increase or decrease the distance threshold for the current color target
// to determine match boundaries between a pixel's color and the target color
void ofApp::keyPressed(int key){
    
    // increase
    if (key == OF_KEY_UP) targetThresholds[target]+=1;
    // decrease, but prevent negative thresholds
    else if (key==OF_KEY_DOWN && targetThresholds[target] > 0) targetThresholds[target]-=1;

    // show or hide the video source and tracking data
    else if (key=='v')sourceVisible=!sourceVisible;

    // switch between targets
    else if (key == '0') target = 0;
    else if (key == '1') target = 1;
    else if (key == '2') target = 2;
    else if (key == '3') target = 3;
    else if (key == '4') target = 4;
    else if (key == '5') target = 5;
    else if (key == '6') target = 6;
    else if (key == '7') target = 7;
}
