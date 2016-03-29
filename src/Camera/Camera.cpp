#include "Camera.h"

Camera::Camera()
{

}

void Camera::begin(const ofRectangle & viewportBounds){
    viewport = viewportBounds;
    if(viewport == ofRectangle()){
        viewport.set(0, 0, ofGetWidth(), ofGetHeight());
    }
    innerCamera.begin(viewport);
}

void Camera::end(){
    innerCamera.end();
}

void Camera::setTarget(const ofVec3f &target){
    innerTarget.setPosition(target);
    innerCamera.lookAt(innerTarget);
}

void Camera::setDistance(float distance){
    innerCamera.setPosition(innerTarget.getPosition() + (distance * innerCamera.getZAxis()));
    innerCamera.truck(xOffset);
    innerCamera.boom(yOffset);
}

void Camera::setPosition(float x, float y, float z){
    innerCamera.setPosition(x, y, z);
}

void Camera::zoomIn(int zoomVal){
    setDistance(getDistance() - zoomVal);
}

void Camera::zoomOut(int zoomVal){
    setDistance(getDistance() + zoomVal);
}

void Camera::setNearClip(float clipD){
    innerCamera.setNearClip(clipD);
}

void Camera::setFarClip(float clipD){
    innerCamera.setFarClip(clipD);
}

void Camera::setAspectRatio(float ratio){
    float finalHeight = ofGetWidth() / ratio;
    innerCamera.setAspectRatio(ratio);
    viewport.width = ofGetWidth();
    viewport.y = (ofGetHeight() - finalHeight) / 2;
    viewport.height = finalHeight;
}

void Camera::setViewport(const ofRectangle & newVP){
    viewport = newVP;
}

float Camera::getDistance() const{
    return innerTarget.getPosition().distance(innerCamera.getPosition());
}

float Camera::getNearClip() const{
    return innerCamera.getNearClip();
}

float Camera::getFarClip() const{
    return innerCamera.getFarClip();
}

ofQuaternion Camera::getOrientationQuat() const{
    return innerCamera.getOrientationQuat();
}

ofRectangle Camera::getCurrentViewport() const{
    return viewport;
}

void Camera::notifyMousePressed(int x, int y, int button){
    lastMousePos.set(x, y);
}

void Camera::notifyMouseDragged(int x, int y, int button, float speed){
    mouseDelta.set(x - lastMousePos.x, y - lastMousePos.y);
    lastMousePos.set(x, y);
    if(button == OF_MOUSE_BUTTON_3){
        rotate(speed);
    }else if(button == OF_MOUSE_BUTTON_1){
        move();
    }
}
void Camera::notifyMouseReleased(int x, int y, int button){
    mouseDelta.set(x - lastMousePos.x, y - lastMousePos.y);
    lastMousePos.set(x, y);
}

void Camera::rotate(float speed){
    ofQuaternion * rotQ = new ofQuaternion(-mouseDelta.y * 180 / viewport.height, innerCamera.getXAxis(), -mouseDelta.x * 180 / viewport.height, innerCamera.getYAxis(), 0, innerCamera.getZAxis());
    ofVec3f *appliedRot = new ofVec3f(innerCamera.getGlobalPosition() - innerTarget.getGlobalPosition());

    (*appliedRot) = (*appliedRot) * (*rotQ);
    innerCamera.setPosition((*appliedRot) + innerTarget.getGlobalPosition());
    innerCamera.setOrientation(innerCamera.getOrientationQuat() * (*rotQ));
    delete appliedRot;
    delete rotQ;
}

void Camera::move(){
    xOffset -= mouseDelta.x;
    yOffset += mouseDelta.y;
    innerCamera.truck(-mouseDelta.x);
    innerCamera.boom(mouseDelta.y);
}
