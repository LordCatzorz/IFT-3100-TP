#ifndef CURVE_H
#define CURVE_H
#include "ofMain.h"
#include <vector>
#include "../Object2D.h"
using namespace std;

class Curve: public Object2D
{
public:
	bool intersect(int x, int y);
    virtual void affectPoint(int deltaX, int deltaY) = 0;
    virtual void Create(int x1, int y1, int width, int height, bool isXInverted = false, bool isYInverted = false) = 0;

	void AddTranslation(int x, int y, ofVec3f _draggedPixelVector);
protected:
    int ctrlPoints;
    vector<ofPoint> points;
    ofPolyline curve;
	ofPoint * intersectsPoint(int x, int y);

	bool isPointInCurve(int x, int y);

	float distanceBetweenPoints(const float & x1, const float & y1, const float & x2, const float & y2) const;

    virtual void refreshPoints() = 0;
    virtual void drawShape() = 0;
};

#endif // CURVE_H
