#include "ofApp.h"

void ofApp::FileOpenCallback(string param){

    std::ifstream input( param, std::ios::binary );
    string imageName = param.substr(param.find_last_of("/"));
    saveFile("./data" + imageName, input);
    input.close();

    Image * newImage = new Image();
    newImage->X = 0;
    newImage->Y = 0;
    newImage->Width = 300;
    newImage->Height = 300;
    newImage->Name = imageName.substr(1);
    visibleImages.insert(visibleImages.end(), *newImage);
}

void ofApp::saveFile(string path, std::ifstream & file){
    std::ofstream output(path, std::ios::binary );

    std::copy(
     std::istreambuf_iterator<char>(file),
     std::istreambuf_iterator<char>( ),
     std::ostreambuf_iterator<char>(output));
    output.close();
}

//--------------------------------------------------------------
void ofApp::setup()
{
    //ofEnableDepthTest();
    ofSetFrameRate(24);
    Shapes shape = Shapes();
    mesh = shape.createCube();
    Gui = new GUI();
    Gui->AddImageOpenedListener(std::bind(&ofApp::FileOpenCallback, this, std::placeholders::_1));
    mouseWatcher = new MouseWatcher();
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

    for(vector<Image>::iterator i = visibleImages.begin(); i != visibleImages.end(); i++){
        ofImage * image = new ofImage();
        image->load((*i).Name);
        image->draw((*i).X, (*i).Y);
        (*i).Width = image->getWidth();
        (*i).Height = image->getHeight();
    }

    ofSetColor(ofColor::black);
    if(isRecordingMouseMouvements)
        ofDrawRectangle(mouseWatcher->TopLeftPoint()->x, mouseWatcher->TopLeftPoint()->y,
                        mouseWatcher->TopRightPoint()->x - mouseWatcher->TopLeftPoint()->x,
                        mouseWatcher->BottomLeftPoint()->y - mouseWatcher->TopLeftPoint()->y);
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
    if(button == 0){
        isRecordingMouseMouvements = true;
        mouseWatcher->Record(x, y);
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    if(button == 0){
        isRecordingMouseMouvements = true;
        mouseWatcher->Record(x, y);
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
    if(button == 0){
        isRecordingMouseMouvements = false;
        mouseWatcher->StopRecording();
    }
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{
    mouseWatcher->ResumeRecording();
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{
    mouseWatcher->PauseRecording();
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
