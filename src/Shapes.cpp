#include "Shapes.h"
///@Todo: Make sure all shapes have a diameter of 1

Shapes::Shapes()
{
}

Shapes::~Shapes()
{
}

of3dPrimitive * Shapes::createTetrahedron()
{
	of3dPrimitive* primitive3d = new of3dPrimitive();
	primitive3d->getMesh().setMode(OF_PRIMITIVE_TRIANGLES);
	primitive3d->getMesh().enableIndices();

	primitive3d->getMesh().addVertex(ofPoint(0.5, 0, -(1.0 / (2.0*sqrt(2)))));
	primitive3d->getMesh().addVertex(ofPoint(-0.5, 0, -(1.0 / (2.0*sqrt(2)))));
	primitive3d->getMesh().addVertex(ofPoint(0, 0.5, (1.0 / (2.0*sqrt(2)))));
	primitive3d->getMesh().addVertex(ofPoint(0, -0.5, (1.0 / (2.0*sqrt(2)))));

	primitive3d->getMesh().addTriangle(0, 1, 2);
	primitive3d->getMesh().addTriangle(0, 1, 3);
	primitive3d->getMesh().addTriangle(0, 2, 3);
	primitive3d->getMesh().addTriangle(1, 2, 3);

	calculateNormals(primitive3d);

	return primitive3d;
}

of3dPrimitive * Shapes::createHexahedron()
{
	of3dPrimitive* primitive3d = new of3dPrimitive();
	//Top vertices
	primitive3d->getMesh().addVertex(ofPoint(-0.5, -0.5, -0.5));// indice 0
	primitive3d->getMesh().addVertex(ofPoint(0.5, -0.5, -0.5));// indice 1
	primitive3d->getMesh().addVertex(ofPoint(-0.5, -0.5, 0.5));// indice 2
	primitive3d->getMesh().addVertex(ofPoint(0.5, -0.5, 0.5));// indice 3

	//Bottom vertices
	primitive3d->getMesh().addVertex(ofPoint(-0.5, 0.5, -0.5));// indice 4
	primitive3d->getMesh().addVertex(ofPoint(0.5, 0.5, -0.5));// indice 5
	primitive3d->getMesh().addVertex(ofPoint(-0.5, 0.5, 0.5));// indice 6
	primitive3d->getMesh().addVertex(ofPoint(0.5, 0.5, 0.5));// indice 7

	//Top Face
	primitive3d->getMesh().addTriangle(0, 1, 2); //indice 0
	primitive3d->getMesh().addTriangle(3, 2, 1);// indice 1

	//Bottom Face
	primitive3d->getMesh().addTriangle(4, 5, 6);//indice 2
	primitive3d->getMesh().addTriangle(7, 5, 6);// indice 3

	//Left face
	primitive3d->getMesh().addTriangle(0, 2, 4);// indice 4
	primitive3d->getMesh().addTriangle(6, 2, 4);//indice 5

	//Right face
	primitive3d->getMesh().addTriangle(1, 3, 5);// indice 6
	primitive3d->getMesh().addTriangle(7, 3, 5);//indice 7

	//Front face
	primitive3d->getMesh().addTriangle(0, 1, 4);// indice 8
	primitive3d->getMesh().addTriangle(5, 1, 4);//indice 9

	//Back face
	primitive3d->getMesh().addTriangle(2, 3, 6);// indice 10
	primitive3d->getMesh().addTriangle(7, 3, 6);//indice 11

	calculateNormals(primitive3d);
	return primitive3d;
}

