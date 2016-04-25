#include "BSpliline.h"

BSpliline::BSpliline(int controlPoints)
{
    ctrlPoints = controlPoints + 1;
    shapeHasBorders = false;
}

void BSpliline::Create(int x1, int y1, int width, int height, bool isXInverted, bool isYInverted){

    this->setTranslation(ofVec3f(x1, y1));

    points.clear();
    points.push_back(ofPoint(isXInverted ? width : 0, isYInverted? height : 0));

    double xDiff = (width * (isXInverted ? -1 : 1)) / ctrlPoints;
    double yDiff = (height * (isYInverted ? -1 : 1)) / ctrlPoints;

    for(int i = 1; i < ctrlPoints; i++){
        ofPoint tmp;
        tmp.x = points[i - 1].x + xDiff;
        tmp.y = points[i - 1].y + yDiff;
        points.push_back(tmp);
    }

    int yOffset = 50;
    for(int i = 1; i < ctrlPoints; i++){
        points[i].y += yOffset;
        yOffset *= -1;
    }

    points.push_back(ofPoint(isXInverted ? 0 : width, isYInverted? 0 : height));

    topLeftPoint.set(0, 0);
    topRightPoint.set(width, 0);
    bottomLeftPoint.set(0, height);
    bottomRightPoint.set(width, height);
    refreshBorders();
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
