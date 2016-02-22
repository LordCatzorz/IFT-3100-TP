#pragma once
#include "ofMain.h"

class Shapes
{
public:

    Shapes();
    ~Shapes();
    ofMesh* createTetrahedron();
    ofMesh* createHexahedron();
    ofMesh* createOctahedron();
    ofMesh* createDodecahedron();
    ofMesh* createIcosahedron();

    ofMesh* createCube();

    ofMesh* createSphere();

private:

};
