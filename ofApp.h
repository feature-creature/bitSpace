#pragma once
#include "ofMain.h"
#include "BitSpace.h"

class ofApp : public ofBaseApp{

	public:
        // methods
		void setup();
		void update();
		void draw();
		void keyPressed(int key);
        void flip(int bit);
        
        // bitspace
        float mutationRate;
        int popmax;
        BitSpace bitSpace;
        int flipper;
};

