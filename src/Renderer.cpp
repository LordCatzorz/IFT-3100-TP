#include "Renderer.h"
#include "Object3D.h"
Shape2D* downCast2D;
Shape3D* downCast3D;


Renderer::Renderer()
{
	this->sceneStructure = new Structure();

    Gui = new GUI();
    Gui->AddImageOpenedListener(std::bind(&Renderer::FileOpenCallback, this, std::placeholders::_1));
    Gui->AddPrintscreenTakenListener(std::bind(&Renderer::PrintScreenTakenCallback, this, std::placeholders::_1));
    Gui->AddPrintscreenSelectionListener(std::bind(&Renderer::PrintScreenSectionCallback, this, std::placeholders::_1));
    //Gui->AddObjFileImportedListener(std::bind(&ofApp::ImportObjFileCallback, this, std::placeholders::_1));
    //Gui->AddModeChangedListener(std::bind(&Renderer::ModeChangeCallback, this, std::placeholders::_1));
    Gui->AddCreateTriangleListener(std::bind(&Renderer::drawTriangleManager, this, std::placeholders::_1));
    Gui->AddCreateRectangleListener(std::bind(&Renderer::drawRectangleManager, this, std::placeholders::_1));
    Gui->AddCreateEllipseListener(std::bind(&Renderer::drawEllipseManager, this, std::placeholders::_1));
    Gui->AddAssociateShapesListener(std::bind(&Renderer::AssociateShapesCallback, this, std::placeholders::_1));
    Gui->AddDissociateShapesListener(std::bind(&Renderer::DissociateShapesCallback, this, std::placeholders::_1));
}

Renderer::~Renderer()
{
	delete this->sceneStructure;
}

void Renderer::TestMoveLeft()
{
	this->sceneStructure->GetElement(0)->AddTranslation(ofVec3f(-10, 0, 0));
}

void Renderer::TestMoveRight()
{

	this->sceneStructure->GetElement(0)->AddTranslation(ofVec3f(10, 0, 0));
}

void Renderer::TestMoveUp()
{

	this->sceneStructure->GetElement(0)->AddTranslation(ofVec3f(0, -10, 0));
}

void Renderer::TestMoveDown()
{

	this->sceneStructure->GetElement(0)->AddTranslation(ofVec3f(0, 10, 0));
}

void Renderer::TestMoveDiag()
{

	this->sceneStructure->GetElement(0)->AddTranslation(ofVec3f(10, 20, 0));
}

void Renderer::TestZoomIn()
{
	this->sceneStructure->GetElement(0)->AddScale(true);
}

void Renderer::TestZoomOut()
{
	this->sceneStructure->GetElement(0)->AddScale(false);
}

void Renderer::TestRotateZ()
{
	this->sceneStructure->GetElement(0)->AddRotation(ofVec3f(25, 10, 0), 1);
}

void Renderer::TestRotateZ2()
{
	this->sceneStructure->GetElement(0)->AddRotation(ofVec3f(25, 10), 2);
}

void Renderer::Setup()
{

    mouseDownDelegate = new MouseWatcher::MouseActionDelegate(this, &Renderer::mouseDownHandler);
    mouseUpDelegate = new MouseWatcher::MouseActionDelegate(this, &Renderer::mouseUpHandler);
    mouseClickDelegate = new MouseWatcher::MouseActionDelegate(this, &Renderer::mouseClickHandler);
    mouseDragDelegate = new MouseWatcher::MouseActionDelegate(this, &Renderer::mouseDragHandler);
    unbindShapeDelegateWorker = new MouseWatcher::MouseActionDelegate(this, &Renderer::unbindShapeWorkers);
    dissociateShapesDelegateWorker = new MouseWatcher::MouseActionDelegate(this, &Renderer::dissociateShapesWorkers);


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
	Object3D* obj = new Object3D(Shapes::createDodecahedron()->getMeshPtr());
	obj->glTranslate(500, 500, 0);
	obj->glScale(200, 200, 200);
	//obj->glRotate(45, 0, 0, -0.5);
    //this->visibleShapes.push_back(obj);
    //this->sceneStructure->AddElement(obj);

    reset();
    //ofSetLogLevel(ofLogLevel::OF_LOG_WARNING);
}

