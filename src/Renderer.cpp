#include "Renderer.h"
#include "Object3D.h"
#include "HeightMap.h"
Object2D * downCast2D;

Renderer::Renderer()
{
	this->sceneStructure = new Structure();

	shapeDelegateWorker = NULL;
	unbindShapeDelegateWorker = NULL;
	dissociateShapesDelegateWorker = NULL;

	Gui = new GUI();
	Gui->AddImageOpenedListener(std::bind(&Renderer::FileOpenCallback, this, std::placeholders::_1));
	Gui->AddHeightMapListener(std::bind(&Renderer::HeightMapOpenCallback, this, std::placeholders::_1));
	Gui->AddPrintscreenTakenListener(std::bind(&Renderer::PrintScreenTakenCallback, this, std::placeholders::_1));
	Gui->AddPrintscreenBlurTakenListener(std::bind(&Renderer::PrintScreenTakenBlurCallback, this, std::placeholders::_1));
	Gui->AddPrintscreenSelectionListener(std::bind(&Renderer::PrintScreenSectionCallback, this, std::placeholders::_1));
    Gui->AddObjFileImportedListener(std::bind(&Renderer::ImportObjFileCallback, this, std::placeholders::_1));
	Gui->AddCreateTriangleListener(std::bind(&Renderer::drawTriangleManager, this, std::placeholders::_1));
	Gui->AddCreateRectangleListener(std::bind(&Renderer::drawRectangleManager, this, std::placeholders::_1));
	Gui->AddCreateEllipseListener(std::bind(&Renderer::drawEllipseManager, this, std::placeholders::_1));
	Gui->AddAssociateShapesListener(std::bind(&Renderer::AssociateShapesCallback, this, std::placeholders::_1));
	Gui->AddDissociateShapesListener(std::bind(&Renderer::DissociateShapesCallback, this, std::placeholders::_1));
	Gui->AddBSplineCreateListener(std::bind(&Renderer::drawBSplineWorker, this));
	Gui->AddCRomCreateListener(std::bind(&Renderer::drawCRomWorker, this));
	Gui->AddSurfaceCreateListener(std::bind(&Renderer::drawSurfaceWorker, this));
    Gui->RemoveSurfaceCreateListener(std::bind(&Renderer::removeSurfaceWorker, this));
	Gui->AddCameraChangedListener(std::bind(&Renderer::CameraChangedCallback, this, std::placeholders::_1));
	Gui->AddVFOVChangedListener(std::bind(&Renderer::VFOVChangedCallback, this, std::placeholders::_1));
	Gui->AddHFOVChangedListener(std::bind(&Renderer::HFOVCallback, this, std::placeholders::_1));
	Gui->AddFarClipChangedListener(std::bind(&Renderer::FarClipChangedCallback, this, std::placeholders::_1));
	Gui->AddNearClipChangedListener(std::bind(&Renderer::NearClipChangedCallback, this, std::placeholders::_1));
	Gui->AddAspectRatioChangedListener(std::bind(&Renderer::AspectRatioChangedCallback, this, std::placeholders::_1));
	Gui->AddProjectionChangedListener(std::bind(&Renderer::ProjectionChangedCallback, this, std::placeholders::_1));

	Gui->setVFOV(cameraManager.getVFOV());
	Gui->setHFOV(cameraManager.getHFOV());
}

Renderer::~Renderer()
{
	delete this->sceneStructure;
}

void Renderer::TestMoveLeft()
{
	for (Shape* shape : *(this->sceneStructure->GetElements()))
	{
		if (shape->GetSelected())
		{
			shape->AddTranslation(0, 0, ofVec3f(-10, 0, 0));
		}
	}
}

void Renderer::TestMoveRight()
{
	for (Shape* shape : *(this->sceneStructure->GetElements()))
	{
		if (shape->GetSelected())
		{
			shape->AddTranslation(0, 0, ofVec3f(10, 0, 0));
		}
	}
}

void Renderer::TestMoveUp()
{
	for (Shape* shape : *(this->sceneStructure->GetElements()))
	{
		if (shape->GetSelected())
		{
			shape->AddTranslation(0, 0, ofVec3f(0, -10, 0));
		}
	}
}

