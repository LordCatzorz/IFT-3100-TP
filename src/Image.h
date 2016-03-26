#ifndef IMAGE_H
#define IMAGE_H

#ifdef _WIN32
#define M_PI PI
#endif

#include "ofMain.h"
#include "Shapes2d/Object2D.h"
#include <math.h>
#include <stdlib.h>

class Image: public Object2D
{
public:
	Image(string imageName);
    void        SetImageName(string imageName);
    string      GetImageName();
    //bool        IsPointWithinBounds(float x, float y);
    //bool        DoesRectangleOverlap(int x1, int y1, int x2, int y2);
    //void        AffectVector(int x, int y, ofVec3f * actionVector, bool isRotation = false);
    void Create(int x1, int y1, int width, int height){}
    //void        Draw();
private:

    string      imgName;
    ofImage     image;

    //void        refreshBorders();
    //bool        isPointInsideRectangle(int x, int y, const ofRectangle & rectangle);
    bool        valueInRange(int value, int min, int max){ return (value >= min) && (value <= max); }
    double      dotProduct(const ofPoint & point1, const ofPoint & point2);
    void drawShape();
    void refreshPoints(){}

};

#endif // IMAGE_H
