#ifndef CURVE_H
#define CURVE_H
#include "ofMain.h"
#include <vector>
#include "../Object2D.h"
using namespace std;

class Curve: public Object2D
{
public:
    bool intersect(int x, int y){
        return intersectsPoint(x, y) != nullptr;
    }
    virtual void affectPoint(int deltaX, int deltaY) = 0;
    virtual void Create(int x1, int y1, int width, int height, bool isXInverted = false, bool isYInverted = false) = 0;

    void AddTranslation(int x, int y, ofVec3f _draggedPixelVector){
        ofPoint tmp;
        tmp.x = x - this->getTranslation().x;
        tmp.y = y - this->getTranslation().y;

        ofPoint closestPoint = curve.getClosestPoint(tmp);
        ofPoint * inersected = intersectsPoint(tmp.x, tmp.y);

        if(inersected != nullptr){
            inersected->x = x - this->getTranslation().x;
            inersected->y = y - this->getTranslation().y;
            inersected = nullptr;
        }else if(distanceBetweenPoints(tmp.x, tmp.y, closestPoint.x, closestPoint.y) < 10)
            Object2D::AddTranslation(x, y, _draggedPixelVector);
    }
protected:
    int ctrlPoints;
    vector<ofPoint> points;
    ofPolyline curve;
    ofPoint * intersectsPoint(int x, int y){
        for(ofPoint & p : points){
            if(abs(p.x - x) <= 10 && abs(p.y - y) <= 10)
                return &p;
        }

        return nullptr;
    }

    bool isPointInCurve(int x, int y){
        if(x >= points[points.size() - 1].x)
            return false;

        int treshold = 5;
        int index1, index2 = 0;
        while(points[index2].x < x && index2 < points.size()){
            index2++;
        }
        if(index2 == 0){
            return false;
        }
        index1 = index2 - 1;

        return distanceBetweenPoints(points[index1].x, points[index1].y, x, y) +
               distanceBetweenPoints(x, y, points[index2].x, points[index2].y) -
               distanceBetweenPoints(points[index1].x, points[index1].y, points[index2].x, points[index2].y) <=
               treshold;
    }

    float distanceBetweenPoints(const float & x1, const float & y1, const float & x2, const float & y2) const{
        return (float)sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    }

    virtual void refreshPoints() = 0;
    virtual void drawShape() = 0;
};

#endif // CURVE_H
