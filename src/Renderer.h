#pragma once

#include "Structure.h"
#include "MouseWatcher.h"
#include "GUI.h"
#include "ScreenshotManager.h"
#include "Shapes.h"
#include "ofxAssimpModelLoader.h"
#include "Image.h"
#include "Shapes2d/Triangle2D.h"
#include "Shapes2d/Rectangle2D.h"
#include "Shapes2d/Ellipse2D.h"
#include "Shapes2d/Courbes/BSpliline.h"
#include "Shapes2d/Courbes/CatmullRom.h"
#include "Camera/CameraManager.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void TestMoveLeft();
	void TestMoveRight();
	void TestMoveUp();
	void TestMoveDown();
	void TestMoveDiag();
	void TestZoomIn();
	void TestZoomOut();
	void TestRotateZ();
	void TestRotateZNeg();
	void TestRotateX();
	void TestRotateXNeg();
	void TestRotateY();
	void TestRotateYNeg();
	void TestCreateTetrahedron();
	void TestCreateHexahedron();
	void TestCreateOctahedron();
	void TestCreateDodecahedron();
	void TestCreateIsocahedron();
	void TestSelectNext();
	void TestSelectPrevious();
	void TestDeselectAll();

	void Setup();
	void Update();
	void Draw();
    void SetMouseRecorder(MouseWatcher * mouseRecorder);
    void FileOpenCallback(string param);
    void PrintScreenTakenCallback(string param);
    void PrintScreenSectionCallback(string arg);
    void AssociateShapesCallback(string arg);
    void DissociateShapesCallback(string arg);
	void ImportObjFileCallback(string param);
    void drawBSplineWorker();
    void drawCRomWorker();
    void CameraChangedCallback(const GUI::CameraSelected & activeCamera);
    void VFOVChangedCallback(float val);
    void HFOVCallback(float val);
    void FarClipChangedCallback(int val);
    void NearClipChangedCallback(int val);
    void AspectRatioChangedCallback(const GUI::AspectRatio & aspectRatio);
    void ProjectionChangedCallback(const GUI::ProjectionType & projection);

    void KeyDown(int key);
    void KeyUp(int key);
private:
	int testSelectedElement = -1;
	Structure* sceneStructure;
	float cameraOffset;

	float oscillation;

	float scaleCube;
	float scaleSphere;
	float scaleTeapot;

	float xCenter;
	float yCenter;

	float speedMotion;
	float speedOscillation;

	float xOffset;
	float zOffset;

	float xDelta;
	float zDelta;

	float xInitial;
	float yInitial;

    float squareARMultiplier = 4.f/3.f,
    wideARMultiplier = 16.f/9.f,
    ultraWideARMultiplier = 21.f/9.f;

	int framebufferWidth;
	int framebufferHeight;

	int glVersionMajor;
	int glVersionMinor;

	bool isActiveLightAmbient;
	bool isActiveLightDirectional;
	bool isActiveLightPoint;
	bool isActiveLightSpot;

	bool isFlipAxisY;
    bool isVerbose;

    ofLight GuiLight;
    GUI* Gui;
    void ModeChangeCallback(GUI::ActionType newMode);
    void screenSectionSectionWorker(int x, int y, int button);

    ofLight ambientLight;
    CameraManager cameraManager;
    void drawCallback();

    //------ MouseWatcher attributes
    MouseWatcher * mouseWatcher;
    MouseWatcher::MouseActionDelegate * mouseDownDelegate;
    MouseWatcher::MouseActionDelegate * mouseUpDelegate;
    MouseWatcher::MouseActionDelegate * mouseClickDelegate;
    MouseWatcher::MouseActionDelegate * mouseDragDelegate;
    MouseWatcher::MouseActionDelegate * screenshotSectionDelegate = new MouseWatcher::MouseActionDelegate(this, &Renderer::screenSectionSectionWorker);

    std::vector<Shape*> visibleShapes;
    std::vector<Shape*> selectedShapes;
    std::vector<int> pressedKeys;
    void saveFile(string path, std::ifstream & file);

	float oscillate(float time, float amplitude, float period, float shift, float offset)
	{
		return amplitude * sin((time - shift) * 2 * PI / period) + offset;
	}

    void addVisibleShape(Shape * toAdd);
    void removeVisibleShape(Shape * toRemove);
    void addSelectedShape(Shape * toAdd);
    void removeSelectedShape(Shape * toRemove);

    void reset();
    void mouseDownHandler(int x, int y, int button);
    void mouseUpHandler(int x, int y, int button);
    void mouseClickHandler(int x, int y, int button);
    void mouseDragHandler(int x, int y, int button);

    void clearSelectedShapes();

    MouseWatcher::MouseActionDelegate * shapeDelegateWorker;
    MouseWatcher::MouseActionDelegate * unbindShapeDelegateWorker;
    MouseWatcher::MouseActionDelegate * dissociateShapesDelegateWorker;

    void drawTriangleManager(string param);
    void drawRectangleManager(string param);
    void drawEllipseManager(string param);
    void drawBSplineManager();
    void drawShapeWorker(int x, int y, int button);
    void unbindShapeWorkers(int x, int y, int button);
    void dissociateShapesWorkers(int x, int y, int button);

    bool isCtrlDown();
};
