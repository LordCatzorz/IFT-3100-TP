#ifndef SHAPE_H
#define SHAPE_H
#include "ofMain.h"

class Shape
{
public:
    virtual ofPoint *   TopLeftPoint() = 0;
    virtual ofPoint *   TopRightPoint() = 0;
    virtual ofPoint *   BottomLeftPoint() = 0;
    virtual ofPoint *   BottomRightPoint() = 0;
    virtual bool        IsPointWithinBounds(int x, int y) = 0;
    virtual bool        DoesRectangleOverlap(int x1, int y1, int x2, int y2) = 0;
    virtual void        AffectVector(int x, int y, ofVec3f * actionVector, bool isRotation = false) = 0;
    virtual void        ShowBorders(bool shouldShow) = 0;
    virtual void        Draw() = 0;
protected:
    static ofPoint * translatePoint(int x, int y, double angleInDegrees, ofPoint * translated){
        double angleRad = angleInDegrees * M_PI/180;
        double px = cos(angleRad) * x - sin(angleRad) * y;
        double py = sin(angleRad) * x + cos(angleRad) * y;

        translated->set(px, py);
    };
};

#endif // SHAPE_H
