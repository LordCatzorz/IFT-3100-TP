#include "Shapes.h"
///@Todo: Make sure all shapes have a diameter of 1

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
	ofMesh* mesh = new ofMesh();
	double root2over2 = sqrt(2) / 2.0;
	//Vertex top
	mesh->addVertex(ofPoint(0, -root2over2, 0)); // Indice 0
	//Vertices middle
	mesh->addVertex(ofPoint(root2over2, 0, 0));// Indice 1
	mesh->addVertex(ofPoint(0, 0, root2over2));// Indice 2
	mesh->addVertex(ofPoint(-root2over2, 0, 0));// Indice 3
	mesh->addVertex(ofPoint(0, 0, -root2over2));// Indice 4
	//Vertex bottom
	mesh->addVertex(ofPoint(0, root2over2, 0));// Indice 5

	//Top
	mesh->addTriangle(0, 1, 2);
	mesh->addTriangle(0, 2, 3);
	mesh->addTriangle(0, 3, 4);
	mesh->addTriangle(0, 4, 1);
	//Bottom
	mesh->addTriangle(5, 1, 2);
	mesh->addTriangle(5, 2, 3);
	mesh->addTriangle(5, 3, 4);
	mesh->addTriangle(5, 4, 1);

	return mesh;
}

ofMesh * Shapes::createDodecahedron()
{
	ofMesh* mesh = new ofMesh();
	double heightOfRoof = (sqrt(5) - 1) / 2.0; //0.618
	double size1 = (1 + heightOfRoof); // 1.618
	double size2 = (1 - heightOfRoof*heightOfRoof); //0.618

	mesh->addVertex(ofPoint(0, size1, size2));  //0
	mesh->addVertex(ofPoint(0, size1, -size2)); //1

	mesh->addVertex(ofPoint(1, 1, 1));			//2
	mesh->addVertex(ofPoint(1, 1, -1));			//3
	mesh->addVertex(ofPoint(-1, 1, 1));			//4
	mesh->addVertex(ofPoint(-1, 1, -1));		//5

	mesh->addVertex(ofPoint(size1, size2, 0));	//6
	mesh->addVertex(ofPoint(-size1, size2, 0));	//7

	mesh->addVertex(ofPoint(size2, 0, size1));	 //8
	mesh->addVertex(ofPoint(size2, 0, -size1));	 //9
	mesh->addVertex(ofPoint(-size2, 0, size1));	 //10
	mesh->addVertex(ofPoint(-size2, 0, -size1)); //11

	mesh->addVertex(ofPoint(size1, -size2, 0));	 //12
	mesh->addVertex(ofPoint(-size1, -size2, 0)); //13

	mesh->addVertex(ofPoint(1, -1, 1));			 //14
	mesh->addVertex(ofPoint(1, -1, -1));		 //15
	mesh->addVertex(ofPoint(-1, -1, 1));		 //16
	mesh->addVertex(ofPoint(-1, -1, -1));		 //17

	mesh->addVertex(ofPoint(0, -size1, size2));	 //18
	mesh->addVertex(ofPoint(0, -size1, -size2)); //19

	//Do the fucking dodecahedron

	//Face 0, vertices 0,1,3,6,2
	mesh->addTriangle(0, 1, 6);
	mesh->addTriangle(0, 2, 6);
	mesh->addTriangle(3, 1, 6);
	//Face 1, vertices 0,1,5,7,4
	mesh->addTriangle(0, 1, 7);
	mesh->addTriangle(0, 4, 7);
	mesh->addTriangle(5, 1, 7);
	//Face 2, vertices 1,5,11,9,3
	mesh->addTriangle(1, 5, 9);
	mesh->addTriangle(1, 3, 9);
	mesh->addTriangle(11, 5, 9);
	//Face 3, vertices 0,4,10,8,2
	mesh->addTriangle(0, 4, 8);
	mesh->addTriangle(0, 2, 8);
	mesh->addTriangle(10, 4, 8);
	//Face 4, vertices 2,6,12,14,8
	mesh->addTriangle(2, 6, 14);
	mesh->addTriangle(2, 8, 14);
	mesh->addTriangle(12, 6, 14);
	//Face 5, vertices 6,3,9,15,12
	mesh->addTriangle(6, 3, 15);
	mesh->addTriangle(6, 12, 15);
	mesh->addTriangle(9, 3, 15);
	//Face 6, vertices 5,11,17,13,7
	mesh->addTriangle(5, 11, 13);
	mesh->addTriangle(5, 7, 13);
	mesh->addTriangle(17, 11, 13);
	//Face 7, vertices 7,4,10,16,13  
	mesh->addTriangle(7, 4, 16);
	mesh->addTriangle(7, 13, 16);
	mesh->addTriangle(10, 4, 16);
	//Face 8, vertices 19,17,11,9,15
	mesh->addTriangle(19, 17, 9);
	mesh->addTriangle(19, 15, 9);
	mesh->addTriangle(11, 17, 9);
	//Face 9, vertices 18,16,10,8,14
	mesh->addTriangle(18, 16, 8);
	mesh->addTriangle(18, 14, 8);
	mesh->addTriangle(10, 16, 8);
	//Face 10, vertices 18,19,15,12,14
	mesh->addTriangle(18, 19, 12);
	mesh->addTriangle(18, 14, 12);
	mesh->addTriangle(15, 19, 12);
	//Face 11, vertices 18,19,17,13,16
	mesh->addTriangle(18, 19, 13);
	mesh->addTriangle(18, 16, 13);
	mesh->addTriangle(17, 19, 13);

	return mesh;
}

