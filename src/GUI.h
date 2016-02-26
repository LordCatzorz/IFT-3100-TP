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
    void AddImageOpenedListener(std::function<void(std::string)> fnc);
private:
	ofxButton openFileBtn;
	ofxPanel gui;
	void openFileBtnCallback();
    ofFileDialogResult requestUsrFile();
    std::function<void(std::string)> imageOpenCallback;
};

#endif // GUI_H
