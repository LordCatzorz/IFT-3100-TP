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

    typedef FastDelegate3<int, int, int> MouseActionDelegate;

    MouseWatcher();
    void Record(int x, int y, int button, MouseActions action);
    void StopRecording(int x, int y, int button);
    void PauseRecording();
    void ResumeRecording();
    void Draw();
    void SetShowSelectionZone(bool shouldShow);
    bool GetShowSelectionZone();
    void AddMouseDownDelegate(MouseActionDelegate * delegate);
    void RemoveMouseDownDelegate(MouseActionDelegate * delegate);
    void AddMouseUpDelegate(MouseActionDelegate * delegate);
    void RemoveMouseUpDelegate(MouseActionDelegate * delegate);
    void AddMouseClickDelegate(MouseActionDelegate * delegate);
    void RemoveMouseClickDelegate(MouseActionDelegate * delegate);
    void AddMouseDragDelegate(MouseActionDelegate * delegate);
    void RemoveMouseDragDelegate(MouseActionDelegate * delegate);
    void AddMouseMoveDelegate(MouseActionDelegate * delegate);
    void RemoveMouseMoveDelegate(MouseActionDelegate * delegate);
    ofVec3f * CurretVector();
    ofPoint * TopLeftPoint();
    ofPoint * TopRightPoint();
    ofPoint * BottomLeftPoint();
    ofPoint * BottomRightPoint();
private:
    bool    isRecording = false,
            isPaused = false,
            shouldDrawSelectionZone = true,
            isTriggeringDownEvents = false,
            isTriggeringUpEvents = false,
            isTriggeringClickEvents = false,
            isTriggeringDragEvents = false;

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
    std::vector<MouseActionDelegate *> bufferMouseDownDelegates;
    std::vector<MouseActionDelegate > mouseUpDelegates;
    std::vector<MouseActionDelegate *> bufferMouseUpDelegates;
    std::vector<MouseActionDelegate > mouseClickDelegates;
    std::vector<MouseActionDelegate *> bufferMouseClickDelegates;
    std::vector<MouseActionDelegate > mouseDragDelegates;
    std::vector<MouseActionDelegate *> bufferMouseDragDelegates;

    void clearResidentDownDelegated();
    void clearResidentUpDelegated();
    void clearResidentClickDelegated();
    void clearResidentDragDelegated();

    void fireMouseDown(int x, int y, int button);
    void fireMouseUp(int x, int y, int button);
    void fireMouseClick(int x, int y, int button);
    void fireMouseDrag(int x, int y, int button);
};

#endif // MOUSEWATCHER_H
