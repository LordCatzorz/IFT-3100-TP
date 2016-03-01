#ifndef IMAGE_H
#define IMAGE_H

#include "ofMain.h"

class Image
{
public:
    Image(string imageName);
    void SetImageName(string imageName);
    string GetImageName();
    bool IsPointWithinBounds(int x, int y);
    void AffectVector(int x, int y, ofVec3f * actionVector);
    void ShowBorders(bool shouldShow);
    void Draw();
private:

    int         borderSize = 10;
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
};

#endif // IMAGE_H
