#ifndef CATMULLROM_H
#define CATMULLROM_H
#include "Curve.h"

class CatmullRom: public Curve
{
public:
    CatmullRom(int controlPoints = 6);
    void affectPoint(int deltaX, int deltaY);
    void Create(int x1, int y1, int width, int height);
    void AddTranslation(int x, int y, ofVec3f _draggedPixelVector);
    ofPoint getPointX(int val);
    ofPoint getPointZ(int val);
private:
    ofPoint Catmull(const ofPoint & p0, const ofPoint & p1, const ofPoint & p2, const ofPoint & p3, float t);
protected:
    void refreshPoints();
    void drawShape();
};

#endif // CATMULLROM_H
