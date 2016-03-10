#pragma once
#include "ofMain.h"

static class Shapes
{
public:

	Shapes();
	~Shapes();
	static ofMesh* createTetrahedron();
	static ofMesh* createHexahedron();
	static ofMesh* createOctahedron();
	static ofMesh* createDodecahedron();
	static ofMesh* createIcosahedron();

	static ofMesh* createCube();

	static ofMesh* createSphere();

private:


};
