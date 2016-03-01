#include "MouseWatcher.h"

MouseWatcher::MouseWatcher()
{
}

void MouseWatcher::Record(int x, int y){
    if(isPaused)
        return;

    if(!isRecording){
        isRecording = true;
        coordX1 = x;
        coordY1 = y;

        lastRecordedPoint.x = 0;
        lastRecordedPoint.y = 0;
    }else{
        coordX2 = x;
        coordY2 = y;
    }

    currectVector.x = x - lastRecordedPoint.x;
    currectVector.y = y - lastRecordedPoint.y;

    lastRecordedPoint.x = x;
    lastRecordedPoint.y = y;
}

void MouseWatcher::StopRecording(){
    isRecording = false;
}

void MouseWatcher::PauseRecording(){
    isPaused = true;
}

void MouseWatcher::ResumeRecording(){
    isPaused = false;
}

ofVec3f * MouseWatcher::CurretVector(){
    return &currectVector;
}

ofPoint * MouseWatcher::TopLeftPoint(){

    topLeftPoint.set(coordX1 <= coordX2 ? coordX1 : coordX2, coordY1 <= coordY2 ? coordY1 : coordY2);

    return &topLeftPoint;
}

ofPoint * MouseWatcher::TopRightPoint(){

    topRightPoint.set(coordX1 <= coordX2 ? coordX2 : coordX1, coordY1 <= coordY2 ? coordY1 : coordY2);

    return &topRightPoint;
}

ofPoint * MouseWatcher::BottomLeftPoint(){

    bottomLeftPoint.set(coordX1 <= coordX2 ? coordX1 : coordX2, coordY1 <= coordY2 ? coordY2 : coordY1);

    return &bottomLeftPoint;
}

ofPoint * MouseWatcher::BottomRightPoint(){

    bottomRightPoint.set(coordX1 <= coordX2 ? coordX2 : coordX1, coordY1 <= coordY2 ? coordY2 : coordY1);

    return &bottomRightPoint;
}
