#include "CameraManager.h"

CameraManager::CameraManager()
{
    selectedCam = &frontCamera;
    standByCam = &backCamera;
}

void CameraManager::setup(int offset){
    backCamera.setViewport(ofRectangle(0, 0, ofGetWidth(), ofGetHeight()));
    backCamera.notifyMouseDragged(772, 0, OF_MOUSE_BUTTON_3);
}

void CameraManager::begin(){
    selectedCam->begin();
}

void CameraManager::end(){
    selectedCam->end();
}

void CameraManager::enableOrtho(){
    frontCamera.enableOrtho();
    backCamera.enableOrtho();
}

void CameraManager::disableOrtho(){
    frontCamera.disableOrtho();
    backCamera.disableOrtho();
}

void CameraManager::setTarget(const ofVec3f& target){
    frontCamera.setTarget(target);
    backCamera.setTarget(target);
}

void CameraManager::setDistance(float distance){
    frontCamera.setDistance(distance);
    backCamera.setDistance(distance);
}

void CameraManager::setPosition(float x, float y, float z){
    frontCamera.setPosition(x, y, z);
    backCamera.setPosition(x, y, z);
}

void CameraManager::zoomIn(int zoomVal){
    frontCamera.zoomIn(zoomVal);
    backCamera.zoomIn(zoomVal);
}

void CameraManager::zoomOut(int zoomVal){
    frontCamera.zoomOut(zoomVal);
    backCamera.zoomOut(zoomVal);
}

void CameraManager::setVFOV(float fovVal){
    frontCamera.setVFOV(fovVal);
    backCamera.setVFOV(fovVal);
}

void CameraManager::setHFOV(float fovVal){
    frontCamera.setHFOV(fovVal);
    backCamera.setHFOV(fovVal);
}

void CameraManager::setNearClip(float clipD){
    frontCamera.setNearClip(clipD);
    backCamera.setNearClip(clipD);
}

void CameraManager::setFarClip(float clipD){
    frontCamera.setFarClip(clipD);
    backCamera.setFarClip(clipD);
}

void CameraManager::setAspectRatio(const aspectRatio & ratio){
    switch(ratio){
    case square:
        frontCamera.setAspectRatio(4.f/3.f);
        backCamera.setAspectRatio(4.f/3.f);
        break;
    case wide:
        frontCamera.setAspectRatio(16.f/9.f);
        backCamera.setAspectRatio(16.f/9.f);
        break;
    default:
        frontCamera.setAspectRatio(21.f/9.f);
        backCamera.setAspectRatio(21.f/9.f);
        break;
    }
}

float CameraManager::getDistance() const{
    return frontCamera.getDistance();
}

float CameraManager::getNearClip() const{
    return frontCamera.getNearClip();
}

float CameraManager::getFarClip() const{
    return frontCamera.getFarClip();
}

float CameraManager::getVFOV() const{
    return frontCamera.getVFOV();
}

float CameraManager::getHFOV() const{
    return frontCamera.getHFOV();
}

void CameraManager::notifyMousePressed(int x, int y, int button){
    selectedCam->notifyMousePressed(x, y, button);
    standByCam->notifyMousePressed(-x, -y, button);
}

void CameraManager::notifyMouseDragged(int x, int y, int button){
    selectedCam->notifyMouseDragged(x, y, button);
    standByCam->notifyMouseDragged(-x, -y, button);
}

void CameraManager::notifyMouseReleased(int x, int y, int button){
    selectedCam->notifyMouseReleased(x, y, button);
    standByCam->notifyMouseReleased(-x, -y, button);
}

void CameraManager::switchCam(const DisplayCamera & cameraToShow){
    switch (cameraToShow) {
    case back:
        selectedCam = &backCamera;
        standByCam = &frontCamera;
        break;
    default:
        selectedCam = &frontCamera;
        standByCam = &backCamera;
        break;
    }
}

void CameraManager::affectCameras(int x, int y, int button){

}

void CameraManager::translateCoordinates(const ofRectangle &sourceViewport, int sourceX, int sourceY, const ofRectangle &destiantionViewport, int *destX, int *destY){
    float xRatio = sourceX / (float)sourceViewport.width;
    float yRatio = sourceY / (float)sourceViewport.height;

    (*destX) = ceil(destiantionViewport.width * xRatio);
    (*destY) = ceil(destiantionViewport.height * yRatio);
}
