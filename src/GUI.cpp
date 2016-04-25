#include "GUI.h"

GUI::GUI()
{
    ofDisableDepthTest();
	openFileBtn.addListener(this, &GUI::openFileBtnCallback);
		openHeightMapBtn.addListener(this, &GUI::openHeightMapBtnCallback);
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
    bSplineCreate.addListener(this, &GUI::bSplineCreateCaller);
    CRomCreate.addListener(this, &GUI::cRomCreateCaller);
    controlPointsSlider.addListener(this, &GUI::controlPointsSliderCaller);
    surfaceCreate.addListener(this, &GUI::surfaceCreateCaller);
    surfaceSide1.addListener(this, &GUI::surfacePoints1SliderCaller);
    surfaceSide2.addListener(this, &GUI::surfacePoints2SliderCaller);
    surfaceSide3.addListener(this, &GUI::surfacePoints3SliderCaller);
    surfaceSide4.addListener(this, &GUI::surfacePoints4SliderCaller);

    frontToggle.addListener(this, &GUI::frontCameraCaller);
    backToggle.addListener(this, &GUI::backCameraCaller);
    fovVSlider.addListener(this, &GUI::VFOVCaller);
    fovHSlider.addListener(this, &GUI::HFOVCaller);
    farClipSlider.addListener(this, &GUI::FarClipCaller);
    nearClipSlider.addListener(this, &GUI::NearClipCaller);
    squareToggle.addListener(this, &GUI::squareCaller);
    wideToggle.addListener(this, &GUI::wideCaller);
    ulraWideToggle.addListener(this, &GUI::ultraWideCaller);
    perspectiveToggle.addListener(this, &GUI::perspectiveCaller);
    orthoToggle.addListener(this, &GUI::orthogonalCaller);

    gui.setup("Outils");
    gui.add(openFileBtn.setup("Ouvir une image"));
    gui.add(printscreenSection.setup("Capturer une zone"));
    gui.add(printscreen.setup("Capturer l'ecran"));
    gui.add(openHeightMapBtn.setup("Ouvrir une carte d'elevation"));
    gui.add(importObjFile.setup("Importer un OBJ"));

    gui.add(associateShapes.setup("Associer les formes"));
    gui.add(dissociateShapes.setup("Separer les enfants"));
    gui.add(drawTriangle.setup("Creer un triangle"));
    gui.add(drawRectangle.setup("Creer un rectangle"));
    gui.add(drawEllipse.setup("Creer un ellipse"));
    gui.add(color.setup("Couleur", ofColor(100, 100, 140), ofColor(0, 0), ofColor(255, 255)));
    gui.add(courbesGroup.setup("Courbes"));
    courbesGroup.add(bSplineCreate.setup("Creer B-Spline"));
    courbesGroup.add(CRomCreate.setup("Creer Catmull-Rom"));
    courbesGroup.add(controlPointsSlider.setup("Points de controle", 5, 1, 10));
    gui.add(surfaceCreate.setup("Creer une surface"));
    gui.add(surfaceGroup.setup("Parametres surface"));
    surfaceGroup.minimize();
    surfaceGroup.add(surfaceSide1.setup("Ondulations cote 1", 3, 0, 10));
    surfaceGroup.add(surfaceSide2.setup("Ondulations cote 2", 3, 0, 10));
    surfaceGroup.add(surfaceSide3.setup("Ondulations cote 3", 3, 0, 10));
    surfaceGroup.add(surfaceSide4.setup("Ondulations cote 4", 3, 0, 10));


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
    cameraGui.add(fovVSlider.setup("FOV Verticale", 0, 0, 180));
    cameraGui.add(fovHSlider.setup("FOV Horizontale", 0, 0, 180));
    cameraGui.add(farClipSlider.setup("Far clip", 1032, 0, 1032));
    cameraGui.add(nearClipSlider.setup("Near clip", 0, 0, 1032));

    cameraGui.add(aspectRatioGroup.setup("Aspect ratio"));
    aspectRatioGroup.add(squareToggle.setup("Caree", false));
    aspectRatioGroup.add(wideToggle.setup("Large", false));
    aspectRatioGroup.add(ulraWideToggle.setup("Tres large", false));
    squareToggle.setName("Caree");
    wideToggle.setName("Large");
    ulraWideToggle.setName("Tres large");
    squareToggle.setBackgroundColor(0);
    wideToggle.setBackgroundColor(160);
    ulraWideToggle.setBackgroundColor(160);

    cameraGui.add(projectionGroup.setup("Type de projection"));
    projectionGroup.add(perspectiveToggle.setup("Perspective", true));
    projectionGroup.add(orthoToggle.setup("Orthogonale", false));

    ofEnableDepthTest();
}

void GUI::AddImageOpenedListener(std::function<void(std::string)> fnc){

	imageOpenCallback = fnc;
}

