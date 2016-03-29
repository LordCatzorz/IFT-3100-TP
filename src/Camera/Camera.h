#ifndef CAMERA_H
#define CAMERA_H
#pragma once
#include "ofMain.h"

class Camera
{
public:

    Camera();
    void begin(const ofRectangle & viewportBounds = ofRectangle());
    void end();
    void setTarget(const ofVec3f& target);
    void setDistance(float distance);
    void setPosition(float x, float y, float z);
    void zoomIn(int zoomVal = 30);
    void zoomOut(int zoomVal = 10);
    void setNearClip(float clipD);
    void setFarClip(float clipD);
    void setAspectRatio(float ratio);
    void setViewport(const ofRectangle & newVP);
    float getDistance() const;
    float getNearClip() const;
    float getFarClip() const;
    ofQuaternion getOrientationQuat() const;
    ofRectangle getCurrentViewport() const;
    void notifyMousePressed(int x, int y, int button);
    void notifyMouseDragged(int x, int y, int button, float speed = 1.f);
    void notifyMouseReleased(int x, int y, int button);

    bool isRotated = false;
    void setXPreRotation(int val){rotate(val);}
    void roll(int val){innerCamera.roll(val);}


private:
    ofCamera innerCamera;
    ofNode innerTarget;
    ofVec2f lastMousePos;
    ofVec2f mouseDelta;
    ofRectangle viewport;
    float xOffset = 0, yOffset = 0;
    void rotate(float speed = 1.f);
    void move();
};

#endif // CAMERA_H
