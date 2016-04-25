#include "TransformableObject.h"
#include "Structure.h"

void TransformableObject::AddTranslation(int x, int y, ofVec3f _draggedPixelVector)
{
	ofVec3f vec = getWorldPosition(_draggedPixelVector);
	this->setTranslation(vec + this->getTranslation());
}

void TransformableObject::AddRotation(ofVec3f _draggedPixelVector, int _axis)
{
	this->GetCentre();
	float length = _draggedPixelVector.length();
	/*if (abs(_draggedPixelVector.x) < abs(_draggedPixelVector.y))
	{
	if (_draggedPixelVector.y < 0)
	{
	length *= -1;
	}
	}
	else
	{
	if (_draggedPixelVector.x < 0)
	{
	length *= -1;
	}
	}*/
	length = _draggedPixelVector.x + _draggedPixelVector.y;
	double angle = atan((length / ofGetWindowWidth())) * 180 / M_PI;
	float a, x, y, z;
	if (_axis == 0) // x
	{
		this->glRotate(angle, 1, 0, 0);
	}
	else if (_axis == 1) //y
	{
		this->glRotate(angle, 0, 1, 0);
	}
	else //z
	{
		this->glRotate(angle, 0, 0, 1);
	}
}

void TransformableObject::AddScale(bool _zoomIn)
{
	if (_zoomIn)
	{
		this->preMultScale(ofVec3f(1.1));
	}
	else
	{
		this->preMultScale(ofVec3f((1 / 1.1)));
	}

}



bool TransformableObject::IsPointWithinBounds(float x, float y)
{
	//return this->boundingBox->
	//@Todo IMPLEMENT IT
	auto vertices = this->boundingBox->getMesh().getVertices();
	ofPoint vertice1 = vertices.front();
	ofPoint vertice2;
	float distanceMax = 0;
	for (ofPoint vertice : vertices)
	{
		if (vertice1.distance(vertice) > distanceMax)
		{
			vertice2 = vertice;
			distanceMax = vertice1.distance(vertice);
		}
	}
	ofPoint screenPoint1 = getScreenPosition(vertice1);
	ofPoint screenPoint2 = getScreenPosition(vertice2);
	float distanceScreen = screenPoint1.distance(screenPoint2);

	ofPoint screenPoint=  getScreenPosition(this->GetCentre());
	float distanceClic = screenPoint.distance(ofPoint(x, y));
	if (distanceClic*0.5 < distanceScreen)
	{
		return true;
	}
	return false;
}

//http://webglfactory.blogspot.ca/2011/05/how-to-convert-world-to-screen.html
ofPoint TransformableObject::getScreenPosition(ofVec3f _point)
{
	ofVec3f point = this->getFinalTransformationMatrix().preMult(_point);
	ofVec3f point2 = this->getFinalTransformationMatrix().postMult(_point);

	return point;
	//int winX = round(((point.x + 1) / 2.0) * ofGetWindowWidth());
	////we calculate -point3D.getY() because the screen Y axis is
	////oriented top->down 
	//int winY = round(((1 - point.y) / 2.0) * ofGetWindowHeight());
	//return ofPoint(winX, winY);
}

//http://webglfactory.blogspot.ca/2011/05/how-to-convert-world-to-screen.html
ofPoint TransformableObject::getWorldPosition(ofVec3f _point)
{
	ofVec3f point = this->parent->GetFinalTransformationMatrix().getInverse().preMult(_point);
	ofVec3f point2 = this->parent->GetFinalTransformationMatrix().getInverse().postMult(_point);

	return point;
	//int winX = round(((point.x + 1) / 2.0) * ofGetWindowWidth());
	////we calculate -point3D.getY() because the screen Y axis is
	////oriented top->down 
	//int winY = round(((1 - point.y) / 2.0) * ofGetWindowHeight());
	//return ofPoint(winX, winY);
}

ofMatrix4x4 TransformableObject::getFinalTransformationMatrix()
{
	ofMatrix4x4 matrix = this->getInverse().getInverse(); // I don't know how to get the matrix.
	if (this->parent != NULL)
	{
		matrix = matrix * (this->parent->GetFinalTransformationMatrix());
	}
	return matrix;
}

void TransformableObject::applyTransformationMatrix()
{
	ofVec3f translation;
	ofQuaternion rotation;
	ofVec3f scale;
	ofQuaternion so;
	this->getFinalTransformationMatrix().decompose(translation, rotation, scale, so);
	float f;
	ofVec3f v;
	rotation.getRotate(f, v);
	ofTranslate(translation);
	ofScale(scale.x, scale.y, scale.z);
	ofRotate(f, v.x, v.y, v.z);

}

TransformableObject::TransformableObject()
{
	this->boundingBox = new ofBoxPrimitive();
}

TransformableObject::~TransformableObject()
{
}

ofVec3f TransformableObject::GetCentre()
{
	return this->boundingBox->getPosition()+ofVec3f(this->boundingBox->getWidth()*0.5, this->boundingBox->getHeight()*0.5, this->boundingBox->getDepth()*0.5);
}

void TransformableObject::setBondingCube(ofMesh* _mesh)
{
	float maxX = 0;
	float maxY = 0;
	float maxZ = 0;
	float minX = 0;
	float minY = 0;
	float minZ = 0;
	if (_mesh != NULL)
	{
		maxX = _mesh->getVertex(0).x;
		maxY = _mesh->getVertex(0).y;
		maxZ = _mesh->getVertex(0).z;
		minX = _mesh->getVertex(0).x;
		minY = _mesh->getVertex(0).y;
		minZ = _mesh->getVertex(0).z;

		for (ofVec3f v : _mesh->getVertices())
		{
			maxX = max(maxX, v.x);
			maxY = max(maxY, v.y);
			maxZ = max(maxZ, v.z);

			minX = min(minX, v.x);
			minY = min(minY, v.y);
			minZ = min(minZ, v.z);
		}

		this->boundingBox->setPosition(minX, minY, minZ);
		this->boundingBox->set(maxX - minX, maxY - minY, maxZ - minZ);
	}

}
