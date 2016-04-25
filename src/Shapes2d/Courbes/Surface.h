#ifndef SURFACE_H
#define SURFACE_H
#include "ofMain.h"
#include "CatmullRom.h"
#include "../Shape.h"
#include <vector>

class Surface : public Shape
{
public:
    Surface(int var1 = 2, int var2 = 2, int var3 = 2, int var4 = 2);
    void Draw();
    virtual void AddTranslation(int x, int y, ofVec3f _draggedPixelVector){};
    virtual void AddRotation(ofVec3f _draggedPixelVector, int _axis){};
    virtual void AddScale(bool _zoomIn){};
	virtual bool IsPointWithinBounds(float x, float y) { return false; };
private:
    ofVboMesh mesh;
    CatmullRom * s1, * s2, *s3, *s4;
    int lerp(int u, int v, int p1, int p2);
    int blerp(int u, int v, int p1, int p2, int p3, int p4);
    vector<ofPoint> points;
};

#endif // SURFACE_H
