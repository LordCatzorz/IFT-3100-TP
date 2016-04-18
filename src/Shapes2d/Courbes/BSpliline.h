#ifndef BSPLILINE_H
#define BSPLILINE_H
#include "ofMain.h"
#include <vector>
#include "Curve.h"
using namespace std;

class BSpliline: public Curve
{
public:
    BSpliline(int controlPoints = 6);
    void affectPoint(int deltaX, int deltaY);
    void Create(int x1, int y1, int width, int height, bool isXInverted = false, bool isYInverted = false);
private:
    ofPoint tCalculation(const ofPoint & p1, const ofPoint & p2, float t);
    ofPoint Bezier(const vector<ofPoint> & curvePoints, float t);
protected:
    void refreshPoints();
    void drawShape();
};

#endif // BSPLILINE_H
