#include "Image.h"
#include <cmath>

Image::Image(string imageName)
{
    imgName = imageName;
    image.load(imgName);    
    image.allocate(image.getWidth(), image.getHeight(), OF_IMAGE_COLOR);

    topLeftPoint.x = 0;
    topLeftPoint.y = 0;
    topRightPoint.x = image.getWidth();
    topRightPoint.y = 0;
    bottomLeftPoint.x = 0;
    bottomLeftPoint.y = image.getHeight();
    bottomRightPoint.x = image.getWidth();
    bottomRightPoint.y = image.getHeight();
    refreshBorders();
}

void Image::SetImageName(string imageName){
    image.load(imgName);

    topRightPoint.x = topLeftPoint.x + image.getWidth();
    bottomLeftPoint.y = topLeftPoint.y + image.getHeight();
    bottomRightPoint.x = topLeftPoint.x + image.getWidth();
    bottomRightPoint.y = topLeftPoint.y + image.getHeight();
    refreshBorders();
}

string Image::GetImageName(){
    return imgName;
}

double rotVal = 0;
void Image::drawShape(){
    image.allocate(topRightPoint.x - topLeftPoint.x, bottomLeftPoint.y - topLeftPoint.y, OF_IMAGE_COLOR);
    image.draw(topLeftPoint.x, topLeftPoint.y, topRightPoint.x - topLeftPoint.x, bottomLeftPoint.y - topLeftPoint.y);
/*    ofDisableDepthTest();
    ofSetColor(ofColor::white);

    ofPushMatrix();
    ofTranslate(xOffset, yOffset);
    //rotVal += 0.1;

    //ofRotate(55.9712);
    ofRotate(angleOffset);

    image.allocate(topRightPoint.x - topLeftPoint.x, bottomLeftPoint.y - topLeftPoint.y, OF_IMAGE_COLOR);
    image.draw(topLeftPoint.x, topLeftPoint.y, topRightPoint.x - topLeftPoint.x, bottomLeftPoint.y - topLeftPoint.y);


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
/*
bool Image::IsPointWithinBounds(float x, float y){
    return isPointInsideRectangle(x, y, ofRectangle(topLeftPoint, bottomRightPoint));
}*/

bool Image::DoesRectangleOverlap(int x1, int y1, int x2, int y2){//TODO: this wont work if the selection rectangle goes trough inside teh shape and parallel to 2 sides of the shape
    bool output = false;

    ofPoint * p1 = new ofPoint();
    ofPoint * p2 = new ofPoint();
    ofPoint * p3 = new ofPoint();
    ofPoint * p4 = new ofPoint();

    ofPoint * p5 = new ofPoint();
    ofPoint * p6 = new ofPoint();

    Shape2D::translatePoint(topLeftPoint.x, topLeftPoint.y, angleOffset - 360, p5);

    ofRectangle * boundingBox = new ofRectangle(topLeftPoint.x, topLeftPoint.y, topRightPoint.x - topLeftPoint.x, bottomLeftPoint.y - topLeftPoint.y);


    Shape2D::translatePoint((x1 - xOffset), (y1 - yOffset), 360 - angleOffset, p1);
    Shape2D::translatePoint((x2 - xOffset), (y1 - yOffset), 360 - angleOffset, p2);
    Shape2D::translatePoint((x1 - xOffset), (y2 - yOffset), 360 - angleOffset, p3);
    Shape2D::translatePoint((x2 - xOffset), (y2 - yOffset), 360 - angleOffset, p4);

    ofRectangle * selectionBox = new ofRectangle(x1, y1, x2 - x1, y2 - y1);

    output = Shape2D::DoEdgesIntersect(*p1, *p2, topLeftPoint, topRightPoint) ||
            Shape2D::DoEdgesIntersect(*p1, *p2, topLeftPoint, bottomLeftPoint) ||
            Shape2D::DoEdgesIntersect(*p1, *p2, bottomLeftPoint, bottomRightPoint) ||
            Shape2D::DoEdgesIntersect(*p1, *p2, topRightPoint, bottomRightPoint) ||

            Shape2D::DoEdgesIntersect(*p3, *p4, topLeftPoint, topRightPoint) ||
            Shape2D::DoEdgesIntersect(*p3, *p4, topLeftPoint, bottomLeftPoint) ||
            Shape2D::DoEdgesIntersect(*p3, *p4, bottomLeftPoint, bottomRightPoint) ||
            Shape2D::DoEdgesIntersect(*p3, *p4, topRightPoint, bottomRightPoint) ||

            isPointInsideRectangle(x1, y1, *boundingBox) ||
            isPointInsideRectangle(x2, y2, *boundingBox) ||

            (p5->x>= selectionBox->x && p5->x <= selectionBox->x + selectionBox->width &&
            p5->y>= selectionBox->y && p5->y <= selectionBox->y + selectionBox->height);

            /*isPointInsideRectangle(p5->x - xOffset - xOffset, p5->y - yOffset - yOffset, *selectionBox) ||
            isPointInsideRectangle(bottomRightPoint.x, bottomRightPoint.y, *selectionBox);*/

    delete p1;
    delete p2;
    delete p3;
    delete p4;
    delete boundingBox;
    delete selectionBox;

    return output;
}

/*void Image::AffectVector(int x, int y, ofVec3f * actionVector, bool isRotation){


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
    }
}*/

/*void Image::refreshBorders(){
    horizontalBorder1.set(topLeftPoint.x, topLeftPoint.y, topRightPoint.x - topLeftPoint.x, borderSize);
    horizontalBorder2.set(topLeftPoint.x, bottomLeftPoint.y - borderSize, bottomRightPoint.x - bottomLeftPoint.x, borderSize);
    verticalBorder1.set(topLeftPoint.x, topLeftPoint.y, borderSize, bottomLeftPoint.y - topLeftPoint.y);
    verticalBorder2.set(topRightPoint.x - borderSize, topRightPoint.y, borderSize, bottomRightPoint.y - topRightPoint.y);
}*/
/*
bool Image::isPointInsideRectangle(int x, int y, const ofRectangle & rectangle){

    ofPoint * translated = new ofPoint();
    Shape2D::translatePoint((x - xOffset), (y - yOffset), 360 - angleOffset, translated);
    bool output = translated->x>= rectangle.getX() && translated->x <= rectangle.getX() + rectangle.getWidth() &&
            translated->y>= rectangle.getY() && translated->y <= rectangle.getY() + rectangle.getHeight();
    delete translated;

    return output;

}*/

double Image::dotProduct(const ofPoint & point1, const ofPoint & point2){
	return 0;
}
