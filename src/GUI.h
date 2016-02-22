#ifndef GUI_H
#define GUI_H

#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "gtk/gtk.h"
#include <fstream>
#include <iterator>
#include <algorithm>

class GUI
{
public:
    GUI();
    void Draw();
    void AddImageOpenedListener(void (inCallBackFunction)(string));
private:
    ofxButton openFileBtn;
    ofxPanel gui;
    void openFileBtnCallback();
    ofFileDialogResult requestUsrFile();
    void saveFile(string path, std::ifstream & file);
    void (*callBackFunction)(string);
};

#endif // GUI_H
