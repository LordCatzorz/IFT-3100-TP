#include "BSpliline.h"

BSpliline::BSpliline(int controlPoints)
{
    ctrlPoints = controlPoints + 1;
}

void BSpliline::Create(int x1, int y1, int width, int height){

    this->setTranslation(ofVec3f(x1, y1));

    int padding = width < 10 ? 0 : 5;
    points.clear();
    points.push_back(ofPoint(padding, height / 2));
    double xDiff = (width - padding * 2) / ctrlPoints;
    double yDiff = height / ctrlPoints;

    for(int i = 1; i < ctrlPoints; i++){
        ofPoint tmp;
        tmp.x = points[i - 1].x + xDiff;
        tmp.y = points[i - 1].y;// + yDiff;
        points.push_back(tmp);
    }

    int yOffset = 50;
    for(int i = 1; i < ctrlPoints; i++){
        points[i].y += yOffset;
        yOffset *= -1;
    }

    points.push_back(ofPoint(width - padding, height / 2));

    topLeftPoint.set(0, 0);
    topRightPoint.set(width, 0);
    bottomLeftPoint.set(0, height);
    bottomRightPoint.set(width, height);
    refreshBorders();
}

void BSpliline::AddTranslation(int x, int y, ofVec3f _draggedPixelVector){
    ofPoint * inersected = intersectsPoint(x - this->getTranslation().x, y - this->getTranslation().y);
    if(inersected == nullptr){
        Object2D::AddTranslation(x, y, _draggedPixelVector);
    }else{
        inersected->x = x - this->getTranslation().x;
        inersected->y = y - this->getTranslation().y;
    }

}

void BSpliline::refreshPoints(){}

void BSpliline::drawShape(){
    if(points.size() < 2)
        return;
    ofFill();
    ofSetColor(0);
    for(ofPoint & p : points){
        ofEllipse(p.x, p.y, 10, 10);
    }
    curve.clear();

    curve.curveTo(points[0]);
    curve.curveTo(points[0]);

    for(float t = 1.f; t >= 0.f; t-= 0.01){
        curve.curveTo(Bezier(points, t));
    }

    curve.curveTo(points[points.size() - 1]);
    curve.curveTo(points[points.size() - 1]);

    curve.draw();
}

void BSpliline::affectPoint(int deltaX, int deltaY){
    ofPoint * toAffect = intersectsPoint(deltaX, deltaY);
    if(toAffect == nullptr)
        return;
    toAffect->x = deltaX;
    toAffect->y = deltaY;
}

ofPoint BSpliline::tCalculation(const ofPoint &p1, const ofPoint &p2, float t){
    ofPoint output;

    output.x = (1.f - t) * p2.x + t * p1.x;
    output.y = (1.f - t) * p2.y + t * p1.y;

    return output;
}

ofPoint BSpliline::Bezier(const vector<ofPoint> & curvePoints, float t){
    if(curvePoints.size() == 1)
        return curvePoints[0];

    vector<ofPoint> newPoints;
    for(vector<ofPoint>::const_iterator itr = curvePoints.begin(); (itr + 1) != curvePoints.end(); itr++){
        newPoints.push_back(tCalculation((*itr), (*(itr + 1)), t));
    }

    return Bezier(newPoints, t);
}
