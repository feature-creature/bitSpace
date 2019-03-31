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
        void mousePressed(int x, int y, int button);
        
        // bitspace
        float mutationRate;
        int popmax;
        BitSpace bitSpace;
        int flipper;
};

