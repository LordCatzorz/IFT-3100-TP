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
    GUI();
    void Draw();
    void Show();
    void Hide();
    void AddImageOpenedListener(std::function<void(std::string)> fnc);
    void AddPrintscreenSelectionListener(std::function<void(std::string)> fnc);
    void AddPrintscreenTakenListener(std::function<void(std::string)> fnc);
    void AddModeChangedListener(std::function<void(GUI::ActionType)> fnc);
	void AddObjFileImportedListener(std::function<void(std::string)> fnc);
    string RequestSaveFilePath(string defaultName);
private:

    int xPos, yPos;

	ofxButton openFileBtn;
    ofxButton printscreenSection;
    ofxButton printscreen;
	ofxButton importObjFile;
    ofxToggle selectionToggle, editToggle;
    ofxPanel gui;

	void openFileBtnCallback();
    void openFilePrintscreenCallback();
    void selectionToggleCallback(bool & inval);
    void editToggleCallback(bool & inval);
    void callScreenSectionCallback();
	void importObjFileCallBack();
    ofFileDialogResult requestUsrFile();
    ofFileDialogResult saveUsrFile(string defaultName);
    std::function<void(std::string)> imageOpenCallback;
    std::function<void(std::string)> printScreenSelectionCallback;
    std::function<void(std::string)> printScreenTakenCallback;
	std::function<void(std::string)> objFileImportedCallback;
    std::function<void(GUI::ActionType)> modeChangedCallback;
	
};

#endif // GUI_H
