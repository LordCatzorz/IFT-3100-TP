#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "Shapes2d.h"

class Triangle: public Shapes2d
{
public:
                Triangle();
    bool        IsPointWithinBounds(int x, int y);
    bool        DoesRectangleOverlap(int x1, int y1, int x2, int y2);
    void        AffectVector(int x, int y, ofVec3f * actionVector, bool isRotation = false);
    //void        Draw();
    void        Create(int x1, int y1, int width, int height);
private:
    ofPoint     point1,
                point2,
                point3;
    bool isPointInsideRectangle(int x, int y, const ofRectangle & rectangle);
    void refreshPoints();
    void drawShape();
};

#endif // TRIANGLE_H
