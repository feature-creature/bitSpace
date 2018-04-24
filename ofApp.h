#pragma once
#include "ofMain.h"
#include "BitSpace.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void keyPressed(int key);
        void displayInfo();

        int popmax;
        float mutationRate;
        BitSpace bitSpace;
        bool activate;
};
