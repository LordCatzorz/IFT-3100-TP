#ifndef MOUSEWATCHER_H
#define MOUSEWATCHER_H
#include "ofMain.h"

class MouseWatcher
{
public:
    MouseWatcher();
    void Record(int x, int y);
    void StopRecording();
    void PauseRecording();
    void ResumeRecording();
    ofPoint * TopLeftPoint();
    ofPoint * TopRightPoint();
    ofPoint * BottomLeftPoint();
    ofPoint * BottomRightPoint();
private:
    bool isRecording = false;
    bool isPaused = false;

    int coordX1 = -1;
    int coordY1 = -1;
    int coordX2 = -1;
    int coordY2 = -1;

    ofPoint topLeftPoint;
    ofPoint topRightPoint;
    ofPoint bottomLeftPoint;
    ofPoint bottomRightPoint;
};

#endif // MOUSEWATCHER_H
