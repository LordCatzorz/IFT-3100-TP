#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Object2D.h"

    class Triangle2D : public Object2D
    {
    public:
                    Triangle2D();
        void        Create(int x1, int y1, int width, int height, bool isXInverted = false, bool isYInverted = false);
    private:
        ofPoint     point1,
                    point2,
                    point3;
        void refreshPoints();
        void drawShape();
    };


#endif // TRIANGLE_H
