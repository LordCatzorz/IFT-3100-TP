#include "ofApp.h"

void ofApp::FileOpenCallback(string param){

    std::ifstream input( param, std::ios::binary );

	std::replace(param.begin(), param.end(), '\\', '/');
	string imageName = param.substr(param.find_last_of("/"));
    saveFile("./data" + imageName, input);
    input.close();

    Image * newImage = new Image(imageName.substr(1));
    newImage->AffectVector((int)(newImage->TopRightPoint()->x /2), (int)(newImage->BottomLeftPoint()->y /2), new ofVec3f(100, 100));
    visibleShapes.insert(visibleShapes.end(), newImage);
}


void ofApp::PrintScreenTakenCallback(string param){
    printScreenTakenCallback(0, 0, ofGetWidth(), ofGetHeight(), param);
}

void ofApp::printScreenTakenCallback(int x, int y, int width, int height, string param)
{
    ofImage screenImg;
	screenImg.allocate(width, height, OF_IMAGE_COLOR);
	screenImg.grabScreen(x, y, width, height);
    screenImg.saveImage(param + ".png");
}

void ofApp::saveFile(string path, std::ifstream & file)
{
	std::ofstream output(path, std::ios::binary);

	std::copy(
		std::istreambuf_iterator<char>(file),
		std::istreambuf_iterator<char>(),
		std::ostreambuf_iterator<char>(output));
	output.close();

}

void ofApp::PrintScreenSectionCallback(string arg)
{
	mouseWatcher->ShouldShowSelectionZone(true);
	isMakingScreenshotSection = true;
	mouseUpDelegates[0].bind(this, &ofApp::takeScreenshotSection);
}

void ofApp::takeScreenshotSection(int x, int y)
{
	int startX = mouseWatcher->TopLeftPoint()->x;
	int startY = mouseWatcher->TopLeftPoint()->y;
	int endX = mouseWatcher->BottomRightPoint()->x;
	int endY = mouseWatcher->BottomRightPoint()->y;
	mouseWatcher->ShouldShowSelectionZone(false);
	for (int i = 0; i < 12; i++)
	{
		if (mouseUpDelegates[i] == MouseActionDelegate(this, &ofApp::takeScreenshotSection))
		{
			mouseUpDelegates[i].clear();
			break;
		}
	}

	ofLog() << "startX: " << startX << " startY: " << startY << " endX - startX: " << endX - startX << " endY - startY: " << endY - startY;

	printScreenTakenCallback(0, 0, ofGetWindowWidth(), ofGetWindowHeight(), Gui->RequestSaveFilePath("captureDEcran") + "captureDEcran");
}

void ofApp::ModeChangeCallback(GUI::ActionType newMode){
    actionMode = newMode;
}

void ofApp::ImportObjFileCallback(string param)
{
	importedModel->loadModel(param);
}

//--------------------------------------------------------------
void ofApp::setup()
{
    ofEnableDepthTest();
    ofSetFrameRate(24);
    Shapes shape = Shapes();
    mesh = shape.createIcosahedron();
	importedModel = new ofxAssimpModelLoader();
    Gui = new GUI();
    Gui->AddImageOpenedListener(std::bind(&ofApp::FileOpenCallback, this, std::placeholders::_1));
    Gui->AddPrintscreenTakenListener(std::bind(&ofApp::PrintScreenTakenCallback, this, std::placeholders::_1));
    Gui->AddPrintscreenSelectionListener(std::bind(&ofApp::PrintScreenSectionCallback, this, std::placeholders::_1));
    Gui->AddModeChangedListener(std::bind(&ofApp::ModeChangeCallback, this, std::placeholders::_1));
	Gui->AddObjFileImportedListener(std::bind(&ofApp::ImportObjFileCallback, this, std::placeholders::_1));
    mouseWatcher = new MouseWatcher();
    //mousePressed.bind(&ofApp::someMouseHandler, this);

}

void ofApp::beginSelectionZoneDraw(int x, int y)
{
	bool a = true;
	for (int i = 0; i < 12; i++)
	{
		if (mouseDownDelegates[i] == MouseActionDelegate(this, &ofApp::beginSelectionZoneDraw))
		{
			mouseDownDelegates[i].clear();
			break;
		}
	}
}

