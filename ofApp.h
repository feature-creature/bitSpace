#pragma once
#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxOpenCv.h"
using namespace cv;

#include "BitSpace.h"

#define HOST "localhost"
#define PORT_SENDER 6448
#define SENDERS_PATH "/wek/inputs"
#define PORT_RECEIVER 12000
#define RECEIVERS_PATH "/wek/outputs"


class ofApp : public ofBaseApp{

	public:
        // methods
		void setup();
		void update();
		void draw();
		void keyPressed(int key);
        void mousePressed(int x, int y, int button);
        
        // bitspace
        float mutationRate;
        int popmax;
        BitSpace bitSpace;
        int flipper;

        // opticalflow
        ofxCvColorImage currentColor;
        ofxCvGrayscaleImage gray1, gray2;
        ofxCvFloatImage flowX, flowY;
        float sumFlowX, sumFlowY;
        float avgFlowX, avgFlowY;
        int numOfFlowEntries;
        bool calculatedFlow;
        float phase;

        // video feed
        ofVideoGrabber vidGrabber;
        bool sourceVisible = true;
        int boxWidth, boxHeight;
        int boxWidthNum, boxHeightNum;

        // osc
        ofxOscSender sender;
        ofxOscReceiver receiver;

};

