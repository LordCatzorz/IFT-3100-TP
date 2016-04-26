#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "Object2D.h"

    class Rectangle2D : public Object2D
    {
    public:
                    Rectangle2D();
        void        Create(int x1, int y1, int width, int height, bool isXInverted = false, bool isYInverted = false);
    protected:
        ofPoint     point1,
                    point2,
                    point3,
                    point4;
        void refreshPoints();
        void drawShape();
	};

#endif // RECTANGLE_H
