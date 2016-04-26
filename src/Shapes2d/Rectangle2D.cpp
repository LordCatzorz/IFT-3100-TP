#include "Rectangle2D.h"


Rectangle2D::Rectangle2D()
{
    topLeftPoint.set(INT_MIN, INT_MIN);
    topRightPoint.set(INT_MIN, INT_MIN);
    bottomLeftPoint.set(INT_MIN, INT_MIN);
    bottomRightPoint.set(INT_MIN, INT_MIN);
   }

void Rectangle2D::drawShape(){

    ofDrawRectangle(point1, point2.x - point1.x, point4.y - point2.y);
}

void Rectangle2D::Create(int x1, int y1, int width, int height, bool isXInverted, bool isYInverted){

    xOffset = x1;
    yOffset = y1;
    this->setTranslation(ofVec3f(x1, y1));
    if(topLeftPoint.x == INT_MIN){
        topLeftPoint.set(0, 0);
        topRightPoint.set(0, 0);
        bottomLeftPoint.set(0, 0);
        bottomRightPoint.set(0, 0);

    }else{

        point1.x = 0;
        point1.y = 0;
        point2.x = width;
        point2.y = 0;
        point3.x = 0;
        point3.y = height;
        point4.x = width;
        point4.y = height;

        topLeftPoint.set(0, 0);
        topRightPoint.set(point4.x > point1.x ? point4.x : point1.x, 0);
        bottomLeftPoint.set(0, point4.y > point1.y ? point4.y : point1.y);
        bottomRightPoint.set(point4.x > point1.x ? point4.x : point1.x, point4.y > point1.y ? point4.y : point1.y);
    }
    refreshBorders();
}

void Rectangle2D::refreshPoints(){

    point1.set(topLeftPoint.x, topLeftPoint.y);
    point2.set(topRightPoint.x, topRightPoint.y);
    point3.set(bottomLeftPoint.x, bottomLeftPoint.y);
    point4.set(bottomRightPoint.x, bottomRightPoint.y);
}

