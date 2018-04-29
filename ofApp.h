#pragma once
#include "ofMain.h"
#include "BitSpace.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void keyPressed(int key);
        void mousePressed(int x, int y, int button);
        
        // bitspace
        void displayInfo();
        int popmax;
        float mutationRate;
        BitSpace bitSpace;
        bool activate;

        // bit tracker
        ofVideoGrabber vidGrabber;
        int count;
        int sumCloseColorsX, sumCloseColorsY;
        int closestColorX, closestColorY;
        float rTarget;
        float gTarget;
        float bTarget;
        float threshold;
        bool sourceVisible = true;



};