void Renderer::Update()
{
	//((Object3D*)(this->sceneStructure->GetElement(0)))->glRotate(1, 0, 1, 0);
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
    Gui->Draw();
    for(Shape * toShow : visibleShapes){
        if (downCast2D = dynamic_cast<Shape2D*>(toShow))
        {
            if(downCast2D->GetParent() == nullptr)
                downCast2D->Draw();
        }
    }
	ofPopMatrix();
}

void Renderer::FileOpenCallback(string param)
{
	std::ifstream input(param, std::ios::binary);

	std::replace(param.begin(), param.end(), '\\', '/');
	string imageName = param.substr(param.find_last_of("/"));
	saveFile("./data" + imageName, input);
	input.close();

    Image * newImage = new Image(imageName.substr(1));
    newImage->AffectVector((int)(newImage->TopRightPoint()->x /2), (int)(newImage->BottomLeftPoint()->y /2), new ofVec3f(100, 100));
    addVisibleShape(newImage);
}

void Renderer::PrintScreenTakenCallback(string param)
{
	ScreenshotManager::TakeScreenshot(param, 0, 0, ofGetWindowWidth(), ofGetWindowHeight());
}

void Renderer::PrintScreenSectionCallback(string arg)
{    
    mouseWatcher->SetShowSelectionZone(true);
	mouseWatcher->AddMouseUpDelegate(screenshotSectionDelegate);
}

void Renderer::AssociateShapesCallback(string arg){
    if(selectedShapes.size() <= 1)
        return;
    Shape2D* parent;
    if (parent = dynamic_cast<Shape2D*>(selectedShapes.front()))
    {
        std::vector<Shape*>::iterator itr = selectedShapes.begin();
        itr++;
        for(itr; itr != selectedShapes.end(); ++itr){
            Shape2D* child;
            if (child = dynamic_cast<Shape2D*>(*itr)){
                parent->AddChild(child);
            }
        }
        clearSelectedShapes();
    }
    //Shape * parent = selectedShapes.front();

}

void Renderer::DissociateShapesCallback(string arg){
    mouseWatcher->AddMouseClickDelegate(dissociateShapesDelegateWorker);
}

void Renderer::KeyDown(int key){
    if(pressedKeys.size() == 0)
        pressedKeys.push_back(key);
    else{
        bool isInArray = false;
        for(int pkey : pressedKeys)
            if(pkey == key){
                isInArray = true;
                break;
            }
        if(!isInArray)
            pressedKeys.push_back(key);
    }
}

void Renderer::KeyUp(int key){
    for(std::vector<int>::iterator itr = pressedKeys.begin(); itr != pressedKeys.end(); itr++){
        if((*itr) == key){
            pressedKeys.erase(itr);
            break;
        }
    }
}

void Renderer::screenSectionSectionWorker(int x, int y, int button){

    ScreenshotManager::TakeScreenshot(Gui->RequestSaveFilePath("captureDEcran"), mouseWatcher->TopLeftPoint()->x, mouseWatcher->TopLeftPoint()->y,
                                      x - mouseWatcher->TopLeftPoint()->x, y - mouseWatcher->TopLeftPoint()->y);
    mouseWatcher->RemoveMouseUpDelegate(screenshotSectionDelegate);
    mouseWatcher->SetShowSelectionZone(false);

}

void Renderer::SetMouseRecorder(MouseWatcher * mouseRecorder)
{
	mouseWatcher = mouseRecorder;
	mouseWatcher->AddMouseDownDelegate(mouseDownDelegate);
	mouseWatcher->AddMouseUpDelegate(mouseUpDelegate);
	mouseWatcher->AddMouseClickDelegate(mouseClickDelegate);
	mouseWatcher->AddMouseDragDelegate(mouseDragDelegate);
}