ofMesh * Shapes::createIcosahedron()
{
	ofMesh* mesh = new ofMesh();
	double phi = ((sqrt(5) + 1) / 2.0);

	//See https://en.wikipedia.org/wiki/Regular_icosahedron#/media/File:Icosahedron-golden-rectangles.svg
	// But flipped horizontally

	//Long on z rectangle
	mesh->addVertex(ofPoint(0, 1, phi));  //0
	mesh->addVertex(ofPoint(0, 1, -phi)); //1
	mesh->addVertex(ofPoint(0, -1, phi)); //2
	mesh->addVertex(ofPoint(0, -1, -phi));//3

	//Long on y rectangle
	mesh->addVertex(ofPoint(1, phi, 0));   //4
	mesh->addVertex(ofPoint(1, -phi, 0));  //5
	mesh->addVertex(ofPoint(-1, phi, 0));  //6
	mesh->addVertex(ofPoint(-1, -phi, 0)); //7

	//Long on x renctangle
	mesh->addVertex(ofPoint(phi, 0, 1));   //8
	mesh->addVertex(ofPoint(-phi, 0, 1));  //9
	mesh->addVertex(ofPoint(phi, 0, -1));  //10
	mesh->addVertex(ofPoint(-phi, 0, -1)); //11

	//Using the long on X rectangle edge
	mesh->addTriangle(8, 10, 4);
	mesh->addTriangle(8, 10, 5);
	mesh->addTriangle(9, 11, 6);
	mesh->addTriangle(9, 11, 7);

	//Using the long on Y rectangle edge
	mesh->addTriangle(4, 6, 0);
	mesh->addTriangle(4, 6, 1);
	mesh->addTriangle(5, 7, 2);
	mesh->addTriangle(5, 7, 3);

	//Using the long on Y rectangle edge
	mesh->addTriangle(0, 2,8);
	mesh->addTriangle(0, 2,9);
	mesh->addTriangle(1, 3,10);
	mesh->addTriangle(1, 3,11);

	//Corners
	mesh->addTriangle(0, 4, 8);
	mesh->addTriangle(0, 6, 9);
	mesh->addTriangle(1, 4, 10);
	mesh->addTriangle(1, 6, 11);
 
	mesh->addTriangle(2, 5, 8);
	mesh->addTriangle(2, 7, 9);
	mesh->addTriangle(3, 5, 10);
	mesh->addTriangle(3, 7, 11);



	return mesh;

}

ofMesh* Shapes::createCube()
{
	return createHexahedron();
}

ofMesh* Shapes::createSphere()
{
	throw std::runtime_error("Not yet implemented");
}



