#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "../Shape2D.h"

    class Rectangle2D : public Shape2D
    {
    public:
                    Rectangle2D();
        //bool        IsPointWithinBounds(float x, float y);
        bool        DoesRectangleOverlap(int x1, int y1, int x2, int y2);
        //void        AffectVector(int x, int y, ofVec3f * actionVector, bool isRotation = false);
        //void        Draw();
        void        Create(int x1, int y1, int width, int height);
    protected:
        ofPoint     point1,
                    point2,
                    point3,
                    point4;
        //bool isPointInsideRectangle(int x, int y, const ofRectangle & rectangle);
        void refreshPoints();
        void drawShape();
    };

#endif // RECTANGLE_H
