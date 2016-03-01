#include "Image.h"

Image::Image(string imageName)
{
    imgName = imageName;
    image.load(imgName);

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

void Image::ShowBorders(bool shouldShow){
    shouldShowBorders = shouldShow;
}

void Image::Draw(){
    image.draw(topLeftPoint.x, topLeftPoint.y, topRightPoint.x - topLeftPoint.x, bottomLeftPoint.y - topLeftPoint.y);
    if(shouldShowBorders){
        ofFill();
        ofSetColor(ofColor::grey);
        ofDrawRectangle(horizontalBorder1);
        ofDrawRectangle(horizontalBorder2);
        ofDrawRectangle(verticalBorder1);
        ofDrawRectangle(verticalBorder2);
    }
}

bool Image::IsPointWithinBounds(int x, int y){//TODO: this doesn't account for a rotated rectangle
    return isPointInsideRectangle(x, y, ofRectangle(topLeftPoint, bottomRightPoint));//x >= topLeftPoint.x && x <= topRightPoint.x && y >= topRightPoint.y && y <= bottomRightPoint.y;
}

void Image::AffectVector(int x, int y, ofVec3f * actionVector){

    //Verify if the user is trying to resize; TODO: this doesn't account for rotated rectangle
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
        topLeftPoint.x += actionVector->x;
        topRightPoint.x += actionVector->x;
        bottomLeftPoint.x += actionVector->x;
        bottomRightPoint.x += actionVector->x;

        topLeftPoint.y += actionVector->y;
        topRightPoint.y += actionVector->y;
        bottomLeftPoint.y += actionVector->y;
        bottomRightPoint.y += actionVector->y;
    }
    refreshBorders();
}

void Image::refreshBorders(){
    horizontalBorder1.set(topLeftPoint.x, topLeftPoint.y, topRightPoint.x - topLeftPoint.x, borderSize);
    horizontalBorder2.set(topLeftPoint.x, bottomLeftPoint.y - borderSize, bottomRightPoint.x - bottomLeftPoint.x, borderSize);
    verticalBorder1.set(topLeftPoint.x, topLeftPoint.y, borderSize, bottomLeftPoint.y - topLeftPoint.y);
    verticalBorder2.set(topRightPoint.x - borderSize, topRightPoint.y, borderSize, bottomRightPoint.y - topRightPoint.y);
}

bool Image::isPointInsideRectangle(int x, int y, const ofRectangle & rectangle){//TODO: make this account for
    return x >= rectangle.getX() && x <= rectangle.getX() + rectangle.getWidth() && y >= rectangle.getY() && y <= rectangle.getY() + rectangle.getHeight();
}
