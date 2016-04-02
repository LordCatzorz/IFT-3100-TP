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
    GUI();
    void Draw();
    void Show();
    void Hide();
    void SetCurrentMode(ActionType newMode);
    ActionType GetCurrentMode();
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
    void AddCameraChangedListener(std::function<void(GUI::CameraSelected)> fnc);
    void AddVFOVChangedListener(std::function<void(int)> fnc);
    void AddHFOVChangedListener(std::function<void(int)> fnc);
    void AddFarClipChangedListener(std::function<void(int)> fnc);
    void AddNearClipChangedListener(std::function<void(int)> fnc);
    ofColor * GetCurrentColor(){
        outputColor = color;
        return &(outputColor);}
    string RequestSaveFilePath(string defaultName);
private:

    int xPos, yPos;

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

    ofxPanel cameraGui;
    ofxGuiGroup cameraPickerGroup;
    ofxToggle frontToggle, backToggle;
    ofxIntSlider fovVSlider,
              fovHSlider,
              farClipSlider,
              nearClipSlider;
    ofxGuiGroup aspectRatioGroup;
    ofxToggle Square, Wide, UlraWide;


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

    //Left-side pane callers
    void frontCameraCaller(bool & inval);
    void backCameraCaller(bool & inval);
    void VFOVCaller(int & val);
    void HFOVCaller(int & val);
    void FarClipCaller(int & val);
    void NearClipCaller(int & val);


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
	
    std::function<void(GUI::CameraSelected)> cameraChangedCallback;
    std::function<void(int val)> VFOVChangedCallback;
    std::function<void(int val)> HFOVChangedCallback;
    std::function<void(int val)> FarClipChangedCallback;
    std::function<void(int val)> NearClipChangedCallback;

};

#endif // GUI_H
