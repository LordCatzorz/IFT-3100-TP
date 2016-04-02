#include "ofMain.h"
#include "ofApp.h"
#include "app/ofAppGlutWindow.h"

//========================================================================
int main()
{
    ofAppGlutWindow window;
    // param�tres du contexte de rendu OpenGL
    ofGLWindowSettings windowSettings;

    windowSettings.width = ofApp::SCREEN_WIDTH;
    windowSettings.height = ofApp::SCREEN_HEIGHT;

    // s�lection de la version de OpenGL : option #1
    //windowSettings.setGLVersion(2, 1);

    // s�lection de la version de OpenGL : option #2
    //windowSettings.setGLVersion(3, 3);

    // cr�ation de la fen�tre
    //ofCreateWindow(windowSettings);			// <-------- setup the GL context

     ofSetupOpenGL(&window, ofApp::SCREEN_WIDTH,ofApp::SCREEN_HEIGHT,OF_WINDOW);

    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp(new ofApp());
}
