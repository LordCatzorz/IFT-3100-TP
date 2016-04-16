#include "Object2D.h"
#include "Structure.h"

Object2D::Object2D()
{
	this->parent = NULL;
}

Object2D::~Object2D()
{
}

void Object2D::AddTranslation(int x, int y, ofVec3f _draggedPixelVector)
{
    ofVec3f vec = getWorldPosition(_draggedPixelVector);
    this->setTranslation(vec + this->getTranslation());
}

void Object2D::AddRotation(ofVec3f _draggedPixelVector, int _axis)
{
   // this->GetCentre();
    float length = _draggedPixelVector.length();
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
        this->glRotate(-angle, 0, 0, 1);
    }
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

/*bool Object2D::DoesRectangleOverlap(int x1, int y1, int x2, int y2)
{
	return false;
}*/

void Object2D::drawShape()
{
}

void Object2D::refreshPoints()
{
}

ofPoint Object2D::getWorldPosition(ofVec3f _point)
{

    ofVec3f point = this->parent->GetFinalTransformationMatrix().getInverse().preMult(_point);
    ofVec3f point2 = this->parent->GetFinalTransformationMatrix().getInverse().postMult(_point);

    return point;
}

