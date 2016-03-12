#include "Renderer.h"


Renderer::Renderer()
{
	this->sceneStructure = new Structure();

    Gui = new GUI();
    Gui->AddImageOpenedListener(std::bind(&Renderer::FileOpenCallback, this, std::placeholders::_1));
    Gui->AddPrintscreenTakenListener(std::bind(&Renderer::PrintScreenTakenCallback, this, std::placeholders::_1));
    Gui->AddPrintscreenSelectionListener(std::bind(&Renderer::PrintScreenSectionCallback, this, std::placeholders::_1));
    //Gui->AddObjFileImportedListener(std::bind(&ofApp::ImportObjFileCallback, this, std::placeholders::_1));
}

Renderer::~Renderer()
{
	delete this->sceneStructure;
}

void Renderer::Setup()
{

    Gui->AddModeChangedListener(std::bind(&Renderer::ModeChangeCallback, this, std::placeholders::_1));

    mouseDownDelegate = new MouseWatcher::MouseActionDelegate(this, &Renderer::mouseDownHandler);
    mouseUpDelegate = new MouseWatcher::MouseActionDelegate(this, &Renderer::mouseUpHandler);
    mouseClickDelegate = new MouseWatcher::MouseActionDelegate(this, &Renderer::mouseClickHandler);
    mouseDragDelegate = new MouseWatcher::MouseActionDelegate(this, &Renderer::mouseDragHandler);

	ofSetFrameRate(60);
	ofSetSphereResolution(12);
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofEnableDepthTest();

	ofLight* light = new ofLight();
	light->setDiffuseColor(ofColor(255, 255, 255));
	light->setSpecularColor(ofColor(191, 191, 191));
	light->setPointLight();
	this->sceneStructure->shadersManager->AddLight(light);

	ofShader* colorFillShader = new ofShader();
	this->sceneStructure->shadersManager->AddShader(colorFillShader);
	colorFillShader->load("shader/V120/LambertVS.glsl", "shader/V120/LambertFS.glsl");
	this->sceneStructure->AddElement(Shapes::createCube());

	reset();
    //ofSetLogLevel(ofLogLevel::OF_LOG_WARNING);
}

void Renderer::Update()
{
	ofPushMatrix();
	ofShader* shader = this->sceneStructure->shadersManager->GetShader(0);
	shader->begin();
	shader->setUniform3f("colorAmbient", 0.9f, 0.1f, 0.1f);
	shader->setUniform3f("colorDiffuse", 0.0f, 0.5f, 0.5f);
	shader->setUniform3f("colorSpecular", 1.0f, 1.0f, 0.0f);
	shader->setUniform3f("color", 1.0f, 1.0f, 0.0f);
	shader->setUniform1f("brightness", 800.0f);
	shader->end();

	ofLight* light = this->sceneStructure->shadersManager->GetLight(0);
	light->setGlobalPosition(500,
		500,
		-zOffset * 1.5f);
	ofPopMatrix();
}

void Renderer::Draw()
{
	ofPushMatrix();
	this->sceneStructure->Draw();
    mouseWatcher->Draw();
    Gui->Draw();
    for(Shape * toShow : visibleShapes)
        toShow->Draw();
	ofPopMatrix();
}

void Renderer::FileOpenCallback(string param){
    std::ifstream input( param, std::ios::binary );

    std::replace(param.begin(), param.end(), '\\', '/');
    string imageName = param.substr(param.find_last_of("/"));
    saveFile("./data" + imageName, input);
    input.close();

    Image * newImage = new Image(imageName.substr(1));
    newImage->AffectVector((int)(newImage->TopRightPoint()->x /2), (int)(newImage->BottomLeftPoint()->y /2), new ofVec3f(100, 100));
    visibleShapes.push_back(newImage);
}

void Renderer::PrintScreenTakenCallback(string param){
    ScreenshotManager::TakeScreenshot(param, 0, 0, ofGetWindowWidth(), ofGetWindowHeight());
}

