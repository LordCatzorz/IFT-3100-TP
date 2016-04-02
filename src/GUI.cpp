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
    drawTriangle.addListener(this, &GUI::createTriangleCaller);
    drawRectangle.addListener(this, &GUI::createRectangleCaller);
    drawEllipse.addListener(this, &GUI::createEllipseCaller);
    associateShapes.addListener(this, &GUI::associateShapesCaller);
    dissociateShapes.addListener(this, &GUI::dissociateShapesCaller);

    frontToggle.addListener(this, &GUI::frontCameraCaller);
    backToggle.addListener(this, &GUI::backCameraCaller);
    fovVSlider.addListener(this, &GUI::VFOVCaller);
    fovHSlider.addListener(this, &GUI::HFOVCaller);
    farClipSlider.addListener(this, &GUI::FarClipCaller);
    nearClipSlider.addListener(this, &GUI::NearClipCaller);

    gui.setup("Outils");
    cameraGui.setPosition(10, 10);
    gui.add(openFileBtn.setup("Ouvir une image"));
    gui.add(printscreenSection.setup("Capturer une zone"));
    gui.add(printscreen.setup("Capturer l'ecran"));
    //gui.add(selectionToggle.setup("Séléction", true));
    //gui.add(editToggle.setup("Éditer", false));
	gui.add(importObjFile.setup("Importer un OBJ"));
    gui.add(associateShapes.setup("Associer les formes"));
    gui.add(dissociateShapes.setup("Separer les enfants"));
    gui.add(drawTriangle.setup("Creer un triangle"));
    gui.add(drawRectangle.setup("Creer un rectangle"));
    gui.add(drawEllipse.setup("Creer un ellipse"));
    gui.add(color.setup("Couleur", ofColor(100, 100, 140), ofColor(0, 0), ofColor(255, 255)));

    editToggle = false;

    xPos = gui.getPosition().x;
    yPos = gui.getPosition().y;

    cameraGui.setup("Camera");

    cameraGui.add(cameraPickerGroup.setup("Aspect ratio"));
    cameraPickerGroup.add(frontToggle.setup("Camera avant", true));
    cameraPickerGroup.add(backToggle.setup("Camera arrière", false));
    frontToggle.setName("Camera avant");
    backToggle.setName("Camera arrière");

    cameraGui.setPosition(ofGetWidth() - cameraGui.getWidth() - 10, 10);
    cameraGui.add(fovVSlider.setup("FOV Verticale", 0, 0, 1032));
    cameraGui.add(fovHSlider.setup("FOV Horizontale", 0, 0, 1032));
    cameraGui.add(farClipSlider.setup("Far clip", 1032, 0, 1032));
    cameraGui.add(nearClipSlider.setup("Near clip", 0, 0, 1032));

    cameraGui.add(aspectRatioGroup.setup("Aspect ratio"));
    aspectRatioGroup.add(Square.setup("Caree"));
    Square.setName("Caree");
    aspectRatioGroup.add(Wide.setup("Large"));
    Wide.setName("Large");
    aspectRatioGroup.add(UlraWide.setup("Tres large"));
    UlraWide.setName("Tres large");
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

void GUI::AddCreateTriangleListener(std::function<void(std::string)> fnc)
{
    createTriangleCallback = fnc;
}

void GUI::AddCreateRectangleListener(std::function<void(std::string)> fnc)
{
    createRectangleCallback = fnc;
}

void GUI::AddCreateEllipseListener(std::function<void(std::string)> fnc)
{
    createEllipseCallback = fnc;
}

void GUI::AddAssociateShapesListener(std::function<void(std::string)> fnc)
{
    associateShapesCallback = fnc;
}

void GUI::AddDissociateShapesListener(std::function<void(std::string)> fnc)
{
    dissociateShapesCallback = fnc;
}

void GUI::AddCameraChangedListener(std::function<void(GUI::CameraSelected)> fnc)
{
    cameraChangedCallback = fnc;
}

void GUI::AddVFOVChangedListener(std::function<void(int)> fnc)
{
    VFOVChangedCallback = fnc;
}

void GUI::AddHFOVChangedListener(std::function<void(int)> fnc)
{
    HFOVChangedCallback = fnc;
}

void GUI::AddFarClipChangedListener(std::function<void(int)> fnc)
{
    FarClipChangedCallback = fnc;
}

void GUI::AddNearClipChangedListener(std::function<void(int)> fnc)
{
    NearClipChangedCallback = fnc;
}

string GUI::RequestSaveFilePath(string defaultName)
{
	ofFileDialogResult result = saveUsrFile("captureDEcran");
	return result.getPath();
}

void GUI::Draw(){
    ofDisableDepthTest();
    gui.draw();
    cameraGui.draw();
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

void GUI::SetCurrentMode(ActionType newMode)
{
    editToggle = newMode == GUI::Edit;
    selectionToggle = newMode == GUI::Select;
}

GUI::ActionType GUI::GetCurrentMode()
{
    if(selectionToggle == true){
        return GUI::Select;
    }else{
        return GUI::Edit;
    }
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

void GUI::createTriangleCaller(){
    createTriangleCallback("");
}

void GUI::createRectangleCaller(){
    createRectangleCallback("");
}

void GUI::createEllipseCaller(){
    createEllipseCallback("");
}

void GUI::associateShapesCaller(){
    associateShapesCallback("");
}

void GUI::dissociateShapesCaller(){
    dissociateShapesCallback("");
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


void GUI::frontCameraCaller(bool & inval)
{
    backToggle = !inval;
    cameraChangedCallback(inval ? GUI::CameraSelected::Front : GUI::CameraSelected::Back);
}

void GUI::backCameraCaller(bool & inval)
{
    frontToggle = !inval;
    cameraChangedCallback(inval ? GUI::CameraSelected::Back : GUI::CameraSelected::Front);
}

void GUI::VFOVCaller(int & val)
{
    VFOVChangedCallback(val);
}

void GUI::HFOVCaller(int & val)
{
    HFOVChangedCallback(val);
}

void GUI::FarClipCaller(int & val)
{
    FarClipChangedCallback(val);
}

void GUI::NearClipCaller(int & val)
{
    NearClipChangedCallback(val);
}
