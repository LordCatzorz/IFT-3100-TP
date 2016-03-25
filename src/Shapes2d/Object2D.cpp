#include "Object2D.h"
#include "Structure.h"

Object2D::Object2D()
{
	this->parent = NULL;
}

Object2D::~Object2D()
{
}

void Object2D::AddTranslation(ofVec3f _draggedPixelVector)
{
}

void Object2D::AddRotation(ofVec3f _draggedPixelVector, int _axis)
{
}

void Object2D::AddScale(bool _zoomIn)
{
}

ofMatrix4x4 Object2D::getFinalTransformationMatrix()
{
	ofMatrix4x4 matrix = this->getInverse().getInverse(); // I don't know how to get the matrix.
	if (this->parent != NULL)
	{
		matrix = matrix * (this->parent->GetFinalTransformationMatrix());
	}
	return matrix;
}

void Object2D::Create(int x1, int y1, int width, int height)
{
}

bool Object2D::DoesRectangleOverlap(int x1, int y1, int x2, int y2)
{
	return false;
}

void Object2D::drawShape()
{
}

void Object2D::refreshPoints()
{
}