void GUI::AddHeightMapListener(std::function<void(std::string)> fnc)
{

	heightMapOpenCallback = fnc;
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

void GUI::AddBSplineCreateListener(std::function<void()> fnc)
{
    bSplineCreateCallback = fnc;
}

void GUI::AddCRomCreateListener(std::function<void()> fnc)
{
    cRomCreateCallback = fnc;
}

void GUI::AddSurfaceCreateListener(std::function<void()> fnc)
{
    surfaceCreateCallback = fnc;
}

void GUI::AddCameraChangedListener(std::function<void(GUI::CameraSelected)> fnc)
{
    cameraChangedCallback = fnc;
}

void GUI::AddVFOVChangedListener(std::function<void(float)> fnc)
{
    VFOVChangedCallback = fnc;
}

void GUI::AddHFOVChangedListener(std::function<void(float)> fnc)
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

void GUI::AddAspectRatioChangedListener(std::function<void(AspectRatio)> fnc)
{
    aspectRatioChangedCallback = fnc;
}

void GUI::AddProjectionChangedListener(std::function<void(ProjectionType)> fnc)
{
    projectionChangedCallback = fnc;
}

void GUI::setVFOV(const float val){
    fovVSlider = val;
}

void GUI::setHFOV(const float val){
    fovHSlider = val;
}

string GUI::RequestSaveFilePath(string defaultName)
{
	ofFileDialogResult result = saveUsrFile("captureDEcran");
	return result.getPath();
}

void GUI::Draw(){
    ofDisableDepthTest();
    gui.draw();
    cameraGui.setPosition(ofGetWidth() - cameraGui.getWidth() - 10, 10);
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

int GUI::getCurveControlPoints() const{
    return curveControlPoints;
}

int GUI::getSurfaceControlCount1() const{
    return surfaceControlCount1;
}

int GUI::getSurfaceControlCount2() const{
    return surfaceControlCount2;
}

int GUI::getSurfaceControlCount3() const{
    return surfaceControlCount3;
}

int GUI::getSurfaceControlCount4() const{
    return surfaceControlCount4;
}

void GUI::openFileBtnCallback()
{
	ofFileDialogResult result = requestUsrFile();
	if (result.bSuccess)
	{
		imageOpenCallback(result.filePath);
	}
}

void GUI::openHeightMapBtnCallback()
{
	ofFileDialogResult result = requestUsrFile();
	if (result.bSuccess)
	{
		heightMapOpenCallback(result.filePath);
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

void GUI::bSplineCreateCaller(){
    bSplineCreateCallback();
}

void GUI::cRomCreateCaller(){
    cRomCreateCallback();
}

void GUI::surfaceCreateCaller(){
    surfaceCreateCallback();
}

void GUI::controlPointsSliderCaller(int &val){
    curveControlPoints = val;
}

void GUI::surfacePoints1SliderCaller(int &val){
    surfaceControlCount1 = val;
}

void GUI::surfacePoints2SliderCaller(int &val){
    surfaceControlCount2 = val;
}

void GUI::surfacePoints3SliderCaller(int &val){
    surfaceControlCount3 = val;
}

void GUI::surfacePoints4SliderCaller(int &val){
    surfaceControlCount4 = val;
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

void GUI::VFOVCaller(float & val)
{
    VFOVChangedCallback(val);
}

void GUI::HFOVCaller(float & val)
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

void GUI::squareCaller(bool & inval)
{
    squareToggle = false;
    wideToggle = false;
    ulraWideToggle = false;

    squareToggle.setBackgroundColor(0);
    wideToggle.setBackgroundColor(160);
    ulraWideToggle.setBackgroundColor(160);
    aspectRatioChangedCallback(AspectRatio::Square);
}

void GUI::wideCaller(bool & inval)
{
    wideToggle = false;
    squareToggle = false;
    ulraWideToggle = false;

    squareToggle.setBackgroundColor(160);
    wideToggle.setBackgroundColor(0);
    ulraWideToggle.setBackgroundColor(160);
    aspectRatioChangedCallback(AspectRatio::Wide);
}

void GUI::ultraWideCaller(bool & inval)
{
    ulraWideToggle = false;
    wideToggle = false;
    squareToggle = false;

    squareToggle.setBackgroundColor(160);
    wideToggle.setBackgroundColor(160);
    ulraWideToggle.setBackgroundColor(0);
    aspectRatioChangedCallback(AspectRatio::UltraWide);
}

void GUI::perspectiveCaller(bool & inval)
{
    orthoToggle = !inval;
    projectionChangedCallback(inval ? GUI::ProjectionType::Perspective : GUI::ProjectionType::Orthogonal);
}

void GUI::orthogonalCaller(bool & inval)
{
    perspectiveToggle = !inval;
    projectionChangedCallback(inval ? GUI::ProjectionType::Orthogonal : GUI::ProjectionType::Perspective);
}
