#include "MouseWatcher.h"

MouseWatcher::MouseWatcher()
{
}

void MouseWatcher::Record(int x, int y, int button, MouseActions action){
    if(isPaused)
        return;

    if(action == MouseWatcher::Down){
        downClickTime = clock();
        fireMouseDown(x, y, button);
    }
    if(!isRecording){
        isRecording = true;
        coordX1 = coordX2 = x;
        coordY1 = coordY2 = y;

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

    if(action == MouseWatcher::Drag){
        fireMouseDrag(x, y, button);
    }
    if(action == MouseWatcher::Up){
        fireMouseUp(x, y, button);
        if(double(clock() - downClickTime) <= clickClocksThreshold)
            fireMouseClick(x, y, button);
        SetShowSelectionZone(shouldDrawSelectionZone);
    }
}

void MouseWatcher::StopRecording(int x, int y, int button){
    isRecording = false;
    //fireMouseUp(x, y, button);
}

void MouseWatcher::PauseRecording(){
    isPaused = true;
}

void MouseWatcher::ResumeRecording(){
    isPaused = false;
}

void MouseWatcher::Draw(){
    if(shouldDrawSelectionZone && (coordX1 != coordX2 || coordY1 != coordY2)){
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

void MouseWatcher::SetShowSelectionZone(bool shouldShow){
    shouldDrawSelectionZone = shouldShow;
    coordX1 = coordX2 = coordY1 = coordY2;
}

bool MouseWatcher::GetShowSelectionZone(){
    return shouldDrawSelectionZone;
}

bool MouseWatcher::isXInverted() const{
    return coordX2 < coordX1;
}

bool MouseWatcher::isYInverted() const{
    return coordY2 < coordY1;
}

void MouseWatcher::AddMouseDownDelegate(MouseActionDelegate * delegate){
    MouseActionDelegate d1 = *delegate;
    mouseDownDelegates.push_back(d1);
}

void MouseWatcher::RemoveMouseDownDelegate(MouseActionDelegate * delegate){
    if(isTriggeringDownEvents){
        bufferMouseDownDelegates.push_back(delegate);
    }else{
        for(std::vector<MouseActionDelegate >::iterator itr = mouseDownDelegates.begin(); itr != mouseDownDelegates.end(); itr++){
            if(*itr == *delegate){
                mouseDownDelegates.erase(itr);
                break;
            }
        }
    }
}

void MouseWatcher::AddMouseUpDelegate(MouseActionDelegate * delegate){
    mouseUpDelegates.push_back(*delegate);
}

void MouseWatcher::RemoveMouseUpDelegate(MouseActionDelegate * delegate){
    if(isTriggeringUpEvents){
        bufferMouseUpDelegates.push_back(delegate);
    }else{
        for(std::vector<MouseActionDelegate >::iterator itr = mouseUpDelegates.begin(); itr != mouseUpDelegates.end(); itr++){
            if(*itr == *delegate){
                mouseUpDelegates.erase(itr);
                break;
            }
        }
    }
}

void MouseWatcher::AddMouseClickDelegate(MouseActionDelegate * delegate){
    mouseClickDelegates.push_back(*delegate);
}

void MouseWatcher::RemoveMouseClickDelegate(MouseActionDelegate * delegate){
    if(isTriggeringClickEvents){
        bufferMouseClickDelegates.push_back(delegate);
    }else{
        for(std::vector<MouseActionDelegate >::iterator itr = mouseClickDelegates.begin(); itr != mouseClickDelegates.end(); itr++){
            if(*itr == *delegate){
                mouseClickDelegates.erase(itr);
                break;
            }
        }
    }
}

void MouseWatcher::AddMouseDragDelegate(MouseActionDelegate * delegate){
    mouseDragDelegates.push_back(*delegate);
}

void MouseWatcher::RemoveMouseDragDelegate(MouseActionDelegate * delegate){
    if(isTriggeringDragEvents){
        bufferMouseDragDelegates.push_back(delegate);
    }else{
        for(std::vector<MouseActionDelegate >::iterator itr = mouseDragDelegates.begin(); itr != mouseDragDelegates.end(); itr++){
            if(*itr == *delegate){
                mouseDragDelegates.erase(itr);
                break;
            }
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

void MouseWatcher::fireMouseDown(int x, int y, int button){
    isTriggeringDownEvents = true;
    for(std::vector<MouseActionDelegate >::iterator itr = mouseDownDelegates.begin(); itr != mouseDownDelegates.end(); itr++){
        (*itr)(x, y, button);
    }
    isTriggeringDownEvents = false;
    clearResidentDownDelegated();
}

void MouseWatcher::fireMouseUp(int x, int y, int button){
    isTriggeringUpEvents = true;
    for(std::vector<MouseActionDelegate >::iterator itr = mouseUpDelegates.begin(); itr != mouseUpDelegates.end(); itr++){
        (*itr)(x, y, button);
    }
    isTriggeringUpEvents = false;
    clearResidentUpDelegated();
}

void MouseWatcher::fireMouseClick(int x, int y, int button){
    isTriggeringClickEvents = true;
    for(std::vector<MouseActionDelegate >::iterator itr = mouseClickDelegates.begin(); itr != mouseClickDelegates.end(); itr++){
        (*itr)(x, y, button);
    }
    isTriggeringClickEvents = false;
    clearResidentClickDelegated();
}

void MouseWatcher::fireMouseDrag(int x, int y, int button){
    isTriggeringDragEvents = true;
    for(std::vector<MouseActionDelegate >::iterator itr = mouseDragDelegates.begin(); itr != mouseDragDelegates.end(); itr++){
        (*itr)(x, y, button);
    }
    isTriggeringDragEvents = false;
    clearResidentDragDelegated();
}

void MouseWatcher::clearResidentDownDelegated(){
    for(std::vector<MouseActionDelegate *>::iterator itr = bufferMouseDownDelegates.begin(); itr != bufferMouseDownDelegates.end(); itr++){
        for(std::vector<MouseActionDelegate >::iterator itr2 = mouseDownDelegates.begin(); itr2 != mouseDownDelegates.end(); itr2++){
            if(**itr == *itr2){
                mouseDownDelegates.erase(itr2);
                break;
            }
        }
    }
}
void MouseWatcher::clearResidentUpDelegated(){
    for(std::vector<MouseActionDelegate *>::iterator itr = bufferMouseUpDelegates.begin(); itr != bufferMouseUpDelegates.end(); itr++){
        for(std::vector<MouseActionDelegate >::iterator itr2 = mouseUpDelegates.begin(); itr2 != mouseUpDelegates.end(); itr2++){
            if(**itr == *itr2){
                mouseUpDelegates.erase(itr2);
                break;
            }
        }
    }
}
void MouseWatcher::clearResidentClickDelegated(){
    for(std::vector<MouseActionDelegate *>::iterator itr = bufferMouseClickDelegates.begin(); itr != bufferMouseClickDelegates.end(); itr++){
        for(std::vector<MouseActionDelegate >::iterator itr2 = mouseClickDelegates.begin(); itr2 != mouseClickDelegates.end(); itr2++){
            if(**itr == *itr2){
                mouseClickDelegates.erase(itr2);
                break;
            }
        }
    }
}
void MouseWatcher::clearResidentDragDelegated(){
    for(std::vector<MouseActionDelegate *>::iterator itr = bufferMouseDragDelegates.begin(); itr != bufferMouseDragDelegates.end(); itr++){
        for(std::vector<MouseActionDelegate >::iterator itr2 = mouseDragDelegates.begin(); itr2 != mouseDragDelegates.end(); itr2++){
            if(**itr == *itr2){
                mouseDragDelegates.erase(itr2);
                break;
            }
        }
    }
}