void Renderer::TestMoveDown()
{
	for (Shape* shape : *(this->sceneStructure->GetElements()))
	{
		if (shape->GetSelected())
		{
			shape->AddTranslation(0, 0, ofVec3f(0, 10, 0));
		}
	}
}

void Renderer::TestMoveDiag()
{
	for (Shape* shape : *(this->sceneStructure->GetElements()))
	{
		if (shape->GetSelected())
		{
			shape->AddTranslation(0, 0, ofVec3f(10, 20, 0));
		}
	}
}

void Renderer::TestZoomIn()
{
	for (Shape* shape : *(this->sceneStructure->GetElements()))
	{
		if (shape->GetSelected())
		{
			shape->AddScale(true);
		}
	}
}

void Renderer::TestZoomOut()
{
	for (Shape* shape : *(this->sceneStructure->GetElements()))
	{
		if (shape->GetSelected())
		{
			shape->AddScale(false);
		}
	}
}

void Renderer::TestRotateZ()
{
	for (Shape* shape : *(this->sceneStructure->GetElements()))
	{
		if (shape->GetSelected())
		{
			shape->AddRotation(ofVec3f(10, 0), 2);
		}
	}
}

void Renderer::TestRotateZNeg()
{
	for (Shape* shape : *(this->sceneStructure->GetElements()))
	{
		if (shape->GetSelected())
		{
			shape->AddRotation(ofVec3f(-10, 0), 2);
		}
	}
}

void Renderer::TestRotateX()
{
	for (Shape* shape : *(this->sceneStructure->GetElements()))
	{
		if (shape->GetSelected())
		{
			shape->AddRotation(ofVec3f(10, 0), 0);
		}
	}
}

void Renderer::TestRotateXNeg()
{
	for (Shape* shape : *(this->sceneStructure->GetElements()))
	{
		if (shape->GetSelected())
		{
			shape->AddRotation(ofVec3f(-10, 0), 0);
		}
	}
}

void Renderer::TestRotateY()
{
	for (Shape* shape : *(this->sceneStructure->GetElements()))
	{
		if (shape->GetSelected())
		{
			shape->AddRotation(ofVec3f(10, 0), 1);
		}
	}
}

void Renderer::TestRotateYNeg()
{
	for (Shape* shape : *(this->sceneStructure->GetElements()))
	{
		if (shape->GetSelected())
		{
			shape->AddRotation(ofVec3f(-10, 0), 1);
		}
	}
}

void Renderer::TestCreateTetrahedron()
{
	Object3D* obj = new Object3D("models/tetrahedron/tetrahedron.obj");
    obj->glTranslate(ofGetWindowWidth()*0.5, ofGetWindowHeight()*0.5, 0);
	this->sceneStructure->AddElement(obj);
}

void Renderer::TestCreateHexahedron()
{
	Object3D* obj = new Object3D("models/hexahedron/hexahedron.obj");
    obj->glTranslate(ofGetWindowWidth()*0.5, ofGetWindowHeight()*0.5, 0);
	this->sceneStructure->AddElement(obj);
}

void Renderer::TestCreateOctahedron()
{
	Object3D* obj = new Object3D("models/octahedron/octahedron.obj");
    obj->glTranslate(ofGetWindowWidth()*0.5, ofGetWindowHeight()*0.5, 0);
	this->sceneStructure->AddElement(obj);
}

void Renderer::TestCreateDodecahedron()
{
	Object3D* obj = new Object3D("models/dodecahedron/dodecahedron.obj");
    obj->glTranslate(ofGetWindowWidth()*0.5, ofGetWindowHeight()*0.5, 0);
	this->sceneStructure->AddElement(obj);
}

void Renderer::TestCreateIcosahedron()
{
	Object3D* obj = new Object3D("models/icosahedron/icosahedron.obj");
    obj->glTranslate(ofGetWindowWidth()*0.5, ofGetWindowHeight()*0.5, 0);
	this->sceneStructure->AddElement(obj);
}

