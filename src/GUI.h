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
    enum ActionType {Select, Edit};
    enum CameraSelected {Front, Back};
    enum AspectRatio {Square, Wide, UltraWide};
    enum ProjectionType {Perspective, Orthogonal};
    GUI();
    void Draw();
    void Show();
    void Hide();
    void SetCurrentMode(ActionType newMode);
    ActionType GetCurrentMode();
    int getCurveControlPoints() const;
    void AddImageOpenedListener(std::function<void(std::string)> fnc);
    void AddPrintscreenSelectionListener(std::function<void(std::string)> fnc);
    void AddPrintscreenTakenListener(std::function<void(std::string)> fnc);
    void AddModeChangedListener(std::function<void(GUI::ActionType)> fnc);
	void AddObjFileImportedListener(std::function<void(std::string)> fnc);
    void AddCreateTriangleListener(std::function<void(std::string)> fnc);
    void AddCreateRectangleListener(std::function<void(std::string)> fnc);
    void AddCreateEllipseListener(std::function<void(std::string)> fnc);
    void AddAssociateShapesListener(std::function<void(std::string)> fnc);
    void AddDissociateShapesListener(std::function<void(std::string)> fnc);
    void AddBSplineCreateListener(std::function<void()> fnc);
    void AddCRomCreateListener(std::function<void()> fnc);


    void AddCameraChangedListener(std::function<void(GUI::CameraSelected)> fnc);
    void AddVFOVChangedListener(std::function<void(float)> fnc);
    void AddHFOVChangedListener(std::function<void(float)> fnc);
    void AddFarClipChangedListener(std::function<void(int)> fnc);
    void AddNearClipChangedListener(std::function<void(int)> fnc);
    void AddAspectRatioChangedListener(std::function<void(AspectRatio)> fnc);
    void AddProjectionChangedListener(std::function<void(ProjectionType)> fnc);

    void setVFOV(const float val);
    void setHFOV(const float val);

    ofColor * GetCurrentColor(){
        outputColor = color;
        return &(outputColor);}
    string RequestSaveFilePath(string defaultName);
private:

    int xPos, yPos, curveControlPoints = 5;

	ofxButton openFileBtn;
    ofxButton printscreenSection;
    ofxButton printscreen;
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

    ofxPanel cameraGui;
    ofxGuiGroup cameraPickerGroup;
    ofxToggle frontToggle, backToggle;
    ofxFloatSlider fovVSlider,
              fovHSlider;
    ofxIntSlider farClipSlider,
              nearClipSlider;
    ofxGuiGroup aspectRatioGroup, projectionGroup;
    ofxToggle squareToggle, wideToggle, ulraWideToggle, perspectiveToggle, orthoToggle;


    //Right-Side pane callers
	void openFileBtnCallback();
    void openFilePrintscreenCallback();
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
    std::function<void(std::string)> printScreenSelectionCallback;
    std::function<void(std::string)> printScreenTakenCallback;
	std::function<void(std::string)> objFileImportedCallback;
    std::function<void(std::string)> createTriangleCallback;
    std::function<void(std::string)> createRectangleCallback;
    std::function<void(std::string)> createEllipseCallback;
    std::function<void(std::string)> associateShapesCallback;
    std::function<void(std::string)> dissociateShapesCallback;
    std::function<void(GUI::ActionType)> modeChangedCallback;
    std::function<void()> bSplineCreateCallback;
    std::function<void()> cRomCreateCallback;
	
    std::function<void(GUI::CameraSelected)> cameraChangedCallback;
    std::function<void(float val)> VFOVChangedCallback;
    std::function<void(float val)> HFOVChangedCallback;
    std::function<void(int val)> FarClipChangedCallback;
    std::function<void(int val)> NearClipChangedCallback;
    std::function<void(GUI::AspectRatio)> aspectRatioChangedCallback;
    std::function<void(GUI::ProjectionType)> projectionChangedCallback;

};

#endif // GUI_H