of3dPrimitive * Shapes::createOctahedron()
{
	of3dPrimitive* primitive3d = new of3dPrimitive();
	double root2over2 = sqrt(2) / 2.0;
	//Vertex top
	primitive3d->getMesh().addVertex(ofPoint(0, -root2over2, 0)); // Indice 0
	//Vertices middle
	primitive3d->getMesh().addVertex(ofPoint(root2over2, 0, 0));// Indice 1
	primitive3d->getMesh().addVertex(ofPoint(0, 0, root2over2));// Indice 2
	primitive3d->getMesh().addVertex(ofPoint(-root2over2, 0, 0));// Indice 3
	primitive3d->getMesh().addVertex(ofPoint(0, 0, -root2over2));// Indice 4
	//Vertex bottom
	primitive3d->getMesh().addVertex(ofPoint(0, root2over2, 0));// Indice 5

	//Top
	primitive3d->getMesh().addTriangle(0, 1, 2);
	primitive3d->getMesh().addTriangle(0, 2, 3);
	primitive3d->getMesh().addTriangle(0, 3, 4);
	primitive3d->getMesh().addTriangle(0, 4, 1);
	//Bottom
	primitive3d->getMesh().addTriangle(5, 1, 2);
	primitive3d->getMesh().addTriangle(5, 2, 3);
	primitive3d->getMesh().addTriangle(5, 3, 4);
	primitive3d->getMesh().addTriangle(5, 4, 1);

	calculateNormals(primitive3d);
	return primitive3d;
}

of3dPrimitive * Shapes::createDodecahedron()
{
	of3dPrimitive* primitive3d = new of3dPrimitive();
	double heightOfRoof = (sqrt(5) - 1) / 2.0; //0.618
	double size1 = (1 + heightOfRoof); // 1.618
	double size2 = (1 - heightOfRoof*heightOfRoof); //0.618

	primitive3d->getMesh().addVertex(ofPoint(0, size1, size2));  //0
	primitive3d->getMesh().addVertex(ofPoint(0, size1, -size2)); //1

	primitive3d->getMesh().addVertex(ofPoint(1, 1, 1));			//2
	primitive3d->getMesh().addVertex(ofPoint(1, 1, -1));			//3
	primitive3d->getMesh().addVertex(ofPoint(-1, 1, 1));			//4
	primitive3d->getMesh().addVertex(ofPoint(-1, 1, -1));		//5

	primitive3d->getMesh().addVertex(ofPoint(size1, size2, 0));	//6
	primitive3d->getMesh().addVertex(ofPoint(-size1, size2, 0));	//7

	primitive3d->getMesh().addVertex(ofPoint(size2, 0, size1));	 //8
	primitive3d->getMesh().addVertex(ofPoint(size2, 0, -size1));	 //9
	primitive3d->getMesh().addVertex(ofPoint(-size2, 0, size1));	 //10
	primitive3d->getMesh().addVertex(ofPoint(-size2, 0, -size1)); //11

	primitive3d->getMesh().addVertex(ofPoint(size1, -size2, 0));	 //12
	primitive3d->getMesh().addVertex(ofPoint(-size1, -size2, 0)); //13

	primitive3d->getMesh().addVertex(ofPoint(1, -1, 1));			 //14
	primitive3d->getMesh().addVertex(ofPoint(1, -1, -1));		 //15
	primitive3d->getMesh().addVertex(ofPoint(-1, -1, 1));		 //16
	primitive3d->getMesh().addVertex(ofPoint(-1, -1, -1));		 //17

	primitive3d->getMesh().addVertex(ofPoint(0, -size1, size2));	 //18
	primitive3d->getMesh().addVertex(ofPoint(0, -size1, -size2)); //19

	//Face 0, vertices 0,1,3,6,2
	primitive3d->getMesh().addTriangle(0, 1, 6);
	primitive3d->getMesh().addTriangle(0, 2, 6);
	primitive3d->getMesh().addTriangle(3, 1, 6);
	//Face 1, vertices 0,1,5,7,4
	primitive3d->getMesh().addTriangle(0, 1, 7);
	primitive3d->getMesh().addTriangle(0, 4, 7);
	primitive3d->getMesh().addTriangle(5, 1, 7);
	//Face 2, vertices 1,5,11,9,3
	primitive3d->getMesh().addTriangle(1, 5, 9);
	primitive3d->getMesh().addTriangle(1, 3, 9);
	primitive3d->getMesh().addTriangle(11, 5, 9);
	//Face 3, vertices 0,4,10,8,2
	primitive3d->getMesh().addTriangle(0, 4, 8);
	primitive3d->getMesh().addTriangle(0, 2, 8);
	primitive3d->getMesh().addTriangle(10, 4, 8);
	//Face 4, vertices 2,6,12,14,8
	primitive3d->getMesh().addTriangle(2, 6, 14);
	primitive3d->getMesh().addTriangle(2, 8, 14);
	primitive3d->getMesh().addTriangle(12, 6, 14);
	//Face 5, vertices 6,3,9,15,12
	primitive3d->getMesh().addTriangle(6, 3, 15);
	primitive3d->getMesh().addTriangle(6, 12, 15);
	primitive3d->getMesh().addTriangle(9, 3, 15);
	//Face 6, vertices 5,11,17,13,7
	primitive3d->getMesh().addTriangle(5, 11, 13);
	primitive3d->getMesh().addTriangle(5, 7, 13);
	primitive3d->getMesh().addTriangle(17, 11, 13);
	//Face 7, vertices 7,4,10,16,13  
	primitive3d->getMesh().addTriangle(7, 4, 16);
	primitive3d->getMesh().addTriangle(7, 13, 16);
	primitive3d->getMesh().addTriangle(10, 4, 16);
	//Face 8, vertices 19,17,11,9,15
	primitive3d->getMesh().addTriangle(19, 17, 9);
	primitive3d->getMesh().addTriangle(19, 15, 9);
	primitive3d->getMesh().addTriangle(11, 17, 9);
	//Face 9, vertices 18,16,10,8,14
	primitive3d->getMesh().addTriangle(18, 16, 8);
	primitive3d->getMesh().addTriangle(18, 14, 8);
	primitive3d->getMesh().addTriangle(10, 16, 8);
	//Face 10, vertices 18,19,15,12,14
	primitive3d->getMesh().addTriangle(18, 19, 12);
	primitive3d->getMesh().addTriangle(18, 14, 12);
	primitive3d->getMesh().addTriangle(15, 19, 12);
	//Face 11, vertices 18,19,17,13,16
	primitive3d->getMesh().addTriangle(18, 19, 13);
	primitive3d->getMesh().addTriangle(18, 16, 13);
	primitive3d->getMesh().addTriangle(17, 19, 13);

	calculateNormals(primitive3d);
	return primitive3d;
}

