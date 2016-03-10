#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main()
{
	ofGLWindowSettings window;
	window.setGLVersion(3, 3);

	ofSetupOpenGL(ofApp::SCREEN_WIDTH, ofApp::SCREEN_HEIGHT, OF_WINDOW);			// <-------- setup the GL context


	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());
}
