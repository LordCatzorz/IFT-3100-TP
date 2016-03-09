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

ofPoint * Image::TopLeftPoint(){
    return &topLeftPoint;
}

ofPoint * Image::TopRightPoint(){
    return &topRightPoint;
}

ofPoint * Image::BottomLeftPoint(){
    return &bottomLeftPoint;
}

ofPoint * Image::BottomRightPoint(){
    return &bottomRightPoint;
}

void Image::SetSelected(bool isSelected){
    shouldShowBorders = isSelected;
}

bool Image::GetSelected(){
    return shouldShowBorders;
}
//double rotVal = 0;
void Image::Draw(){
    ofDisableDepthTest();
    ofSetColor(ofColor::white);

    ofPushMatrix();
    ofTranslate(xOffset, yOffset);
    //rotVal += 0.1;

    //ofRotate(55.9712);
    ofRotate(angleOffset);

    image.allocate(topRightPoint.x - topLeftPoint.x, bottomLeftPoint.y - topLeftPoint.y, OF_IMAGE_COLOR);
    image.draw(topLeftPoint.x, topLeftPoint.y, topRightPoint.x - topLeftPoint.x, bottomLeftPoint.y - topLeftPoint.y);


    if(shouldShowBorders){
        ofLog() << "Drawing borders: YES";
        ofFill();
        ofSetColor(ofColor::grey);
        ofDrawRectangle(horizontalBorder1);
        ofDrawRectangle(horizontalBorder2);
        ofDrawRectangle(verticalBorder1);
        ofDrawRectangle(verticalBorder2);
    }else{
        ofLog() << "Drawing borders: NO";
    }
    ofPopMatrix();
    ofEnableDepthTest();
}

bool Image::IsPointWithinBounds(int x, int y){
    return isPointInsideRectangle(x, y, ofRectangle(topLeftPoint, bottomRightPoint));
}

bool Image::DoesRectangleOverlap(int x1, int y1, int x2, int y2){//TODO: this wont work if the selection rectangle goes trough inside teh shape and parallel to 2 sides of the shape
    bool output = false;

    ofPoint * p1 = new ofPoint();
    ofPoint * p2 = new ofPoint();
    ofPoint * p3 = new ofPoint();
    ofPoint * p4 = new ofPoint();

    ofRectangle * boundingBox = new ofRectangle(topLeftPoint.x, topLeftPoint.y, topRightPoint.x - topLeftPoint.x, bottomLeftPoint.y - topLeftPoint.y);


    Shape::translatePoint((x1 - xOffset), (y1 - yOffset), 360 - angleOffset, p1);
    Shape::translatePoint((x2 - xOffset), (y1 - yOffset), 360 - angleOffset, p2);
    Shape::translatePoint((x1 - xOffset), (y2 - yOffset), 360 - angleOffset, p3);
    Shape::translatePoint((x2 - xOffset), (y2 - yOffset), 360 - angleOffset, p4);

    output = Shape::DoEdgesIntersect(*p1, *p2, topLeftPoint, topRightPoint) ||
            Shape::DoEdgesIntersect(*p1, *p2, topLeftPoint, bottomLeftPoint) ||
            Shape::DoEdgesIntersect(*p1, *p2, bottomLeftPoint, bottomRightPoint) ||
            Shape::DoEdgesIntersect(*p1, *p2, topRightPoint, bottomRightPoint) ||

            Shape::DoEdgesIntersect(*p3, *p4, topLeftPoint, topRightPoint) ||
            Shape::DoEdgesIntersect(*p3, *p4, topLeftPoint, bottomLeftPoint) ||
            Shape::DoEdgesIntersect(*p3, *p4, bottomLeftPoint, bottomRightPoint) ||
            Shape::DoEdgesIntersect(*p3, *p4, topRightPoint, bottomRightPoint) ||

            isPointInsideRectangle(x1, y1, *boundingBox) ||
            isPointInsideRectangle(x2, y2, *boundingBox);

    delete p1;
    delete p2;
    delete p3;
    delete p4;
    delete boundingBox;

    return output;
}

void Image::AffectVector(int x, int y, ofVec3f * actionVector, bool isRotation){


    if(isRotation){
        //angleXOffset = x - xOffset - topLeftPoint.x; angleYOffset = y - yOffset - topLeftPoint.y;
        double side = (double)(x - xOffset - topLeftPoint.x);
        double adj = (double)(y - yOffset - topLeftPoint.y);

        angleOffset = atan((adj / side)) * 180/M_PI;

        if(referenceAngleOffset <= 0)
            referenceAngleOffset = angleOffset;

        angleOffset -= referenceAngleOffset;

        if(side < 0){
            angleOffset += 180;
        }

        ofLog() << "side: " << side <<  " adj: " << adj << " final angle: " << angleOffset;

        //ofLog() << "width: " << angleXOffset <<  " height: " << angleYOffset << " angleOffset: " << (angleOffset* 180/M_PI);
    }else{
        referenceAngleOffset = 0;
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
}

void Image::refreshBorders(){
    horizontalBorder1.set(topLeftPoint.x, topLeftPoint.y, topRightPoint.x - topLeftPoint.x, borderSize);
    horizontalBorder2.set(topLeftPoint.x, bottomLeftPoint.y - borderSize, bottomRightPoint.x - bottomLeftPoint.x, borderSize);
    verticalBorder1.set(topLeftPoint.x, topLeftPoint.y, borderSize, bottomLeftPoint.y - topLeftPoint.y);
    verticalBorder2.set(topRightPoint.x - borderSize, topRightPoint.y, borderSize, bottomRightPoint.y - topRightPoint.y);
}

bool Image::isPointInsideRectangle(int x, int y, const ofRectangle & rectangle){

    ofPoint * traslated = new ofPoint();
    Shape::translatePoint((x - xOffset), (y - yOffset), 360 - angleOffset, traslated);
    bool output = traslated->x>= rectangle.getX() && traslated->x <= rectangle.getX() + rectangle.getWidth() &&
            traslated->y>= rectangle.getY() && traslated->y <= rectangle.getY() + rectangle.getHeight();
    delete traslated;

    return output;

}

double Image::dotProduct(const ofPoint & point1, const ofPoint & point2){
	return 0;
}