void Renderer::TestDeselectAll()
{
	this->clearSelectedShapes();
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
    ofImage* textureImage = new ofImage("IFT3100H16_TP1.png");
	textureImage->bind(0);
	ofShader* defaultShader = new ofShader();
    this->sceneStructure->shadersManager->AddShader(defaultShader);

	cameraManager.setTarget(ofVec3f((ofGetWidth() / 2), (ofGetHeight() / 2)));
	cameraManager.setDistance(500);
	cameraManager.setup();
	ambientLight.setPosition(0, 0, -50);
	GuiLight.setPosition(0, 0, 10000);

    reset();
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
	GuiLight.enable();
	Gui->Draw();
    if(!Gui->isFreeView())
        mouseWatcher->Draw();
    GuiLight.disable();

    if(Gui->isFreeView())
        cameraManager.begin();

    ambientLight.enable();
	ofFill();
    ofPushMatrix();
    this->sceneStructure->Draw();

    ofPopMatrix();
	ambientLight.disable();
    if(Gui->isFreeView())
        cameraManager.end();
}

void Renderer::FileOpenCallback(string param)
{
	std::ifstream input(param, std::ios::binary);

	std::replace(param.begin(), param.end(), '\\', '/');
	string imageName = param.substr(param.find_last_of("/"));
	saveFile("./data" + imageName, input);
	input.close();

    Image * newImage = new Image(imageName.substr(1));
	addVisibleShape(newImage);
}

void Renderer::HeightMapOpenCallback(string param)
{
	std::ifstream input(param, std::ios::binary);

	std::replace(param.begin(), param.end(), '\\', '/');
	string imageName = param.substr(param.find_last_of("/"));
	saveFile("./data" + imageName, input);
	input.close();

	ofImage * newImage = new ofImage(imageName.substr(1));
	HeightMap * hm = new HeightMap();
    hm->Setup(newImage);
	addVisibleShape(hm);
}

void Renderer::PrintScreenTakenCallback(string param)
{
	ScreenshotManager::TakeScreenshot(param, 0, 0, ofGetWindowWidth(), ofGetWindowHeight());
}
void Renderer::PrintScreenTakenBlurCallback(string param)
{
	ScreenshotManager::TakeScreenshot(param, 0, 0, ofGetWindowWidth(), ofGetWindowHeight(), true);
}

void Renderer::PrintScreenSectionCallback(string arg)
{
	mouseWatcher->SetShowSelectionZone(true);
	mouseWatcher->AddMouseUpDelegate(screenshotSectionDelegate);
}

void Renderer::AssociateShapesCallback(string arg)
{
	if (selectedShapes.size() <= 1)
		return;
	Object2D* parent;
	if (parent = dynamic_cast<Object2D*>(selectedShapes.front()))
	{
		std::vector<Shape*>::iterator itr = selectedShapes.begin();
		itr++;
		for (itr; itr != selectedShapes.end(); ++itr)
		{
			Object2D* child;
			if (child = dynamic_cast<Object2D*>(*itr))
			{
				parent->AddChild(child);
			}
		}
		clearSelectedShapes();
    }

}

void Renderer::DissociateShapesCallback(string arg)
{
	mouseWatcher->AddMouseClickDelegate(dissociateShapesDelegateWorker);
}

void Renderer::ImportObjFileCallback(string param)
{
	Object3D* obj = new Object3D(param);
	obj->glTranslate(ofGetWindowWidth()*0.5, ofGetWindowHeight()*0.5, 0);

	this->sceneStructure->AddElement(obj);
}

void Renderer::CameraChangedCallback(const GUI::CameraSelected & activeCamera)
{
    cameraManager.switchCam(activeCamera == GUI::Front ? CameraManager::front : CameraManager::back);
}

void Renderer::VFOVChangedCallback(float val)
{
    cameraManager.setVFOV(val);
    Gui->setHFOV(cameraManager.getHFOV());
}

void Renderer::HFOVCallback(float val)
{
	cameraManager.setHFOV(val);
	Gui->setVFOV(cameraManager.getVFOV());
}

void Renderer::FarClipChangedCallback(int val)
{
	cameraManager.setFarClip(val);
}

void Renderer::NearClipChangedCallback(int val)
{
	cameraManager.setNearClip(val);
}

