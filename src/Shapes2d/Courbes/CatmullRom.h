#ifndef CATMULLROM_H
#define CATMULLROM_H
#include "Curve.h"

class CatmullRom: public Curve
{
public:
    CatmullRom(int controlPoints = 6, int initialOndulation = 0);
    void affectPoint(int deltaX, int deltaY);
    void Create(int x1, int y1, int width, int height, bool isXInverted = false, bool isYInverted = false);
    void Create(const ofPoint & p0, const ofPoint & p1);
    ofPoint getPointX(int val);
    ofPoint getPointZ(int val);
private:
    ofPoint Catmull(const ofPoint & p0, const ofPoint & p1, const ofPoint & p2, const ofPoint & p3, float t);
    void creator(int x1, int y1, int z1, int width, int height, int depth, bool fixCoordinates = true);
    int baseOndulation;
protected:
    void refreshPoints();
    void drawShape();
};

#endif // CATMULLROM_H