void Renderer::PrintScreenSectionCallback(string arg){
    mouseWatcher->AddMouseUpDelegate(screenshotSectionDelegate);
}

void Renderer::screenSectionSectionWorker(int x, int y, int button){

    ScreenshotManager::TakeScreenshot(Gui->RequestSaveFilePath("captureDEcran"), mouseWatcher->TopLeftPoint()->x, mouseWatcher->TopLeftPoint()->y,
                                      x - mouseWatcher->TopLeftPoint()->x, y - mouseWatcher->TopLeftPoint()->y);
    mouseWatcher->RemoveMouseUpDelegate(screenshotSectionDelegate);
    mouseWatcher->SetShowSelectionZone(Gui->GetCurrentMode() == GUI::Select);
}

void Renderer::SetMouseRecorder(MouseWatcher * mouseRecorder){
    mouseWatcher = mouseRecorder;
    mouseWatcher->AddMouseDownDelegate(mouseDownDelegate);
    mouseWatcher->AddMouseUpDelegate(mouseUpDelegate);
    mouseWatcher->AddMouseClickDelegate(mouseClickDelegate);
    mouseWatcher->AddMouseDragDelegate(mouseDragDelegate);
}

void Renderer::reset()
{
	// initialisation des variables
	framebufferWidth = ofGetWidth();
	framebufferHeight = ofGetHeight();

	// centre du framebuffer
	xCenter = framebufferWidth / 2.0f;
	yCenter = framebufferHeight / 2.0f;

	// configurer la lumi�re ponctuelle
	ofLight* light = this->sceneStructure->shadersManager->GetLight(0);
	light->setDiffuseColor(ofColor(255, 255, 255));
	light->setSpecularColor(ofColor(191, 191, 191));
	light->setPointLight();

	ofLog() << "<reset>";
}

void Renderer::ModeChangeCallback(GUI::ActionType newMode){
    mouseWatcher->SetShowSelectionZone(newMode == GUI::Select);
}

void Renderer::mouseDownHandler(int x, int y, int button){
    bool clickedOnSelectedShape = false;
    for(Shape* selected : selectedShapes){
        if(selected->IsPointWithinBounds(x, y)){
            clickedOnSelectedShape = true;
            break;
        }
    }
    if(!clickedOnSelectedShape){
        for(Shape* visible : visibleShapes){
            if(visible->IsPointWithinBounds(x, y)){
                selectedShapes.push_back(visible);
                visible->SetSelected(true);
                break;
            }
        }
    }

}
void Renderer::mouseUpHandler(int x, int y, int button){
    for(Shape* selected : selectedShapes){
        selected->AffectVector(x, y, mouseWatcher->CurretVector(), false);
    }
}
void Renderer::mouseClickHandler(int x, int y, int button){
    clearSelectedShapes();
    for(Shape* visible : visibleShapes){
        if(visible->IsPointWithinBounds(x, y)){
            selectedShapes.push_back(visible);
            visible->SetSelected(true);
            break;
        }
    }
}
void Renderer::mouseDragHandler(int x, int y, int button){
    switch (Gui->GetCurrentMode()) {
    case GUI::Edit:
        for(Shape * selected : selectedShapes)
            selected->AffectVector(x, y, mouseWatcher->CurretVector(), button == 2);
        break;
    default:
        break;
    }
}

void Renderer::saveFile(string path, std::ifstream & file)
{
    std::ofstream output(path, std::ios::binary);

    std::copy(
        std::istreambuf_iterator<char>(file),
        std::istreambuf_iterator<char>(),
        std::ostreambuf_iterator<char>(output));
    output.close();

}

void Renderer::clearSelectedShapes(){
    for(Shape* selected : selectedShapes){
        selected->SetSelected(false);
    }
    selectedShapes.clear();
}
