#include "GUI.h"

GUI::GUI()
{
    openFileBtn.addListener(this, &GUI::openFileBtnCallback);
    printscreenSection.addListener(this, &GUI::callScreenSectionCallback);
    printscreen.addListener(this, &GUI::openFilePrintscreenCallback);
    gui.setup();
    gui.add(openFileBtn.setup("Ouvir une image"));
    gui.add(printscreenSection.setup("Capturer une zone de l'écran"));
    gui.add(printscreen.setup("Capturer l'écran"));
    xPos = gui.getPosition().x;
    yPos = gui.getPosition().y;
}

void GUI::AddImageOpenedListener(std::function<void(std::string)> fnc){

    imageOpenCallback = fnc;
}

void GUI::AddPrintscreenSelectionListener(std::function<void(std::string)> fnc){

    printScreenSelectionCallback = fnc;
}

void GUI::AddPrintscreenTakenListener(std::function<void(std::string)> fnc){

    printScreenTakenCallback = fnc;
}

string GUI::RequestSaveFilePath(string defaultName){
    ofFileDialogResult result = saveUsrFile("captureDEcran");
    return result.getPath();
}

void GUI::Draw(){
    gui.draw();
}

void GUI::Show(){
    gui.setPosition(xPos, yPos);
}

void GUI::Hide(){
    xPos = gui.getPosition().x;
    yPos = gui.getPosition().y;

    gui.setPosition(-1000, -1000);
}

void GUI::openFileBtnCallback(){
    ofFileDialogResult result = requestUsrFile();
    if(result.bSuccess)
        imageOpenCallback(result.filePath);
}

void GUI::openFilePrintscreenCallback(){

    ofFileDialogResult result = saveUsrFile("captureDEcran");

    printScreenTakenCallback(result.filePath);
}

void GUI::callScreenSectionCallback(){

    printScreenSelectionCallback("");
}

ofFileDialogResult GUI::requestUsrFile(){
    ofFileDialogResult result = ofSystemLoadDialog("Open File");
    return result;
}

ofFileDialogResult GUI::saveUsrFile(string defaultName){
    ofFileDialogResult result = ofSystemSaveDialog(defaultName, "Choisisez où savegarder votre capture d'écran");
    return result;
}
