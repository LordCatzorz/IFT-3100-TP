#include "GUI.h"

GUI::GUI()
{
    openFileBtn.addListener(this, &GUI::openFileBtnCallback);
    gui.setup();
    gui.add(openFileBtn.setup("Ouvir une image"));
}

void GUI::AddImageOpenedListener(std::function<void(std::string)> fnc){

    imageOpenCallback = fnc;
}

void GUI::Draw(){
    gui.draw();
}

void GUI::openFileBtnCallback(){
    ofFileDialogResult result = requestUsrFile();

    imageOpenCallback(result.filePath);
}

/*
    ofImage * image = new ofImage();
    image->load("labo3.png");
    image->draw(10, 10, 300, 300);
    */

ofFileDialogResult GUI::requestUsrFile(){
    ofFileDialogResult result = ofSystemLoadDialog("Open File");
    return result;
}