//--------------------------------------------------------------
void ofApp::update()
{

}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofEnableDepthTest();
	ofPushMatrix();
	ofTranslate(400, 400);
	ofScale(200, 200);
	ofRotateY(iteration++);
	ofColor colours[20] = {
		ofColor::red,			//0
		ofColor::orange,		//1
		ofColor::yellow,		//2
		ofColor::green,			//3
		ofColor::blue,			//4
		ofColor::violet,		//5
		ofColor::magenta,		//6
		ofColor::darkRed,		//7
		ofColor::darkGreen,		//8
		ofColor::darkBlue,		//9
		ofColor::darkTurquoise,	//10
		ofColor::darkViolet,	//11
		ofColor::darkMagenta,	//12
		ofColor::gold,			//13
		ofColor::lightGreen,	//14
		ofColor::lightBlue,		//15
		ofColor::lightPink,		//16
		ofColor::white,			//17
		ofColor::grey,			//18
		ofColor::black			//19
	};
	for (size_t i = 0; i < mesh->getUniqueFaces().size(); i++)
	{
		/*for (size_t j = 0; j < 3; j++)
		{*/
			ofMeshFace face = mesh->getUniqueFaces().at(i/**3+j*/);

			ofSetColor(colours[i]);

			ofDrawTriangle(face.getVertex(0), face.getVertex(1), face.getVertex(2));
		/*}*/
	}
	for (size_t i = 0; i < mesh->getVertices().size(); i++)
	{
		ofVec3f vertex = mesh->getVertex(i);
		ofSetColor(colours[i]);
		ofDrawSphere(vertex, 0.1);
	}
	//mesh->drawFaces();
	ofPopMatrix();
	ofPushMatrix();
	ofTranslate(300, 300);
	importedModel->draw(OF_MESH_FILL);
	ofPopMatrix();

	ofDisableDepthTest();
	Gui->Draw();
	mouseWatcher->Draw();
    for (vector<Shape * >::iterator i = visibleShapes.begin(); i != visibleShapes.end(); i++)
	{
		//Image * image = new Image((*i).Name);
		//image->load((*i).Name);
		//image->draw((*i).X, (*i).Y);
		//(*i).Width = image->getWidth();
		//(*i).Height = image->getHeight();
        (*i)->Draw();
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
    for(vector<Shape * >::iterator i = visibleShapes.begin(); i != visibleShapes.end(); i++){
        if((*i)->IsPointWithinBounds(x, y)){
            (*i)->ShowBorders(true);
        }else{
            (*i)->ShowBorders(false);
        }
    }
}
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
    isRecordingMouseMouvements = true;
    mouseWatcher->Record(x, y);

    if(actionMode == GUI::Edit){
        if(button == 0 || button == 2){

            /*if(selectedShapes != nullptr){
                selectedShapes->AffectVector(x, y, mouseWatcher->CurretVector(), button == 2);
            }*/

            for(vector<Shape * >::iterator i = selectedShapes.begin(); i != selectedShapes.end(); i++){
                (*i)->AffectVector(x, y, mouseWatcher->CurretVector(), button == 2);
            }
        }
    }else{//
        for(vector<Shape * >::iterator i = visibleShapes.begin(); i != visibleShapes.end(); i++){
            if(mouseWatcher->TopLeftPoint()->x < (*i)->BottomRightPoint()->x &&
               mouseWatcher->BottomRightPoint()->x < (*i)->TopLeftPoint()->x &&
               mouseWatcher->TopLeftPoint()->y < (*i)->BottomRightPoint()->y &&
               mouseWatcher->BottomRightPoint()->y < (*i)->TopLeftPoint()->y){
                (*i)->ShowBorders(true);
                selectedShapes.push_back((*i));
            }//mouseWatcher
        }
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{

    if(actionMode == GUI::Select)
        mouseWatcher->ShouldShowSelectionZone(true);
    if(button == 0 || button == 2){
        for(vector<Shape * >::iterator i = visibleShapes.begin(); i != visibleShapes.end(); i++){
            if((*i)->IsPointWithinBounds(x, y)){
                selectedShapes.clear();
                selectedShapes.push_back((*i));
                break;
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

    for(vector<Shape * >::iterator i = selectedShapes.begin(); i != selectedShapes.end(); i++){
        (*i)->ShowBorders(false);
    }
    selectedShapes.clear();
    if(button == 0){
        isRecordingMouseMouvements = false;
        mouseWatcher->StopRecording();
    }else if(button == 2){
        for(vector<Shape * >::iterator i = visibleShapes.begin(); i != visibleShapes.end(); i++){
            (*i)->AffectVector(x, y, mouseWatcher->CurretVector(), false);
        }
    }

    for (int i=0; i<12; i++) {
            if (!mouseUpDelegates[i]) {
                printf("Delegate is empty\n");
            } else {
                mouseUpDelegates[i](x, y);
            };
        }

    mouseWatcher->ShouldShowSelectionZone(false);
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
