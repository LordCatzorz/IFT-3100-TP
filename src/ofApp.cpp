#include "ofApp.h"



void ofApp::FileOpenCallback(string param){

    std::ifstream input( param, std::ios::binary );
    string imageName = param.substr(param.find_last_of("/"));
    saveFile("./data" + imageName, input);
    input.close();

    Image * newImage = new Image(imageName.substr(1));
    visibleImages.insert(visibleImages.end(), *newImage);
}

void ofApp::PrintScreenTakenCallback(string param){
    printScreenTakenCallback(0, 0, ofGetWidth(), ofGetHeight(), param);
}

void ofApp::printScreenTakenCallback(int x, int y, int width, int height, string param){
    ofImage screenImg;
    screenImg.allocate(width, height, OF_IMAGE_COLOR);
    screenImg.grabScreen(x,y,width,height);
    screenImg.saveImage(param + ".png");
}

void ofApp::saveFile(string path, std::ifstream & file){
    std::ofstream output(path, std::ios::binary );

    std::copy(
     std::istreambuf_iterator<char>(file),
     std::istreambuf_iterator<char>( ),
     std::ostreambuf_iterator<char>(output));
    output.close();

}

void ofApp::PrintScreenSectionCallback(string arg){
    mouseWatcher->ShouldShowSelectionZone(true);
    isMakingScreenshotSection = true;
    mouseUpDelegates[0].bind(this, &ofApp::takeScreenshotSection);
}

void ofApp::takeScreenshotSection(int x, int y){
    int startX = mouseWatcher->TopLeftPoint()->x;
    int startY = mouseWatcher->TopLeftPoint()->y;
    int endX = mouseWatcher->BottomRightPoint()->x;
    int endY = mouseWatcher->BottomRightPoint()->y;
    mouseWatcher->ShouldShowSelectionZone(false);
    for (int i=0; i<12; i++) {
        if(mouseUpDelegates[i] == MouseActionDelegate(this, &ofApp::takeScreenshotSection)){
            mouseUpDelegates[i].clear();
            break;
        }
    }

    ofLog() << "startX: " << startX << " startY: " << startY << " endX - startX: " << endX - startX << " endY - startY: " << endY - startY;

    printScreenTakenCallback(0, 0, ofGetWindowWidth(), ofGetWindowHeight(), Gui->RequestSaveFilePath("captureDEcran") + "captureDEcran");
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
    Gui->AddPrintscreenTakenListener(std::bind(&ofApp::PrintScreenTakenCallback, this, std::placeholders::_1));
    Gui->AddPrintscreenSelectionListener(std::bind(&ofApp::PrintScreenSectionCallback, this, std::placeholders::_1));
    mouseWatcher = new MouseWatcher();
    //mousePressed.bind(&ofApp::someMouseHandler, this);

}

void ofApp::beginSelectionZoneDraw(int x, int y){
    bool a = true;
    for (int i=0; i<12; i++) {
        if(mouseDownDelegates[i] == MouseActionDelegate(this, &ofApp::beginSelectionZoneDraw)){
            mouseDownDelegates[i].clear();
            break;
        }
    }
}

//--------------------------------------------------------------
void ofApp::update()
{

}

int xE1 = -1, yE1 = -1, xE2 = -1, yE2 = -1;

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
    mouseWatcher->Draw();
    for(vector<Image>::iterator i = visibleImages.begin(); i != visibleImages.end(); i++){
        //Image * image = new Image((*i).Name);
        //image->load((*i).Name);
        //image->draw((*i).X, (*i).Y);
        //(*i).Width = image->getWidth();
        //(*i).Height = image->getHeight();
        (*i).Draw();
    }

    if(xE1 >= 0){
        ofFill();
        ofSetColor(ofColor::red);
        ofEllipse(xE1, yE1, 50, 50);
        ofSetColor(ofColor::black);
        ofEllipse(xE2, yE2, 50, 50);
        ofSetColor(ofColor::white);
    }

    /*ofSetColor(ofColor::black);
    if(isRecordingMouseMouvements)
        ofDrawRectangle(mouseWatcher->TopLeftPoint()->x, mouseWatcher->TopLeftPoint()->y,
                        mouseWatcher->TopRightPoint()->x - mouseWatcher->TopLeftPoint()->x,
                        mouseWatcher->BottomLeftPoint()->y - mouseWatcher->TopLeftPoint()->y);*/
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
    for(vector<Image>::iterator i = visibleImages.begin(); i != visibleImages.end() && selectedImage == nullptr; i++){
        if((*i).IsPointWithinBounds(x, y)){
            (*i).ShowBorders(true);
        }else{
            (*i).ShowBorders(false);
        }
    }
}
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
    if(button == 0 || button == 2){
        isRecordingMouseMouvements = true;
        mouseWatcher->Record(x, y);

        if(selectedImage != nullptr){
            xE2 = x - selectedImage->TopLeftPoint()->x;
            yE2 = y - selectedImage->TopLeftPoint()->y;
            selectedImage->AffectVector(x, y, mouseWatcher->CurretVector(), button == 2);
        }
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{

    if(button == 0 || button == 2){
        xE1 = x;
        yE1 = y;
        for(vector<Image>::iterator i = visibleImages.begin(); i != visibleImages.end() && selectedImage == nullptr; i++){
            if((*i).IsPointWithinBounds(x, y)){
                selectedImage = &(*i);
                selectedImage->ShowBorders(true);
            }
        }

        isRecordingMouseMouvements = true;
        mouseWatcher->Record(x, y);
    }

    for (int i=0; i<12; i++) {
            if (!mouseDownDelegates[i]) {
                printf("Delegate is empty\n");
            } else {
                // Invocation generates optimal assembly code.
                mouseDownDelegates[i](x, y);
            };
        }

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{

    xE1 = yE1 = xE2 = yE2 = -1;
    if(selectedImage != nullptr)
        selectedImage->ShowBorders(false);
    selectedImage = nullptr;
    if(button == 0){
        isRecordingMouseMouvements = false;
        mouseWatcher->StopRecording();
        mouseWatcher->ShouldShowSelectionZone(false);
    }else if(button == 2){
        for(vector<Image>::iterator i = visibleImages.begin(); i != visibleImages.end() && selectedImage == nullptr; i++){
            (*i).AffectVector(x, y, mouseWatcher->CurretVector(), false);
        }
    }

    for (int i=0; i<12; i++) {
            if (!mouseUpDelegates[i]) {
                printf("Delegate is empty\n");
            } else {
                // Invocation generates optimal assembly code.
                mouseUpDelegates[i](x, y);
            };
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