void Renderer::AspectRatioChangedCallback(const GUI::AspectRatio & aspectRatio)
{
	switch (aspectRatio)
	{
	case GUI::Wide:
		ofSetWindowShape((int) (ofGetHeight() * wideARMultiplier), ofGetHeight());
		cameraManager.setAspectRatio(CameraManager::wide);
		break;
	case GUI::UltraWide:
		ofSetWindowShape((int) (ofGetHeight() * ultraWideARMultiplier), ofGetHeight());
		cameraManager.setAspectRatio(CameraManager::ultraWide);
		break;
	default:
		ofSetWindowShape((int) (ofGetHeight() * squareARMultiplier), ofGetHeight());
		cameraManager.setAspectRatio(CameraManager::square);
		break;
	}
	Gui->setVFOV(cameraManager.getVFOV());
	Gui->setHFOV(cameraManager.getHFOV());
}

void Renderer::ProjectionChangedCallback(const GUI::ProjectionType & projection)
{
	if (projection == GUI::Orthogonal)
	{
		cameraManager.enableOrtho();
	}
	else
	{
		cameraManager.disableOrtho();
	}
}

int tmpY = 0;
void Renderer::KeyDown(int key)
{
	if (pressedKeys.size() == 0)
		pressedKeys.push_back(key);
	else
	{
		bool isInArray = false;
		for (int pkey : pressedKeys)
			if (pkey == key)
			{
				isInArray = true;
				break;
			}
		if (!isInArray)
			pressedKeys.push_back(key);
    }
    if(key == 'a'){
        cameraManager.setup(++tmpY);
    }else if(key == 'd'){
        cameraManager.setup(--tmpY);
    }

    ofLog() << tmpY;
}

void Renderer::KeyUp(int key)
{
	for (std::vector<int>::iterator itr = pressedKeys.begin(); itr != pressedKeys.end(); itr++)
	{
		if ((*itr) == key)
		{
			pressedKeys.erase(itr);
			break;
		}
	}
}


