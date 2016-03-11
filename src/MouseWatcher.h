#ifndef MOUSEWATCHER_H
#define MOUSEWATCHER_H
#include "ofMain.h"
#include "../DelegatesLib/FastDelegate.h"
#include <ctime>
#include <vector>

using namespace fastdelegate;
class MouseWatcher
{
public:
    enum MouseActions{Drag, Down, Up};

    typedef FastDelegate2<int, int> MouseActionDelegate;

    MouseWatcher();
    void Record(int x, int y, MouseActions action);
    void StopRecording();
    void PauseRecording();
    void ResumeRecording();
    void Draw();
    void ShouldShowSelectionZone(bool shouldShow);
    void AddMouseDownDelegate(MouseActionDelegate  delegate);
    void RemoveMouseDownDelegate(MouseActionDelegate  delegate);
    void AddMouseUpDelegate(MouseActionDelegate  delegate);
    void RemoveMouseUpDelegate(MouseActionDelegate  delegate);
    void AddMouseClickDelegate(MouseActionDelegate  delegate);
    void RemoveMouseClickDelegate(MouseActionDelegate  delegate);
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
        selectionBarsSize = 5,
        clickClocksThreshold = 1500;

    clock_t downClickTime;
    
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

    std::vector<MouseActionDelegate > mouseDownDelegates;
    std::vector<MouseActionDelegate > mouseUpDelegates;
    std::vector<MouseActionDelegate > mouseClickDelegates;

    void fireMouseDown(int x, int y);
    void fireMouseUp(int x, int y);
    void fireMouseClick(int x, int y);
};

#endif // MOUSEWATCHER_H
