#include "Rectangle.h"

Rectangle::Rectangle()
{
    topLeftPoint.set(INT_MIN, INT_MIN);
    topRightPoint.set(INT_MIN, INT_MIN);
    bottomLeftPoint.set(INT_MIN, INT_MIN);
    bottomRightPoint.set(INT_MIN, INT_MIN);
}

Rectangle::Rectangle(bool isDefault)
{
    topLeftPoint.set(0, 0);
    topRightPoint.set(100, 0);
    bottomLeftPoint.set(0, 100);
    bottomRightPoint.set(100, 100);
    refreshBorders();
    refreshPoints();
}

void Rectangle::drawShape(){
    ofDrawRectangle(point1, point2.x - point1.x, point4.y - point2.y);
    /*ofDisableDepthTest();
    ofPushMatrix();
    if(parentShape != nullptr)
        ofTranslate(parentXOffset, parentYOffset);
    else
        ofTranslate(xOffset, yOffset);
    ofRotate(angleOffset);
    ofFill();
    ofSetColor(0);
    ofDrawRectangle(point1, point2.x - point1.x, point4.y - point2.y);
    if(shouldShowBorders){
        ofFill();
        ofSetColor(ofColor::grey);
        ofDrawRectangle(horizontalBorder1);
        ofDrawRectangle(horizontalBorder2);
        ofDrawRectangle(verticalBorder1);
        ofDrawRectangle(verticalBorder2);
    }else{
    }
    ofPopMatrix();

    ofEnableDepthTest();*/
}

void Rectangle::AffectVector(int x, int y, ofVec3f * actionVector, bool isRotation){


    if(isRotation){
        double side = (double)(x - xOffset - topLeftPoint.x);
        double adj = (double)(y - yOffset - topLeftPoint.y);

        double currentAngle = atan((adj / side)) * 180/M_PI;


        if(referenceAngleOffset <= 0){
            referenceAngleOffset = currentAngle;
            if(side < 0){
                referenceAngleOffset += 180;
            }
            angleOffset -= referenceAngleOffset;
        }

        if(side < 0){
            currentAngle = currentAngle - 180;
        }
        angleOffset += currentAngle - previousAngle;

        previousAngle = currentAngle;

        angleOffset = fmod(angleOffset, 360);
    }else{
        previousAngle = referenceAngleOffset = 0;
        if(isPointInsideRectangle(x, y, horizontalBorder1)){
            topLeftPoint.y += actionVector->y;
            topRightPoint.y += actionVector->y;
        }else if(isPointInsideRectangle(x, y, horizontalBorder2)){
            bottomLeftPoint.y += actionVector->y;
            bottomRightPoint.y += actionVector->y;
        }else if(isPointInsideRectangle(x, y, verticalBorder1)){
            topLeftPoint.x += actionVector->x;
            bottomLeftPoint.x += actionVector->x;
        }else if(isPointInsideRectangle(x, y, verticalBorder2)){
            topRightPoint.x += actionVector->x;
            bottomRightPoint.x += actionVector->x;
        }else{//Not trying to resize
            xOffset += actionVector->x; yOffset += actionVector->y;
        }

        refreshBorders();
        refreshPoints();
    }
}

void Rectangle::Create(int x1, int y1, int width, int height){

    xOffset = x1;
    yOffset = y1;
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

bool Rectangle::DoesRectangleOverlap(int x1, int y1, int x2, int y2){
    return false;
}

bool Rectangle::IsPointWithinBounds(int x, int y){
    return isPointInsideRectangle(x, y, ofRectangle(topLeftPoint, bottomRightPoint));
}

bool Rectangle::isPointInsideRectangle(int x, int y, const ofRectangle & rectangle){

    ofPoint * traslated = new ofPoint();

    if(parentShape != nullptr)
        ofTranslate(parentXOffset, parentYOffset);
    else
       Shape::translatePoint((x - xOffset), (y - yOffset), 360 - angleOffset, traslated);


    bool output = traslated->x>= rectangle.getX() && traslated->x <= rectangle.getX() + rectangle.getWidth() &&
            traslated->y>= rectangle.getY() && traslated->y <= rectangle.getY() + rectangle.getHeight();
    delete traslated;

    return output;

}

void Rectangle::refreshPoints(){

    point1.set(topLeftPoint.x, topLeftPoint.y);
    point2.set(topRightPoint.x, topRightPoint.y);
    point3.set(bottomLeftPoint.x, bottomLeftPoint.y);
    point4.set(bottomRightPoint.x, bottomRightPoint.y);
}
