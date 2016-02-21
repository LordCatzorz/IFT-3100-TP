#include "shapes.h"

Shapes::Shapes()
{
}

Shapes::~Shapes()
{
}

ofMesh * Shapes::createTetrahedron()
{
	ofMesh* mesh = new ofMesh();
	mesh->addVertex(ofPoint(0.5, 0, -(1.0 / (2.0*sqrt(2)))));
	mesh->addVertex(ofPoint(-0.5, 0, -(1.0 / (2.0*sqrt(2)))));
	mesh->addVertex(ofPoint(0, 0.5, (1.0 / (2.0*sqrt(2)))));
	mesh->addVertex(ofPoint(0, -0.5, (1.0 / (2.0*sqrt(2)))));

	mesh->addTriangle(0, 1, 2);
	mesh->addTriangle(0, 1, 3);
	mesh->addTriangle(0, 2, 3);
	mesh->addTriangle(1, 2, 3);
	
	return mesh;
}

ofMesh * Shapes::createHexahedron()
{
	ofMesh* mesh = new ofMesh();

	//Top vertices
	mesh->addVertex(ofPoint(-0.5, -0.5, -0.5));// indice 0
	mesh->addVertex(ofPoint(0.5, -0.5, -0.5));// indice 1
	mesh->addVertex(ofPoint(-0.5, -0.5, 0.5));// indice 2
	mesh->addVertex(ofPoint(0.5, -0.5, 0.5));// indice 3
									  //Bottom vertices
	mesh->addVertex(ofPoint(-0.5, 0.5, -0.5));// indice 4
	mesh->addVertex(ofPoint(0.5, 0.5, -0.5));// indice 5
	mesh->addVertex(ofPoint(-0.5, 0.5, 0.5));// indice 6
	mesh->addVertex(ofPoint(0.5, 0.5, 0.5));// indice 7

									  //Top Face
	mesh->addTriangle(0, 1, 2); //indice 0
	mesh->addTriangle(3, 1, 2);// indice 1
							   //Bottom Face
	mesh->addTriangle(4, 5, 6);//indice 2
	mesh->addTriangle(7, 5, 6);// indice 3
							   //Left face
	mesh->addTriangle(0, 2, 4);// indice 4
	mesh->addTriangle(6, 2, 4);//indice 5
							   //Right face
	mesh->addTriangle(1, 3, 5);// indice 6
	mesh->addTriangle(7, 3, 5);//indice 7
							   //Front face
	mesh->addTriangle(0, 1, 4);// indice 8
	mesh->addTriangle(5, 1, 4);//indice 9
							   //Back face
	mesh->addTriangle(2, 3, 6);// indice 10
	mesh->addTriangle(7, 3, 6);//indice 11
	return mesh;
}

ofMesh * Shapes::createOctahedron()
{
	throw exception("Not yet implemented");
}

ofMesh * Shapes::createDodecahedron()
{
	throw exception("Not yet implemented");
}

ofMesh * Shapes::createIcosahedron()
{
	throw exception("Not yet implemented");
}

ofMesh* Shapes::createCube()
{
	return this->createHexahedron();
}

ofMesh* Shapes::createSphere()
{
	throw exception("Not yet implemented");
}