void Renderer::screenSectionSectionWorker(int x, int y, int button)
{

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

void Renderer::addVisibleShape(Shape * toAdd)
{
	bool isInArray = false;
	for (std::vector<Shape*>::iterator itr = visibleShapes.begin(); itr != visibleShapes.end() && !isInArray; itr++)
	{
		isInArray = toAdd == (*itr);
	}
    this->sceneStructure->AddElement(toAdd);
	if (!isInArray)
		visibleShapes.push_back(toAdd);
}
void Renderer::removeVisibleShape(Shape * toAdd)
{
	for (std::vector<Shape*>::iterator itr = visibleShapes.end(); itr != visibleShapes.begin(); itr--)
	{
        Shape * tmp = *itr;
		if (*itr == toAdd)
		{
            visibleShapes.erase(itr);
			break;
		}
	}
    for(int i = 0; i < sceneStructure->GetElementsCount(); i++){
        if(sceneStructure->GetElement(i) == toAdd){
            sceneStructure->RemoveElement(i);
            break;
        }
    }
}
void Renderer::addSelectedShape(Shape * toAdd)
{
	bool isInArray = false;
	for (std::vector<Shape*>::iterator itr = selectedShapes.begin(); itr != selectedShapes.end() && !isInArray; itr++)
	{
		isInArray = toAdd == (*itr);
	}
	if (!isInArray)
		selectedShapes.push_back(toAdd);
}
void Renderer::removeSelectedShape(Shape * toAdd)
{
	for (std::vector<Shape*>::iterator itr = selectedShapes.end(); itr != selectedShapes.begin(); itr--)
	{
		if (*itr == toAdd)
		{
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


void Renderer::mouseDownHandler(int x, int y, int button)
{
    if(Gui->isFreeView()){
        if (button == OF_MOUSE_BUTTON_4)
        {
            cameraManager.zoomIn();
        }
        else if (button == OF_MOUSE_BUTTON_5)
        {
            cameraManager.zoomOut();
        }
        else
        {
            cameraManager.notifyMousePressed(x, y, button);
        }
    }else{

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
                    if (!isKeyDown(261))
                        clearSelectedShapes();
                    selectedShapes.push_back(visible);
                    visible->SetSelected(true);
                    break;
                }
            }
        }
    }
}
void Renderer::mouseUpHandler(int x, int y, int button)
{
    if(Gui->isFreeView())
        cameraManager.notifyMouseReleased(x, y, button);
}
void Renderer::mouseClickHandler(int x, int y, int button)
{
	if (!isKeyDown(261))
		clearSelectedShapes();
	for (Shape* visible : *(this->sceneStructure->GetElements()) /*visibleShapes*/)
	{
		if (visible->IsPointWithinBounds(x, y))
		{
			addSelectedShape(visible);
			visible->SetSelected(true);
			break;
		}
	}

}
void Renderer::mouseDragHandler(int x, int y, int button)
{
    if(Gui->isFreeView()){
        cameraManager.notifyMouseDragged(x,y, button);
    }else{
        for (Shape * selected : selectedShapes)
        {
            if (button != 2)
                selected->AddTranslation(x, y, *(mouseWatcher->CurretVector()));
            else
            {
                bool rotated = false;
                if (isKeyDown('1'))
                {
                    selected->AddRotation(*(mouseWatcher->CurretVector()), 0);
                    rotated = true;
                }
                if (isKeyDown('2'))
                {
                    selected->AddRotation(*(mouseWatcher->CurretVector()), 1);
                    rotated = true;
                }
                if (isKeyDown('3'))
                {
                    selected->AddRotation(*(mouseWatcher->CurretVector()), 2);
                    rotated = true;
                }
                if (!rotated)
                {
                    selected->AddRotation(*(mouseWatcher->CurretVector()), 0);

                }
            }
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

void Renderer::drawTriangleManager(string param)
{
	clearSelectedShapes();
	if (shapeDelegateWorker != nullptr)
        mouseWatcher->RemoveMouseDragDelegate(shapeDelegateWorker);
	delete shapeDelegateWorker;
	shapeDelegateWorker = nullptr;

	mouseWatcher->SetShowSelectionZone(false);
	addVisibleShape(new Triangle2D());

	(visibleShapes.back())->SetSelected(true);
	shapeDelegateWorker = new MouseWatcher::MouseActionDelegate(this, &Renderer::drawShapeWorker);
	mouseWatcher->AddMouseDragDelegate(shapeDelegateWorker);
	mouseWatcher->AddMouseUpDelegate(unbindShapeDelegateWorker);
}

void Renderer::drawRectangleManager(string param)
{
	clearSelectedShapes();
	if (shapeDelegateWorker != nullptr)
        mouseWatcher->RemoveMouseDragDelegate(shapeDelegateWorker);
	delete shapeDelegateWorker;
	shapeDelegateWorker = nullptr;

	mouseWatcher->SetShowSelectionZone(false);
	addVisibleShape(new Rectangle2D());

	(visibleShapes.back())->SetSelected(true);
	shapeDelegateWorker = new MouseWatcher::MouseActionDelegate(this, &Renderer::drawShapeWorker);
	mouseWatcher->AddMouseDragDelegate(shapeDelegateWorker);
	mouseWatcher->AddMouseUpDelegate(unbindShapeDelegateWorker);
}

void Renderer::drawEllipseManager(string param)
{
	clearSelectedShapes();
	if (shapeDelegateWorker != nullptr)
        mouseWatcher->RemoveMouseDragDelegate(shapeDelegateWorker);
	delete shapeDelegateWorker;
	shapeDelegateWorker = nullptr;

	mouseWatcher->SetShowSelectionZone(false);
	addVisibleShape(new Ellipse2D());

	(visibleShapes.back())->SetSelected(true);
	shapeDelegateWorker = new MouseWatcher::MouseActionDelegate(this, &Renderer::drawShapeWorker);
	mouseWatcher->AddMouseDragDelegate(shapeDelegateWorker);
	mouseWatcher->AddMouseUpDelegate(unbindShapeDelegateWorker);
}

void Renderer::drawShapeWorker(int x, int y, int button)
{
    if(visibleShapes.size() > 0){
        if (downCast2D = dynamic_cast<Object2D*>(visibleShapes.back()))
        {
            ofColor tmpColor = *(Gui->GetCurrentColor());
            ((Object2D *) visibleShapes.back())->SetColor(&tmpColor);
            downCast2D->Create(mouseWatcher->TopLeftPoint()->x, mouseWatcher->TopLeftPoint()->y, mouseWatcher->TopRightPoint()->x - mouseWatcher->TopLeftPoint()->x, mouseWatcher->BottomLeftPoint()->y - mouseWatcher->TopLeftPoint()->y, mouseWatcher->isXInverted(), mouseWatcher->isYInverted());
        }
    }
}

void Renderer::drawBSplineWorker()
{
	clearSelectedShapes();

	if (shapeDelegateWorker != nullptr)
        mouseWatcher->RemoveMouseDragDelegate(shapeDelegateWorker);
	delete shapeDelegateWorker;
	shapeDelegateWorker = nullptr;

	mouseWatcher->SetShowSelectionZone(false);
	addVisibleShape(new BSpliline(Gui->getCurveControlPoints()));

	(visibleShapes.back())->SetSelected(true);
	shapeDelegateWorker = new MouseWatcher::MouseActionDelegate(this, &Renderer::drawShapeWorker);
	mouseWatcher->AddMouseDragDelegate(shapeDelegateWorker);
	mouseWatcher->AddMouseUpDelegate(unbindShapeDelegateWorker);
}

void Renderer::drawCRomWorker()
{
	clearSelectedShapes();

	if (shapeDelegateWorker != nullptr)
        mouseWatcher->RemoveMouseDragDelegate(shapeDelegateWorker);
	delete shapeDelegateWorker;
	shapeDelegateWorker = nullptr;

	mouseWatcher->SetShowSelectionZone(false);
	addVisibleShape(new CatmullRom(Gui->getCurveControlPoints()));

	(visibleShapes.back())->SetSelected(true);
	shapeDelegateWorker = new MouseWatcher::MouseActionDelegate(this, &Renderer::drawShapeWorker);
	mouseWatcher->AddMouseDragDelegate(shapeDelegateWorker);
	mouseWatcher->AddMouseUpDelegate(unbindShapeDelegateWorker);
}

void Renderer::drawSurfaceWorker()
{
	clearSelectedShapes();

	if (shapeDelegateWorker != nullptr)
        mouseWatcher->RemoveMouseDragDelegate(shapeDelegateWorker);
	delete shapeDelegateWorker;
	shapeDelegateWorker = nullptr;

	mouseWatcher->SetShowSelectionZone(false);
    addVisibleShape(new Surface(Gui->getSurfaceControlCount1(), Gui->getSurfaceControlCount2(), Gui->getSurfaceControlCount3(), Gui->getSurfaceControlCount4(), ofFloatColor(Gui->GetCurrentColor()->r / 255.f, Gui->GetCurrentColor()->g / 255.f, Gui->GetCurrentColor()->b / 255.f, Gui->GetCurrentColor()->a / 255.f)));

	(visibleShapes.back())->SetSelected(true);
	shapeDelegateWorker = new MouseWatcher::MouseActionDelegate(this, &Renderer::drawShapeWorker);
	mouseWatcher->AddMouseDragDelegate(shapeDelegateWorker);
	mouseWatcher->AddMouseUpDelegate(unbindShapeDelegateWorker);
}

Surface * verficationObect;
void Renderer::removeSurfaceWorker(){
    int i = 0;
    for(std::vector<Shape*>::iterator itr = visibleShapes.begin(); itr != visibleShapes.end(); itr++){
        if(verficationObect = dynamic_cast<Surface*>(*itr)){
            visibleShapes.erase(itr);
            sceneStructure->RemoveElement(i);
            break;
        }
        i++;
    }
    verficationObect = nullptr;
}

void Renderer::unbindShapeWorkers(int x, int y, int button)
{
	if (shapeDelegateWorker != nullptr)
		mouseWatcher->RemoveMouseDragDelegate(shapeDelegateWorker);
	mouseWatcher->RemoveMouseUpDelegate(unbindShapeDelegateWorker);
	delete shapeDelegateWorker;
	shapeDelegateWorker = nullptr;
    (visibleShapes.back())->SetSelected(false);
}

void Renderer::dissociateShapesWorkers(int x, int y, int button)
{
	for (Shape * selected : visibleShapes)
	{
        if (downCast2D = dynamic_cast<Object2D*>(selected))
		{
			if (downCast2D->IsPointWithinBounds(x, y))
			{
				clearSelectedShapes();
				downCast2D->ClearChildren();
				mouseWatcher->RemoveMouseClickDelegate(dissociateShapesDelegateWorker);
			}
		}
	}
}
bool Renderer::isKeyDown(char _keyCode)
{
	for (std::vector<int>::iterator itr = pressedKeys.begin(); itr != pressedKeys.end(); itr++)
	{
		if ((*itr) == _keyCode)
			return true;
	}
	return false;
}

