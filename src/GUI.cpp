#include "GUI.h"

GUI::GUI()
{
    ofDisableDepthTest();
    openFileBtn.addListener(this, &GUI::openFileBtnCallback);
    printscreenSection.addListener(this, &GUI::callScreenSectionCallback);
    printscreen.addListener(this, &GUI::openFilePrintscreenCallback);
    selectionToggle.addListener(this, &GUI::selectionToggleCallback);
    editToggle.addListener(this, &GUI::editToggleCallback);
	importObjFile.addListener(this, &GUI::importObjFileCallBack);
    gui.setSize(200, 500);
    gui.setup();
    gui.add(openFileBtn.setup("Ouvir une image"));
    gui.add(printscreenSection.setup("Capturer une zone de l'écran"));
    gui.add(printscreen.setup("Capturer l'écran"));
    gui.add(selectionToggle.setup("Séléction", true));
    gui.add(editToggle.setup("Éditer", false));
	gui.add(importObjFile.setup("Importer un OBJ"));
    editToggle = false;

    xPos = gui.getPosition().x;
    yPos = gui.getPosition().y;
    ofEnableDepthTest();
}

void GUI::AddImageOpenedListener(std::function<void(std::string)> fnc){

	imageOpenCallback = fnc;
}

void GUI::AddPrintscreenSelectionListener(std::function<void(std::string)> fnc)
{

	printScreenSelectionCallback = fnc;
}

void GUI::AddPrintscreenTakenListener(std::function<void(std::string)> fnc)
{

	printScreenTakenCallback = fnc;
}

void GUI::AddModeChangedListener(std::function<void(GUI::ActionType)> fnc)
{

	modeChangedCallback = fnc;
}

void GUI::AddObjFileImportedListener(std::function<void(std::string)> fnc)
{
	objFileImportedCallback = fnc;
}

string GUI::RequestSaveFilePath(string defaultName)
{
	ofFileDialogResult result = saveUsrFile("captureDEcran");
	return result.getPath();
}

void GUI::Draw(){
    ofDisableDepthTest();
    gui.draw();
    ofEnableDepthTest();
}

void GUI::Show()
{
	gui.setPosition(xPos, yPos);
}

void GUI::Hide()
{
	xPos = gui.getPosition().x;
	yPos = gui.getPosition().y;

	gui.setPosition(-1000, -1000);
}

void GUI::openFileBtnCallback()
{
	ofFileDialogResult result = requestUsrFile();
	if (result.bSuccess)
	{
		imageOpenCallback(result.filePath);
	}
}

void GUI::openFilePrintscreenCallback()
{

	ofFileDialogResult result = saveUsrFile("captureDEcran");
	if (result.bSuccess)
	{
		printScreenTakenCallback(result.filePath);
	}
}

void GUI::callScreenSectionCallback()
{

	printScreenSelectionCallback("");
}

void GUI::importObjFileCallBack()
{
	ofFileDialogResult result = requestUsrFile();
	if (result.bSuccess)
	{
		objFileImportedCallback(result.filePath);
	}
}

void GUI::selectionToggleCallback(bool & inval)
{
	editToggle = !inval;
	modeChangedCallback(inval ? GUI::ActionType::Select : GUI::ActionType::Edit);
}

void GUI::editToggleCallback(bool & inval)
{
	selectionToggle = !inval;
	modeChangedCallback(inval ? GUI::ActionType::Edit : GUI::ActionType::Select);
	// else
	 //    editToggle = true;
}

ofFileDialogResult GUI::requestUsrFile()
{
	ofFileDialogResult result = ofSystemLoadDialog("Open File");
	return result;
}

ofFileDialogResult GUI::saveUsrFile(string defaultName)
{
	ofFileDialogResult result = ofSystemSaveDialog(defaultName, "Choisisez où savegarder votre capture d'écran");
	return result;
}
