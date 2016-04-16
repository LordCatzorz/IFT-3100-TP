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
    virtual void Create(int x1, int y1, int width, int height) = 0;
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

    virtual void refreshPoints() = 0;
    virtual void drawShape() = 0;
};

#endif // CURVE_H
