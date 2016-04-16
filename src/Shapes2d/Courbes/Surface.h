#ifndef SURFACE_H
#define SURFACE_H
#include "ofMain.h"
#include "CatmullRom.h"
#include <vector>

class Surface
{
public:
    Surface();
    void Draw();
private:
    ofVboMesh mesh;
    CatmullRom * s1, * s2, *s3, *s4;
    int lerp(int u, int v, int p1, int p2);
    int blerp(int u, int v, int p1, int p2, int p3, int p4);
    vector<ofPoint> points;
};

#endif // SURFACE_H
