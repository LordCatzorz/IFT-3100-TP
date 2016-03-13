#include "Renderer.h"


Renderer::Renderer()
{
	this->sceneStructure = new Structure();

    Gui = new GUI();
    Gui->AddImageOpenedListener(std::bind(&Renderer::FileOpenCallback, this, std::placeholders::_1));
    Gui->AddPrintscreenTakenListener(std::bind(&Renderer::PrintScreenTakenCallback, this, std::placeholders::_1));
    Gui->AddPrintscreenSelectionListener(std::bind(&Renderer::PrintScreenSectionCallback, this, std::placeholders::_1));
    //Gui->AddObjFileImportedListener(std::bind(&ofApp::ImportObjFileCallback, this, std::placeholders::_1));
    Gui->AddModeChangedListener(std::bind(&Renderer::ModeChangeCallback, this, std::placeholders::_1));
    Gui->AddCreateTriangleListener(std::bind(&Renderer::drawTriangleManager, this, std::placeholders::_1));
    Gui->AddCreateRectangleListener(std::bind(&Renderer::drawRectangleManager, this, std::placeholders::_1));
    Gui->AddCreateEllipseListener(std::bind(&Renderer::drawEllipseManager, this, std::placeholders::_1));

}

Renderer::~Renderer()
{
	delete this->sceneStructure;
}

void Renderer::Setup()
{

    mouseDownDelegate = new MouseWatcher::MouseActionDelegate(this, &Renderer::mouseDownHandler);
    mouseUpDelegate = new MouseWatcher::MouseActionDelegate(this, &Renderer::mouseUpHandler);
    mouseClickDelegate = new MouseWatcher::MouseActionDelegate(this, &Renderer::mouseClickHandler);
    mouseDragDelegate = new MouseWatcher::MouseActionDelegate(this, &Renderer::mouseDragHandler);
    unbindShapeDelegateWorker = new MouseWatcher::MouseActionDelegate(this, &Renderer::unbindShapeWorkers);

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
    colorFillShader->load("shader/v330/PhongVS.glsl", "shader/v330/PhongFS.glsl");
    this->sceneStructure->AddElement(Shapes::createCube());

    reset();
    //ofSetLogLevel(ofLogLevel::OF_LOG_WARNING);
}

void Renderer::Update()
{
    ofShader* shader = this->sceneStructure->shadersManager->GetShader(0);
	shader->begin();
	shader->setUniform3f("colorAmbient", 0.1f, 0.1f, 0.1f);
	shader->setUniform3f("colorDiffuse", 0.0f, 0.5f, 0.5f);
	shader->setUniform3f("colorSpecular", 1.0f, 1.0f, 0.0f);
	shader->setUniform3f("color", 1.0f, 1.0f, 0.0f);
	shader->setUniform1f("brightness", 400.0f);
	shader->end();

	ofLight* light = this->sceneStructure->shadersManager->GetLight(0);
	light->setGlobalPosition(
		ofMap(ofGetMouseX() / (float) framebufferWidth, 0.0f, 1.0f, -framebufferWidth / 2.0, framebufferWidth / 2.0),
		ofMap(ofGetMouseY() / (float) framebufferHeight, 0.0f, 1.0f, -framebufferHeight / 2.0, framebufferHeight / 2.0),
		-zOffset * 1.5f);
}

void Renderer::Draw()
{
	this->sceneStructure->Draw();
    mouseWatcher->Draw();
    Gui->Draw();
    for(Shape * toShow : visibleShapes)
        toShow->Draw();
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

void Renderer::drawTriangleManager(string param){
    if(shapeDelegateWorker != nullptr)
        mouseWatcher->RemoveMouseDragDelegate(shapeDelegateWorker);//mouseDownDelegate = new MouseWatcher::MouseActionDelegate(this, &Renderer::mouseDownHandler);
    delete shapeDelegateWorker;
    shapeDelegateWorker = nullptr;

    mouseWatcher->SetShowSelectionZone(false);
    visibleShapes.push_back(new Triangle());

    (visibleShapes.back())->SetSelected(true);
    shapeDelegateWorker = new MouseWatcher::MouseActionDelegate(this, &Renderer::drawShapeWorker);
    mouseWatcher->AddMouseDragDelegate(shapeDelegateWorker);
    mouseWatcher->AddMouseUpDelegate(unbindShapeDelegateWorker);
}

void Renderer::drawRectangleManager(string param){
    if(shapeDelegateWorker != nullptr)
        mouseWatcher->RemoveMouseDragDelegate(shapeDelegateWorker);//mouseDownDelegate = new MouseWatcher::MouseActionDelegate(this, &Renderer::mouseDownHandler);
    delete shapeDelegateWorker;
    shapeDelegateWorker = nullptr;

    mouseWatcher->SetShowSelectionZone(false);
    visibleShapes.push_back(new Rectangle());

    (visibleShapes.back())->SetSelected(true);
    shapeDelegateWorker = new MouseWatcher::MouseActionDelegate(this, &Renderer::drawShapeWorker);
    mouseWatcher->AddMouseDragDelegate(shapeDelegateWorker);
    mouseWatcher->AddMouseUpDelegate(unbindShapeDelegateWorker);
}

void Renderer::drawEllipseManager(string param){
    if(shapeDelegateWorker != nullptr)
        mouseWatcher->RemoveMouseDragDelegate(shapeDelegateWorker);//mouseDownDelegate = new MouseWatcher::MouseActionDelegate(this, &Renderer::mouseDownHandler);
    delete shapeDelegateWorker;
    shapeDelegateWorker = nullptr;

    mouseWatcher->SetShowSelectionZone(false);
    visibleShapes.push_back(new Ellipse());

    (visibleShapes.back())->SetSelected(true);
    shapeDelegateWorker = new MouseWatcher::MouseActionDelegate(this, &Renderer::drawShapeWorker);
    mouseWatcher->AddMouseDragDelegate(shapeDelegateWorker);
    mouseWatcher->AddMouseUpDelegate(unbindShapeDelegateWorker);
}

void Renderer::drawShapeWorker(int x, int y, int button){
    ((Shapes2d * )visibleShapes.back())->Create(mouseWatcher->TopLeftPoint()->x, mouseWatcher->TopLeftPoint()->y, mouseWatcher->TopRightPoint()->x - mouseWatcher->TopLeftPoint()->x, mouseWatcher->BottomLeftPoint()->y - mouseWatcher->TopLeftPoint()->y);
}

void Renderer::unbindShapeWorkers(int x, int y, int button){
    if(shapeDelegateWorker != nullptr)
        mouseWatcher->RemoveMouseDragDelegate(shapeDelegateWorker);
    mouseWatcher->RemoveMouseUpDelegate(unbindShapeDelegateWorker);
    delete shapeDelegateWorker;
    shapeDelegateWorker = nullptr;
    (visibleShapes.back())->SetSelected(false);
    mouseWatcher->SetShowSelectionZone(Gui->GetCurrentMode() == GUI::Select);
}
