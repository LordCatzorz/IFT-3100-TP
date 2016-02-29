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
    }else{
        coordX2 = x;
        coordY2 = y;
    }
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