of3dPrimitive * Shapes::createIcosahedron()
{
	of3dPrimitive* primitive3d = new of3dPrimitive();
	double phi = ((sqrt(5) + 1) / 2.0);

	//See https://en.wikipedia.org/wiki/Regular_icosahedron#/media/File:Icosahedron-golden-rectangles.svg
	// But flipped horizontally

	//Long on z rectangle
	primitive3d->getMesh().addVertex(ofPoint(0, 1, phi));  //0
	primitive3d->getMesh().addVertex(ofPoint(0, 1, -phi)); //1
	primitive3d->getMesh().addVertex(ofPoint(0, -1, phi)); //2
	primitive3d->getMesh().addVertex(ofPoint(0, -1, -phi));//3

	//Long on y rectangle
	primitive3d->getMesh().addVertex(ofPoint(1, phi, 0));   //4
	primitive3d->getMesh().addVertex(ofPoint(1, -phi, 0));  //5
	primitive3d->getMesh().addVertex(ofPoint(-1, phi, 0));  //6
	primitive3d->getMesh().addVertex(ofPoint(-1, -phi, 0)); //7

	//Long on x renctangle
	primitive3d->getMesh().addVertex(ofPoint(phi, 0, 1));   //8
	primitive3d->getMesh().addVertex(ofPoint(-phi, 0, 1));  //9
	primitive3d->getMesh().addVertex(ofPoint(phi, 0, -1));  //10
	primitive3d->getMesh().addVertex(ofPoint(-phi, 0, -1)); //11

	//Using the long on X rectangle edge
	primitive3d->getMesh().addTriangle(8, 10, 4);
	primitive3d->getMesh().addTriangle(8, 10, 5);
	primitive3d->getMesh().addTriangle(9, 11, 6);
	primitive3d->getMesh().addTriangle(9, 11, 7);

	//Using the long on Y rectangle edge
	primitive3d->getMesh().addTriangle(4, 6, 0);
	primitive3d->getMesh().addTriangle(4, 6, 1);
	primitive3d->getMesh().addTriangle(5, 7, 2);
	primitive3d->getMesh().addTriangle(5, 7, 3);

	//Using the long on Y rectangle edge
	primitive3d->getMesh().addTriangle(0, 2, 8);
	primitive3d->getMesh().addTriangle(0, 2, 9);
	primitive3d->getMesh().addTriangle(1, 3, 10);
	primitive3d->getMesh().addTriangle(1, 3, 11);

	//Corners
	primitive3d->getMesh().addTriangle(0, 4, 8);
	primitive3d->getMesh().addTriangle(0, 6, 9);
	primitive3d->getMesh().addTriangle(1, 4, 10);
	primitive3d->getMesh().addTriangle(1, 6, 11);

	primitive3d->getMesh().addTriangle(2, 5, 8);
	primitive3d->getMesh().addTriangle(2, 7, 9);
	primitive3d->getMesh().addTriangle(3, 5, 10);
	primitive3d->getMesh().addTriangle(3, 7, 11);


	calculateNormals(primitive3d);

	return primitive3d;

}

