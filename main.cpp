#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	ofSetupOpenGL(900,320,OF_WINDOW);			// <-------- setup the GL context


    //linux w/ ps2 camera
    //$ sudo apt-get install v4l2ucp
    //$ v4l2ucp
    //turn off auto white balance and auto exposure
    //for more consistent results
    //also vertical & horizontal flip of camera feed
 
    // implementation note:
    // this program expects that color tracking targets
    // are selected from the video source, not from the standard window
    // this program will crash if you do not select targets from the video source.

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());
}
