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
	void TestRotateZ2();

	void Setup();
	void Update();
	void Draw();
    void SetMouseRecorder(MouseWatcher * mouseRecorder);
    void FileOpenCallback(string param);
    void PrintScreenTakenCallback(string param);
    void PrintScreenSectionCallback(string arg);
    void AssociateShapesCallback(string arg);
    void KeyDown(int key);
    void KeyUp(int key);
private:
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

    GUI* Gui;
    void ModeChangeCallback(GUI::ActionType newMode);
    void screenSectionSectionWorker(int x, int y, int button);

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

    void drawTriangleManager(string param);
    void drawRectangleManager(string param);
    void drawEllipseManager(string param);
    void drawShapeWorker(int x, int y, int button);
    void unbindShapeWorkers(int x, int y, int button);
};
