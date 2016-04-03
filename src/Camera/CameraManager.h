#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H
#include "Camera.h"
#include <math.h>


class CameraManager
{
public:
    enum DisplayCamera{front, back};
    enum aspectRatio{square,//4:3
                     wide,//16:9
                     ultraWide};//21:9
    CameraManager();
    void setup();
    void begin();
    void end();
    void enableOrtho();
    void disableOrtho();
    void setTarget(const ofVec3f& target);
    void setDistance(float distance);
    void setPosition(float x, float y, float z);
    void zoomIn(int zoomVal = 30);
    void zoomOut(int zoomVal = 10);
    void setVFOV(float fovVal);
    void setHFOV(float fovVal);
    void setFarClip(float clipD);
    void setNearClip(float clipD);
    void setAspectRatio(const aspectRatio & ratio);
    float getDistance() const;
    float getNearClip() const;
    float getFarClip() const;
    float getVFOV() const;
    float getHFOV() const;

    void notifyMousePressed(int x, int y, int button);
    void notifyMouseDragged(int x, int y, int button);
    void notifyMouseReleased(int x, int y, int button);
    //void roll(int deg){innerVal2 += deg;frontCamera.roll(deg); backCamera.roll(deg); ofLog() << innerVal2;}
    void switchCam(const DisplayCamera & cameraToShow);

private:
    Camera frontCamera, backCamera;
    Camera * selectedCam;
    Camera * standByCam;
    DisplayCamera selectedCamEnum;
    ofRectangle secondaryViewport = ofRectangle();//0, 10, 2048, 256);
    void translateCoordinates(const ofRectangle & sourceViewport, int sourceX, int sourceY, const ofRectangle & destiantionViewport, int * destX, int * destY);
    void affectCameras(int x, int y, int button);
};

#endif // CAMERAMANAGER_H