of3dPrimitive* Shapes::createCube()
{
	return createHexahedron();
}

of3dPrimitive* Shapes::createSphere()
{
	throw std::runtime_error("Not yet implemented");
}
//Based on https://github.com/ofZach/ofxMeshUtils/blob/master/src/ofxMeshUtils.cpp#L32-L58
void Shapes::calculateNormals(of3dPrimitive* _3dprimitive)
{
    ofMesh* mesh = _3dprimitive->getMeshPtr();
    //mesh->addNormals(mesh->getFaceNormals(true));
    for (int i = 0; i < mesh->getVertices().size(); i++)
    {
        mesh->addNormal(ofPoint(0, 0, 0));
    }

    for (int i = 0; i < mesh->getIndices().size(); i += 3)
    {
        const int indexA = mesh->getIndices()[i];
        const int indexB = mesh->getIndices()[i + 1];
        const int indexC = mesh->getIndices()[i + 2];


        /*ofVec3f vertex1 = mesh->getVertices()[indexA];
        ofVec3f vertex2 = mesh->getVertices()[indexB];
        ofVec3f vertex3 = mesh->getVertices()[indexC];
        ofVec3f vertexCentre = (vertex1 + vertex2 + vertex3) / 3;
*/
        ofVec3f edge1 = mesh->getVertices()[indexA] - mesh->getVertices()[indexB];
        ofVec3f edge2 = mesh->getVertices()[indexC] - mesh->getVertices()[indexB];
        ofVec3f normal = edge2.cross(edge1);

        /*float additiveDistance = (vertexCentre.operator+(normal.scale(0.01f))).distance(ofVec3f(0));
        float sustractiveDistance = (vertexCentre.operator-(normal.scale(0.01f))).distance(ofVec3f(0));
        /*if (additiveDistance < sustractiveDistance )
        {
            normal = -normal;
        }*/
        // depending on your clockwise / winding order, you might want to reverse the e2 / e1 above if your normals are flipped.

        mesh->getNormals()[indexA] += normal;
        mesh->getNormals()[indexB] += normal;
        mesh->getNormals()[indexC] += normal;
    }

    for (int i = 0; i < mesh->getNormals().size(); i++)
    {
        mesh->getNormals()[i].normalize();
    }

    /*for each (ofMeshFace face in mesh->getUniqueFaces())
    {
        ofVec3f edge1 = face.getVertex(0) - face.getVertex(1);
        ofVec3f edge2 = face.getVertex(1) - face.getVertex(1);
        ofVec3f normal = edge2.cross(edge1);
        float additiveDistance = (face.getVertex(0) - normal.scale(0.01f)).distance(ofVec3f(0));
        float sustractiveDistance = (face.getVertex(0) - normal.scale(0.01f)).distance(ofVec3f(0));
        if (additiveDistance < sustractiveDistance)
        {
            normal = -normal;
        }
        face.setNormal(0, face.getNormal(0) + normal);
        face.setNormal(1, face.getNormal(1) + normal);
        face.setNormal(2, face.getNormal(2) + normal);
    }*/
}





