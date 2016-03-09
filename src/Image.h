#ifndef IMAGE_H
#define IMAGE_H

#ifdef _WIN32
#define M_PI PI
#endif

#include "ofMain.h"
#include "Shape.h"
#include <math.h>
#include <stdlib.h>

class Image: public Shape
{
public:
	Image(string imageName);
    void        SetImageName(string imageName);
    string      GetImageName();
    ofPoint *   TopLeftPoint();
    ofPoint *   TopRightPoint();
    ofPoint *   BottomLeftPoint();
    ofPoint *   BottomRightPoint();
    bool        IsPointWithinBounds(int x, int y);
    bool        DoesRectangleOverlap(int x1, int y1, int x2, int y2);
    void        AffectVector(int x, int y, ofVec3f * actionVector, bool isRotation = false);
    void        SetSelected(bool isSelected);
    bool        GetSelected();
    void        Draw();
private:

	int         borderSize = 10, xOffset = 0, yOffset = 0;
	double      angleOffset = 0, referenceAngleOffset = 0;
	bool        shouldShowBorders = false;
	string      imgName;
	ofImage     image;
	ofRectangle horizontalBorder1,
                horizontalBorder2,
                verticalBorder1,
                verticalBorder2;
	ofPoint     topLeftPoint,
                topRightPoint,
                bottomLeftPoint,
                bottomRightPoint;

	void        refreshBorders();
	bool        isPointInsideRectangle(int x, int y, const ofRectangle & rectangle);
    bool        valueInRange(int value, int min, int max){ return (value >= min) && (value <= max); };
    double      dotProduct(const ofPoint & point1, const ofPoint & point2);

};

#endif // IMAGE_H
