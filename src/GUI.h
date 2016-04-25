#ifndef GUI_H
#define GUI_H

#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#ifdef __linux__
#include "gtk/gtk.h"
#endif

class GUI
{
public:
	enum ActionType { Select, Edit };
	enum CameraSelected { Front, Back };
	enum AspectRatio { Square, Wide, UltraWide };
	enum ProjectionType { Perspective, Orthogonal };
	GUI();
	void Draw();
	void Show();
	void Hide();
    bool isFreeView() const;
	void SetCurrentMode(ActionType newMode);
	ActionType GetCurrentMode();
	int getCurveControlPoints() const;
	int getSurfaceControlCount1() const;
	int getSurfaceControlCount2() const;
	int getSurfaceControlCount3() const;
	int getSurfaceControlCount4() const;
	void AddImageOpenedListener(std::function<void(std::string)> fnc);
	void AddPrintscreenSelectionListener(std::function<void(std::string)> fnc);
	void AddPrintscreenTakenListener(std::function<void(std::string)> fnc);
	void AddPrintscreenBlurTakenListener(std::function<void(std::string)> fnc);
	void AddModeChangedListener(std::function<void(GUI::ActionType)> fnc);
	void AddObjFileImportedListener(std::function<void(std::string)> fnc);
	void AddHeightMapListener(std::function<void(std::string)> fnc);
	void AddCreateTriangleListener(std::function<void(std::string)> fnc);
	void AddCreateRectangleListener(std::function<void(std::string)> fnc);
	void AddCreateEllipseListener(std::function<void(std::string)> fnc);
	void AddAssociateShapesListener(std::function<void(std::string)> fnc);
	void AddDissociateShapesListener(std::function<void(std::string)> fnc);
	void AddBSplineCreateListener(std::function<void()> fnc);
	void AddCRomCreateListener(std::function<void()> fnc);
	void AddSurfaceCreateListener(std::function<void()> fnc);

	void AddCameraChangedListener(std::function<void(GUI::CameraSelected)> fnc);
	void AddVFOVChangedListener(std::function<void(float)> fnc);
	void AddHFOVChangedListener(std::function<void(float)> fnc);
	void AddFarClipChangedListener(std::function<void(int)> fnc);
	void AddNearClipChangedListener(std::function<void(int)> fnc);
	void AddAspectRatioChangedListener(std::function<void(AspectRatio)> fnc);
	void AddProjectionChangedListener(std::function<void(ProjectionType)> fnc);

	void setVFOV(const float val);
	void setHFOV(const float val);

	ofColor * GetCurrentColor()
	{
		outputColor = color;
		return &(outputColor);
	}
	string RequestSaveFilePath(string defaultName);
private:

    bool isInFreeView;
    int xPos,
        yPos,
        curveControlPoints = 5,
        surfaceControlCount1 = 2,
        surfaceControlCount2 = 2,
        surfaceControlCount3 = 2,
        surfaceControlCount4 = 2;

    ofxPanel toolsToggleGui;
    ofxToggle freeViewToggle;
	ofxButton openFileBtn;
	ofxButton openHeightMapBtn;
	ofxButton printscreenSection;
	ofxButton printscreen;
	ofxButton printscreenBlur;
	ofxButton importObjFile;
    ofxButton drawTriangle;
    ofxButton drawRectangle;
    ofxButton drawEllipse;
    ofxButton associateShapes;
    ofxButton dissociateShapes;
    ofxToggle selectionToggle, editToggle;
    ofxColorSlider color;
    ofColor  outputColor;
    ofxPanel gui;
    ofxGuiGroup courbesGroup;
    ofxButton bSplineCreate, CRomCreate;
    ofxIntSlider controlPointsSlider;
    ofxButton surfaceCreate;
    ofxGuiGroup surfaceGroup;
    ofxIntSlider surfaceSide1;
    ofxIntSlider surfaceSide2;
    ofxIntSlider surfaceSide3;
    ofxIntSlider surfaceSide4;

    ofxPanel cameraGui;
    ofxGuiGroup cameraPickerGroup;
    ofxToggle frontToggle, backToggle;
    ofxFloatSlider fovVSlider,
              fovHSlider;
    ofxIntSlider farClipSlider,
              nearClipSlider;
    ofxGuiGroup aspectRatioGroup, projectionGroup;
    ofxToggle squareToggle, wideToggle, ulraWideToggle, perspectiveToggle, orthoToggle;

    void activePanelSwitchCaller(bool & inval);

    //Right-Side pane callers
	void openFileBtnCallback();
	void openHeightMapBtnCallback();
	void openFilePrintscreenCallback();
	void openFilePrintscreenBlurCallback();
	void selectionToggleCallback(bool & inval);
	void editToggleCallback(bool & inval);
	void callScreenSectionCallback();
	void importObjFileCallBack();
	void createTriangleCaller();
	void createRectangleCaller();
	void createEllipseCaller();
	void associateShapesCaller();
	void dissociateShapesCaller();
	void bSplineCreateCaller();
	void cRomCreateCaller();
	void controlPointsSliderCaller(int & val);
	void surfaceCreateCaller();
	void surfacePoints1SliderCaller(int & val);
	void surfacePoints2SliderCaller(int & val);
	void surfacePoints3SliderCaller(int & val);
	void surfacePoints4SliderCaller(int & val);

	//Left-side pane callers
	void frontCameraCaller(bool & inval);
	void backCameraCaller(bool & inval);
	void VFOVCaller(float & val);
	void HFOVCaller(float & val);
	void FarClipCaller(int & val);
	void NearClipCaller(int & val);
	void squareCaller(bool & inval);
	void wideCaller(bool & inval);
	void ultraWideCaller(bool & inval);
	void perspectiveCaller(bool & inval);
	void orthogonalCaller(bool & inval);


	ofFileDialogResult requestUsrFile();
	ofFileDialogResult saveUsrFile(string defaultName);
	std::function<void(std::string)> imageOpenCallback;
	std::function<void(std::string)> heightMapOpenCallback;
	std::function<void(std::string)> printScreenSelectionCallback;
	std::function<void(std::string)> printScreenTakenCallback;
	std::function<void(std::string)> printScreenBlurTakenCallback;
	std::function<void(std::string)> objFileImportedCallback;
	std::function<void(std::string)> createTriangleCallback;
	std::function<void(std::string)> createRectangleCallback;
	std::function<void(std::string)> createEllipseCallback;
	std::function<void(std::string)> associateShapesCallback;
	std::function<void(std::string)> dissociateShapesCallback;
	std::function<void(GUI::ActionType)> modeChangedCallback;
	std::function<void()> bSplineCreateCallback;
	std::function<void()> cRomCreateCallback;
	std::function<void()> surfaceCreateCallback;

	std::function<void(GUI::CameraSelected)> cameraChangedCallback;
	std::function<void(float val)> VFOVChangedCallback;
	std::function<void(float val)> HFOVChangedCallback;
	std::function<void(int val)> FarClipChangedCallback;
	std::function<void(int val)> NearClipChangedCallback;
	std::function<void(GUI::AspectRatio)> aspectRatioChangedCallback;
	std::function<void(GUI::ProjectionType)> projectionChangedCallback;

};

#endif // GUI_H
