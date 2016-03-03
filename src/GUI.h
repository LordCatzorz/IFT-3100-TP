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
    GUI();
    void Draw();
    void Show();
    void Hide();
    void AddImageOpenedListener(std::function<void(std::string)> fnc);
    void AddPrintscreenSelectionListener(std::function<void(std::string)> fnc);
    void AddPrintscreenTakenListener(std::function<void(std::string)> fnc);
    string RequestSaveFilePath(string defaultName);
private:

    int xPos, yPos;

	ofxButton openFileBtn;
    ofxButton printscreenSection;
    ofxButton printscreen;
	ofxPanel gui;
	void openFileBtnCallback();
    void openFilePrintscreenCallback();
    void callScreenSectionCallback();
    ofFileDialogResult requestUsrFile();
    ofFileDialogResult saveUsrFile(string defaultName);
    std::function<void(std::string)> imageOpenCallback;
    std::function<void(std::string)> printScreenSelectionCallback;
    std::function<void(std::string)> printScreenTakenCallback;
};

#endif // GUI_H
