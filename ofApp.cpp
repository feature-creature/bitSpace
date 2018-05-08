#include "ofApp.h"
#include "ofxOsc.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // open an outgoing connection to HOST:PORT
    sender.setup(HOST,PORT_SENDER);
    // listen on an incoming connection
    receiver.setup(PORT_RECEIVER);

    ofBackground(155);
    
    // initialize eightBit settings
    mutationRate = 0.25;
    popmax = 8;
    bitSpace.setup(mutationRate, popmax);

    // initialize computer vision video source
    vidGrabber.setDeviceID(0);
    vidGrabber.setDesiredFrameRate(30);
    vidGrabber.initGrabber(640,460);
    boxWidth = 16;
    boxHeight = 11;
    boxWidthNum = boxWidth/160;
    boxHeightNum = boxHeight/110; //115;
}

//--------------------------------------------------------------
void ofApp::update(){

    // update current frame data from video source
    vidGrabber.update();

    // if current frame data is received and new
    if(vidGrabber.isFrameNew()){

        if(gray1.bAllocated){
            gray2 = gray1;
            calculatedFlow = true;
        }

        // Convert video frame to ofxOpenCv image
        ofPixels & pixels = vidGrabber.getPixels();
        currentColor.setFromPixels(pixels);

        // create temporary, local 25% decimated image 
        // this decreases computation time and can work like a blur effect
        // in comparison to computing on the default video frame
        float decimate = 0.25;
        ofxCvColorImage imageDecimated1;
        // 160X120
        imageDecimated1.allocate(currentColor.width * decimate, currentColor.height * decimate);
        
        // resize currentColor to the size of decimated image
        imageDecimated1.scaleIntoMe(currentColor, CV_INTER_AREA);
        // 
        gray1 = imageDecimated1;
        // increase contrast
        // gray1.threshold(80);
        //cout << gray1.width << endl;
        //cout << gray1.height << endl;

        if(gray2.bAllocated){

            // create temporary, local OpenCv images
            Mat img1 (gray1.getCvImage());
            Mat img2 (gray2.getCvImage());
            Mat flow;

            // Compute optical flow
            // reference: https://docs.opencv.org/3.0-beta/modules/video/doc/motion_analysis_and_object_tracking.html
            calcOpticalFlowFarneback(img1,img2,flow,0.7,3,11,10,10,1.1,0);

            // split flow into separate images
            // temporary, local vector
            vector<Mat> flowPlanes;
            split(flow,flowPlanes);
        
            // copy float planes to ofxCv images
            // convert datatypes
            IplImage iplX(flowPlanes[0]);
            IplImage iplY(flowPlanes[1]);
            flowX = &iplX;
            flowY = &iplY;
        }
        phase += (avgFlowX*10);

    }


        




        
        //}



    // send non-information to wek
    //
    //ofxOscMessage m;
    //m.setAddress(string(MESSAGE));
    //m.addFloatArg(-1.0f);
    //sender.sendMessage(m);

    // receive data from Wek via OSC

    while(receiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(&m);
  
        // if correct data exists, use it
        // otherwise print out message
        if(m.getAddress() == string(RECEIVERS_PATH)){
            //cout << m.getNumArgs()<< endl;
            for(int i = 0; i < m.getNumArgs(); i++){
                //cout << m.getArgAsFloat(i) << endl;
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
        }else{
            string msg_string;
            msg_string = m.getAddress();
            msg_string += ": ";

            // unrecognized message: display on the bottom of the screen
            for(int i = 0; i < m.getNumArgs(); i++){
                // get the argument type
                msg_string += m.getArgTypeName(i);
                msg_string += ":";
                // display the argument - make sure we get the right type
                if(m.getArgType(i) == OFXOSC_TYPE_INT32){
                    msg_string += ofToString(m.getArgAsInt32(i));
                }
                else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
                    msg_string += ofToString(m.getArgAsFloat(i));
                }
                else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
                    msg_string += m.getArgAsString(i);
                }
                else{
                    msg_string += "unknown";
                }
            }
            cout << msg_string << endl;
        }
   }




}

//--------------------------------------------------------------
void ofApp::draw(){

    // show setup and debugging information
    if(sourceVisible == true){

        // clear global variables of previous data 
        sumFlowX = 0;
        sumFlowY = 0;
        numOfFlowEntries = 0;
        
        if(calculatedFlow){

            // send information to wek via OSC
            //
            ofxOscMessage m;
            m.setAddress(string(SENDERS_PATH));

            // show video feed
            gray1.draw(0,0);

            ofPixels grayData = gray1.getPixels();
            int w = gray1.width;
            int h = gray1.height - 15;    
            int boxNum = 0;
            int boxTotal = boxWidth*boxHeight;


            float *flowXPixels = flowX.getPixelsAsFloats();
            float *flowYPixels = flowY.getPixelsAsFloats();

            // draw individual flowlines
            for (int y=0; y<h; y+=boxHeight) {
                for (int x=0; x<w; x+=boxWidth) {
                    float fx = flowXPixels[ x + w * y ];
                    float fy = flowYPixels[ x + w * y ];
                    sumFlowX += fx;
                    sumFlowY += fy;
                    numOfFlowEntries++;

                    if ( fabs( fx ) + fabs( fy ) > 1 ) {
                        ofDrawRectangle( x-0.5, y-0.5, 1, 1 );
                        ofDrawLine( x, y, x + fx, y + fy );
                    }

                    int graySum = 0;
                    for(int i = 0; i < boxWidth; i++){
                        for(int j = 0; j < boxHeight; j++){
                            int index = (x+i) + (y+j) * 160;
                            graySum += grayData[index];
                        }
                    }
                    // 10 features 
                    if(y > 40&& y < 50){
                        //send to wek
                        m.addFloatArg(graySum/boxTotal);

                        ofPushStyle();
                        ofPushMatrix();
                        ofSetColor(graySum/boxTotal);
                        ofTranslate(x,y+115);
                        ofDrawRectangle(0,0,boxWidth,boxHeight);
                        ofPopMatrix();
                        ofPopStyle();
                    }
                }    
            }

            // if entries exist, calculate the average for all entries
            if(numOfFlowEntries > 0){
                avgFlowX = ofClamp(sumFlowX / numOfFlowEntries,-10,10);
                avgFlowY = sumFlowY/numOfFlowEntries;
            }

            // draw master flowline
            ofPushMatrix();
            ofPushStyle();
            ofTranslate(gray1.width/2,gray1.height/2);
            ofSetColor(255,0,0);
            ofDrawLine(0,0,avgFlowX*-100,avgFlowY*-100);
            ofPopStyle();
            ofPopMatrix();
            
            // send optical flow avgs to wek
            // 2 features
            m.addFloatArg(avgFlowX);
            m.addFloatArg(avgFlowY);

            // 12 features total
            sender.sendMessage(m, false);
        }

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
}

//--------------------------------------------------------------
// increase or decrease the distance threshold for the current color target
// to determine match boundaries between a pixel's color and the target color
void ofApp::keyPressed(int key){
    
    // show or hide the video source and tracking data
    if (key=='v')sourceVisible=!sourceVisible;
}
