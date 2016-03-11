#include "MouseWatcher.h"

MouseWatcher::MouseWatcher()
{
}

void MouseWatcher::Record(int x, int y, MouseActions action){
    if(isPaused)
        return;

    if(action == MouseWatcher::Down){
        downClickTime = clock();
        fireMouseDown(x, y);
    }
    if(action == MouseWatcher::Up){
        fireMouseUp(x, y);
        if(double(clock() - downClickTime) <= clickClocksThreshold)
            fireMouseClick(x, y);
    }
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
    fireMouseUp(coordX2, coordY2);
}

void MouseWatcher::PauseRecording(){
    isPaused = true;
}

void MouseWatcher::ResumeRecording(){
    isPaused = false;
}

void MouseWatcher::Draw(){
    if(shouldDrawSelectionZone){
        ofSetColor(ofColor::grey);

        selectionZoneTHBar.set(TopLeftPoint()->x, TopLeftPoint()->y, TopRightPoint()->x - TopLeftPoint()->x, selectionBarsSize);
        selectionZoneBHBar.set(TopLeftPoint()->x, BottomLeftPoint()->y - selectionBarsSize, TopRightPoint()->x - TopLeftPoint()->x, selectionBarsSize);
        selectionZoneLVBar.set(TopLeftPoint()->x, TopLeftPoint()->y, selectionBarsSize, BottomLeftPoint()->y - TopLeftPoint()->y);
        selectionZoneRVBar.set(TopRightPoint()->x - selectionBarsSize, TopRightPoint()->y, selectionBarsSize, BottomRightPoint()->y - TopRightPoint()->y);

        ofRect(selectionZoneTHBar);
        ofRect(selectionZoneBHBar);
        ofRect(selectionZoneLVBar);
        ofRect(selectionZoneRVBar);
    }
}

void MouseWatcher::ShouldShowSelectionZone(bool shouldShow){
    shouldDrawSelectionZone = shouldShow;
}

void MouseWatcher::AddMouseDownDelegate(MouseActionDelegate  delegate){
    mouseDownDelegates.push_back(delegate);
}

void MouseWatcher::RemoveMouseDownDelegate(MouseActionDelegate  delegate){
    for(std::vector<MouseActionDelegate >::iterator itr = mouseDownDelegates.begin(); itr != mouseDownDelegates.end(); itr++){
        if(*itr == delegate){
            mouseDownDelegates.erase(itr);
            break;
        }
    }
}

void MouseWatcher::AddMouseUpDelegate(MouseActionDelegate  delegate){
    mouseUpDelegates.push_back(delegate);
}

void MouseWatcher::RemoveMouseUpDelegate(MouseActionDelegate  delegate){
    for(std::vector<MouseActionDelegate >::iterator itr = mouseUpDelegates.begin(); itr != mouseUpDelegates.end(); itr++){
        if(*itr == delegate){
            mouseUpDelegates.erase(itr);
            break;
        }
    }
}

void MouseWatcher::AddMouseClickDelegate(MouseActionDelegate  delegate){
    mouseClickDelegates.push_back(delegate);
}

void MouseWatcher::RemoveMouseClickDelegate(MouseActionDelegate  delegate){
    for(std::vector<MouseActionDelegate >::iterator itr = mouseClickDelegates.begin(); itr != mouseClickDelegates.end(); itr++){
        if(*itr == delegate){
            mouseClickDelegates.erase(itr);
            break;
        }
    }
}

ofVec3f * MouseWatcher::CurretVector(){
    return &currectVector;
}

ofPoint * MouseWatcher::TopLeftPoint(){

    topLeftPoint.set((coordX1 <= coordX2 ? coordX1 : coordX2) + (shouldDrawSelectionZone ? selectionBarsSize : 0), (coordY1 <= coordY2 ? coordY1 : coordY2) + (shouldDrawSelectionZone ? selectionBarsSize : 0));

    return &topLeftPoint;
}

ofPoint * MouseWatcher::TopRightPoint(){

    topRightPoint.set(coordX1 <= coordX2 ? coordX2 : coordX1, (coordY1 <= coordY2 ? coordY1 : coordY2) + (shouldDrawSelectionZone ? selectionBarsSize : 0));

    return &topRightPoint;
}

ofPoint * MouseWatcher::BottomLeftPoint(){

    bottomLeftPoint.set((coordX1 <= coordX2 ? coordX1 : coordX2) + (shouldDrawSelectionZone ? selectionBarsSize : 0), coordY1 <= coordY2 ? coordY2 : coordY1);

    return &bottomLeftPoint;
}

ofPoint * MouseWatcher::BottomRightPoint(){

    bottomRightPoint.set(coordX1 <= coordX2 ? coordX2 : coordX1, coordY1 <= coordY2 ? coordY2 : coordY1);

    return &bottomRightPoint;
}

void MouseWatcher::fireMouseDown(int x, int y){
    for(std::vector<MouseActionDelegate >::iterator itr = mouseDownDelegates.begin(); itr != mouseDownDelegates.end(); itr++){
        (*itr)(x, y);
    }
}

void MouseWatcher::fireMouseUp(int x, int y){
    for(std::vector<MouseActionDelegate >::iterator itr = mouseUpDelegates.begin(); itr != mouseUpDelegates.end(); itr++){
        (*itr)(x, y);
    }
}

void MouseWatcher::fireMouseClick(int x, int y){
    for(std::vector<MouseActionDelegate >::iterator itr = mouseClickDelegates.begin(); itr != mouseClickDelegates.end(); itr++){
        (*itr)(x, y);
    }
}
