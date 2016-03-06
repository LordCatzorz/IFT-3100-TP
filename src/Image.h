#ifndef IMAGE_H
#define IMAGE_H

#include "ofMain.h"
#include <math.h>
#include <stdlib.h>

class Image
{
public:
    Image(string imageName);
    void SetImageName(string imageName);
    string GetImageName();
    ofPoint * TopLeftPoint();
    ofPoint * TopRightPoint();
    ofPoint * BottomLeftPoint();
    ofPoint * BottomRightPoint();
    bool IsPointWithinBounds(int x, int y);
    void AffectVector(int x, int y, ofVec3f * actionVector, bool isRotation = false);
    void ShowBorders(bool shouldShow);
    void Draw();
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

    double      dotProduct(const ofPoint & point1, const ofPoint & point2);
};

#endif // IMAGE_H
