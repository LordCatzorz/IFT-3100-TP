#include "Ellipse.h"

Ellipse::Ellipse()
{
    topLeftPoint.set(INT_MIN, INT_MIN);
    topRightPoint.set(INT_MIN, INT_MIN);
    bottomLeftPoint.set(INT_MIN, INT_MIN);
    bottomRightPoint.set(INT_MIN, INT_MIN);
}

void Ellipse::drawShape(){
    ofEllipse(point1.x + (int)((point2.x - point1.x) / 2), point1.y + (int)((point3.y - point1.y) / 2), point2.x - point1.x, point4.y - point2.y);
    /*ofDisableDepthTest();
    ofPushMatrix();
    ofTranslate(xOffset, yOffset);
    ofRotate(angleOffset);
    ofFill();
    ofSetColor(0);
    ofEllipse(point1.x + (int)((point2.x - point1.x) / 2), point1.y + (int)((point3.y - point1.y) / 2), point2.x - point1.x, point4.y - point2.y);
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
