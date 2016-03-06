#ifndef SHAPE_H
#define SHAPE_H
#include "ofMain.h"

class Shape
{
public:
    virtual ofPoint * TopLeftPoint() = 0;
    virtual ofPoint * TopRightPoint() = 0;
    virtual ofPoint * BottomLeftPoint() = 0;
    virtual ofPoint * BottomRightPoint() = 0;
    virtual bool IsPointWithinBounds(int x, int y) = 0;
    virtual void AffectVector(int x, int y, ofVec3f * actionVector, bool isRotation = false) = 0;
    virtual void ShowBorders(bool shouldShow) = 0;
    virtual void Draw() = 0;
};

#endif // SHAPE_H
