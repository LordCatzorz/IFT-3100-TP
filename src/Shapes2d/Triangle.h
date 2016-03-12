#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "Shapes2d.h"

class Triangle: public Shapes2d
{
public:
    Triangle(int x1, int y1, int x2, int y2, int x3, int y3);
    /*bool        IsPointWithinBounds(int x, int y);
    bool        DoesRectangleOverlap(int x1, int y1, int x2, int y2);
    void        AffectVector(int x, int y, ofVec3f * actionVector, bool isRotation = false);
    void        Draw();*/
private:
    ofPoint     point1,
                point2,
                point3;
};

#endif // TRIANGLE_H
