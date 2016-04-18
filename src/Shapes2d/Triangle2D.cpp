#include "Triangle2D.h"

Triangle2D::Triangle2D()
{
    topLeftPoint.set(INT_MIN, INT_MIN);
    topRightPoint.set(INT_MIN, INT_MIN);
    bottomLeftPoint.set(INT_MIN, INT_MIN);
    bottomRightPoint.set(INT_MIN, INT_MIN);
}

void Triangle2D::drawShape(){
    ofDrawTriangle(point1, point2, point3);
}

void Triangle2D::Create(int x1, int y1, int width, int height, bool isXInverted, bool isYInverted){

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
        point1.y = height;

        point2.x = (int)(width / 2);
        point2.y = 0;

        point3.x = width;
        point3.y = height;

        topLeftPoint.set(0, 0);
        topRightPoint.set(point3.x > point1.x ? point3.x : point1.x, 0);
        bottomLeftPoint.set(0, point3.y > point1.y ? point3.y : point1.y);
        bottomRightPoint.set(point3.x > point1.x ? point3.x : point1.x, point3.y > point1.y ? point3.y : point1.y);
    }
    refreshBorders();
}

/*bool Triangle2D::DoesRectangleOverlap(int x1, int y1, int x2, int y2){
    return false;
}*/

void Triangle2D::refreshPoints(){

    point1.set(bottomLeftPoint.x, bottomLeftPoint.y);
    point2.set(bottomLeftPoint.x + (int)((bottomRightPoint.x - bottomLeftPoint.x) / 2), topLeftPoint.y);
    point3.set(bottomRightPoint.x, bottomRightPoint.y);

}

