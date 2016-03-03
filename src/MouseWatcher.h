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
    void Draw();
    void ShouldShowSelectionZone(bool shouldShow);
    ofVec3f * CurretVector();
    ofPoint * TopLeftPoint();
    ofPoint * TopRightPoint();
    ofPoint * BottomLeftPoint();
    ofPoint * BottomRightPoint();
private:
    bool    isRecording = false,
            isPaused = false,
            shouldDrawSelectionZone = false;

    int coordX1 = 0,
        coordY1 = 0,
        coordX2 = 0,
        coordY2 = 0,
        selectionBarsSize = 5;

    ofRectangle selectionZoneTHBar,
                selectionZoneBHBar,
                selectionZoneLVBar,
                selectionZoneRVBar;

    ofPoint lastRecordedPoint;
    ofVec3f currectVector;
    ofPoint topLeftPoint;
    ofPoint topRightPoint;
    ofPoint bottomLeftPoint;
    ofPoint bottomRightPoint;
};

#endif // MOUSEWATCHER_H