void Renderer::addVisibleShape(Shape * toAdd){
    bool isInArray = false;
    for(std::vector<Shape*>::iterator itr = visibleShapes.begin(); itr != visibleShapes.end() && !isInArray; itr++){
        isInArray = toAdd == (*itr);
    }
    if(!isInArray)
        visibleShapes.push_back(toAdd);
}
void Renderer::removeVisibleShape(Shape * toAdd){
    for(std::vector<Shape*>::iterator itr = visibleShapes.end(); itr != visibleShapes.begin(); itr--){
        if(*itr == toAdd){
            visibleShapes.erase(itr);
            break;
        }
    }
}
void Renderer::addSelectedShape(Shape * toAdd){
    bool isInArray = false;
    for(std::vector<Shape*>::iterator itr = selectedShapes.begin(); itr != selectedShapes.end() && !isInArray; itr++){
        isInArray = toAdd == (*itr);
    }
    if(!isInArray)
        selectedShapes.push_back(toAdd);
}
void Renderer::removeSelectedShape(Shape * toAdd){
    for(std::vector<Shape*>::iterator itr = selectedShapes.end(); itr != selectedShapes.begin(); itr--){
        if(*itr == toAdd){
            selectedShapes.erase(itr);
            break;
        }
    }
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


/*void Renderer::ModeChangeCallback(GUI::ActionType newMode)
{
	mouseWatcher->SetShowSelectionZone(newMode == GUI::Select);
}*/

void Renderer::mouseDownHandler(int x, int y, int button)
{

	bool clickedOnSelectedShape = false;
	for (Shape* selected : selectedShapes)
	{
		if (selected->IsPointWithinBounds(x, y))
		{
			clickedOnSelectedShape = true;
			break;
		}
	}
	if (!clickedOnSelectedShape)
	{
		for (Shape* visible : visibleShapes)
		{
			if (visible->IsPointWithinBounds(x, y))
			{
                if(!isCtrlDown())
                    clearSelectedShapes();
				selectedShapes.push_back(visible);
				visible->SetSelected(true);
				break;
			}
		}
    }
}
void Renderer::mouseUpHandler(int x, int y, int button)
{
	for (Shape* selected : selectedShapes)
	{
		if (downCast2D = dynamic_cast<Shape2D*>(selected))
		{
			downCast2D->AffectVector(x, y, mouseWatcher->CurretVector(), false);
            downCast2D->ActionStop();
		}
		else if (downCast3D = dynamic_cast<Shape3D*>(selected))
		{
			//TODO::Implement;
		}
	}
}
void Renderer::mouseClickHandler(int x, int y, int button)
{
    if(!isCtrlDown())
        clearSelectedShapes();
    for(Shape* visible : visibleShapes){
        if(visible->IsPointWithinBounds(x, y)){
            addSelectedShape(visible);
            visible->SetSelected(true);
            break;
        }
    }
}
void Renderer::mouseDragHandler(int x, int y, int button)
{
    for(Shape * selected : selectedShapes){
        if (downCast2D = dynamic_cast<Shape2D*>(selected))
        {
            downCast2D->AffectVector(x, y, mouseWatcher->CurretVector(), button == 2 && downCast2D->IsPointWithinBounds(x, y));
        }
        else if (downCast3D = dynamic_cast<Shape3D*>(selected))
        {
            //TODO::Implement;
        }
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

void Renderer::clearSelectedShapes()
{
	for (Shape* selected : selectedShapes)
	{
		selected->SetSelected(false);
	}
	selectedShapes.clear();
}

void Renderer::drawTriangleManager(string param){
    clearSelectedShapes();
    if(shapeDelegateWorker != nullptr)
        mouseWatcher->RemoveMouseDragDelegate(shapeDelegateWorker);//mouseDownDelegate = new MouseWatcher::MouseActionDelegate(this, &Renderer::mouseDownHandler);
    delete shapeDelegateWorker;
    shapeDelegateWorker = nullptr;

    mouseWatcher->SetShowSelectionZone(false);
    addVisibleShape(new Triangle2D());

    (visibleShapes.back())->SetSelected(true);
    shapeDelegateWorker = new MouseWatcher::MouseActionDelegate(this, &Renderer::drawShapeWorker);
    mouseWatcher->AddMouseDragDelegate(shapeDelegateWorker);
    mouseWatcher->AddMouseUpDelegate(unbindShapeDelegateWorker);
}

void Renderer::drawRectangleManager(string param){
    clearSelectedShapes();
    if(shapeDelegateWorker != nullptr)
        mouseWatcher->RemoveMouseDragDelegate(shapeDelegateWorker);//mouseDownDelegate = new MouseWatcher::MouseActionDelegate(this, &Renderer::mouseDownHandler);
    delete shapeDelegateWorker;
    shapeDelegateWorker = nullptr;

    mouseWatcher->SetShowSelectionZone(false);
    addVisibleShape(new Rectangle2D());

    (visibleShapes.back())->SetSelected(true);
    shapeDelegateWorker = new MouseWatcher::MouseActionDelegate(this, &Renderer::drawShapeWorker);
    mouseWatcher->AddMouseDragDelegate(shapeDelegateWorker);
    mouseWatcher->AddMouseUpDelegate(unbindShapeDelegateWorker);
}

void Renderer::drawEllipseManager(string param){
    clearSelectedShapes();
    if(shapeDelegateWorker != nullptr)
        mouseWatcher->RemoveMouseDragDelegate(shapeDelegateWorker);//mouseDownDelegate = new MouseWatcher::MouseActionDelegate(this, &Renderer::mouseDownHandler);
    delete shapeDelegateWorker;
    shapeDelegateWorker = nullptr;

    mouseWatcher->SetShowSelectionZone(false);
    addVisibleShape(new Ellipse2D());

    (visibleShapes.back())->SetSelected(true);
    shapeDelegateWorker = new MouseWatcher::MouseActionDelegate(this, &Renderer::drawShapeWorker);
    mouseWatcher->AddMouseDragDelegate(shapeDelegateWorker);
    mouseWatcher->AddMouseUpDelegate(unbindShapeDelegateWorker);
}

void Renderer::drawShapeWorker(int x, int y, int button){
    if (downCast2D = dynamic_cast<Shape2D*>(visibleShapes.back()))
    {
        ofColor tmpColor = *(Gui->GetCurrentColor());
        ((Shape2D *)visibleShapes.back())->SetColor(&tmpColor);
        downCast2D->Create(mouseWatcher->TopLeftPoint()->x, mouseWatcher->TopLeftPoint()->y, mouseWatcher->TopRightPoint()->x - mouseWatcher->TopLeftPoint()->x, mouseWatcher->BottomLeftPoint()->y - mouseWatcher->TopLeftPoint()->y);
    }
}

void Renderer::unbindShapeWorkers(int x, int y, int button){
    if(shapeDelegateWorker != nullptr)
        mouseWatcher->RemoveMouseDragDelegate(shapeDelegateWorker);
    mouseWatcher->RemoveMouseUpDelegate(unbindShapeDelegateWorker);
    delete shapeDelegateWorker;
    shapeDelegateWorker = nullptr;
    (visibleShapes.back())->SetSelected(false);
    //mouseWatcher->SetShowSelectionZone(Gui->GetCurrentMode() == GUI::Select);
}

void Renderer::dissociateShapesWorkers(int x, int y, int button){
    for(Shape * selected : visibleShapes){
        if (downCast2D = dynamic_cast<Shape2D*>(selected))
        {
            if(downCast2D->IsPointWithinBounds(x, y)){
                clearSelectedShapes();
                downCast2D->ClearChildren();
                mouseWatcher->RemoveMouseClickDelegate(dissociateShapesDelegateWorker);
            }
        }
    }
}
bool Renderer::isCtrlDown(){
    for(std::vector<int>::iterator itr = pressedKeys.begin(); itr != pressedKeys.end(); itr++){
        if((*itr) == 768)
            return true;
    }
    return false;
}
