#pragma once
#include "ofMain.h"

class Shapes
{
public:

	Shapes();
	~Shapes();
	static of3dPrimitive* createTetrahedron();
	static of3dPrimitive* createHexahedron();
	static of3dPrimitive* createOctahedron();
	static of3dPrimitive* createDodecahedron();
	static of3dPrimitive* createIcosahedron();

	static of3dPrimitive* createCube();

	static of3dPrimitive* createSphere();

private:

    static void calculateNormals(of3dPrimitive* _3dprimitive);

};
