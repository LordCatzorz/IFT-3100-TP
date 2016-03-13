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
    /*ofDisableDepthTest();
    ofPushMatrix();
    if(parentShape != nullptr)
        ofTranslate(parentXOffset, parentYOffset);
    else
        ofTranslate(xOffset, yOffset);
    ofRotate(angleOffset);
    ofFill();
    ofSetColor(drawColor);
    ofDrawTriangle(point1, point2, point3);
    if(shouldShowBorders){
        ofFill();
        ofSetColor(ofColor::grey);
        ofDrawRectangle(horizontalBorder1);
        ofDrawRectangle(horizontalBorder2);
        ofDrawRectangle(verticalBorder1);
        ofDrawRectangle(verticalBorder2);
    }else{
    }
    for(Shape * child : children)
        child->Draw();
    ofPopMatrix();

    ofEnableDepthTest();*/
}

void Triangle2D::AffectVector(int x, int y, ofVec3f * actionVector, bool isRotation){


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
            for(Shape2D * child : children){
                child->AffectVector(x, y, actionVector, isRotation);
            }
        }

        refreshBorders();
        refreshPoints();

    }

}

void Triangle2D::Create(int x1, int y1, int width, int height){

    xOffset = x1;
    yOffset = y1;
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

bool Triangle2D::DoesRectangleOverlap(int x1, int y1, int x2, int y2){
    return false;
}

bool Triangle2D::IsPointWithinBounds(float x, float y){
    return isPointInsideRectangle(x, y, ofRectangle(topLeftPoint, bottomRightPoint));
}

bool Triangle2D::isPointInsideRectangle(int x, int y, const ofRectangle & rectangle){

    ofPoint * traslated = new ofPoint();
    Shape2D::translatePoint((x - xOffset), (y - yOffset), 360 - angleOffset, traslated);
    bool output = traslated->x>= rectangle.getX() && traslated->x <= rectangle.getX() + rectangle.getWidth() &&
            traslated->y>= rectangle.getY() && traslated->y <= rectangle.getY() + rectangle.getHeight();
    delete traslated;

    return output;

}

void Triangle2D::refreshPoints(){

    point1.set(bottomLeftPoint.x, bottomLeftPoint.y);
    point2.set(bottomLeftPoint.x + (int)((bottomRightPoint.x - bottomLeftPoint.x) / 2), topLeftPoint.y);
    point3.set(bottomRightPoint.x, bottomRightPoint.y);

}

