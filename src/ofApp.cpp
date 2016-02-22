#include "ofApp.h"

string loadedImage;
void FileOpenCallback(string param){
    loadedImage = param;
}

//--------------------------------------------------------------
void ofApp::setup()
{
    //ofEnableDepthTest();
    ofSetFrameRate(24);
    Shapes shape = Shapes();
    mesh = shape.createCube();
    Gui = new GUI();

    Gui->AddImageOpenedListener(&FileOpenCallback);
}

//--------------------------------------------------------------
void ofApp::update()
{

}

//--------------------------------------------------------------
void ofApp::draw()
{

	ofPushMatrix();
	ofTranslate(100, 100);
	ofScale(15, 15);
	ofSetColor(ofColor::aqua);
	mesh->draw();
	ofPopMatrix();

    Gui->Draw();

    if(!loadedImage.empty()){
        ofImage * image = new ofImage();
        image->load(loadedImage);
        image->draw(200, 10, 300, 300);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{

}
