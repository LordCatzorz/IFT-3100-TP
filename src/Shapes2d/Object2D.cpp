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

double Object2D::determinant(const ofPoint & p1, const ofPoint & p2)
{
	return p1.x * p2.y - p1.y * p2.x;
}

void Object2D::notifyAttachedToParen(Object2D * parent)
{
	parentShape = parent;
	parentXOffset = xOffset - parent->xOffset;
	parentYOffset = yOffset - parent->yOffset;
}

ofMatrix4x4 Object2D::getFinalTransformationMatrix()
{
    ofMatrix4x4 matrix = this->getInverse().getInverse();
	if (this->parent != NULL)
	{
		matrix = matrix * (this->parent->GetFinalTransformationMatrix());
	}
	return matrix;
}

void Object2D::Create(int x1, int y1, int width, int height, bool isXInverted, bool isYInverted)
{
}

void Object2D::Draw()
{
	ofFill();
	ofSetColor(255);
	ofPushMatrix();
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


	ofSetColor(255, 0, 0, 255);
	drawShape();

	if (shapeHasBorders && shouldShowBorders)
	{
		ofFill();
		ofSetColor(borderColor);
		ofDrawRectangle(horizontalBorder1);
		ofDrawRectangle(horizontalBorder2);
		ofDrawRectangle(verticalBorder1);
		ofDrawRectangle(verticalBorder2);
	}
	ofPopMatrix();

}

bool Object2D::IsPointWithinBounds(float x, float y)
{
	return isPointInsideRectangle(x, y, ofRectangle(topLeftPoint, bottomRightPoint));
}

void Object2D::SetColor(ofColor * newColor)
{
	delete drawColor;
	drawColor = new ofColor();
	(*drawColor).r = newColor->r;
	(*drawColor).g = newColor->g;
	(*drawColor).b = newColor->b;
	(*drawColor).a = newColor->a;
	bool a = true;
}

Shape * Object2D::GetParent()
{
	return  parentShape;
}

void Object2D::AddChild(Object2D * child)
{
	if (child->parentShape == nullptr)
	{
		children.push_back(child);
		child->notifyAttachedToParen(this);
	}
}

void Object2D::RemoveChild(Object2D * child)
{
	for (std::vector<Object2D*>::iterator toDel = children.begin(); toDel != children.end(); toDel++)
	{
		if (*toDel == child)
		{
			(*toDel)->parentShape = nullptr;
			(*toDel)->xOffset = (*toDel)->parentXOffset + xOffset;
			(*toDel)->yOffset = (*toDel)->parentYOffset + yOffset;
            (*toDel)->SetSelected(false);
			children.erase(toDel);
			break;
		}
	}
}

void Object2D::ClearChildren()
{
	for (Object2D * toDel : children)
	{
		toDel->parentShape = nullptr;
		toDel->xOffset = toDel->parentXOffset + xOffset;
		toDel->yOffset = toDel->parentYOffset + yOffset;
		toDel->SetSelected(false);
		toDel->angleOffset += angleOffset;
	}
	children.clear();
}

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

int Object2D::getBlueVal()
{
	if (parentShape != nullptr)
		return parentShape->getBlueVal() - 10;
	else
		return 265;
}

void Object2D::refreshBorders()
{
	horizontalBorder1.set(topLeftPoint.x, topLeftPoint.y, topRightPoint.x - topLeftPoint.x, borderSize);
	horizontalBorder2.set(topLeftPoint.x, bottomLeftPoint.y - borderSize, bottomRightPoint.x - bottomLeftPoint.x, borderSize);
	verticalBorder1.set(topLeftPoint.x, topLeftPoint.y, borderSize, bottomLeftPoint.y - topLeftPoint.y);
	verticalBorder2.set(topRightPoint.x - borderSize, topRightPoint.y, borderSize, bottomRightPoint.y - topRightPoint.y);
}

ofPoint * Object2D::translatePoint(int x, int y, double angleInDegrees, ofPoint * translated)
{
	double angleRad = angleInDegrees * M_PI / 180;
	double px = cos(angleRad) * x - sin(angleRad) * y;
	double py = sin(angleRad) * x + cos(angleRad) * y;

	translated->set(px, py);

	return  translated;
}
bool Object2D::DoEdgesIntersect(const ofPoint & p1, const ofPoint & p2, const ofPoint & p3, const ofPoint & p4)
{
	bool output;
	ofPoint * p2p1 = new ofPoint();
	p2p1->set(p2.x - p1.x, p2.y - p1.y);
	ofPoint * p3p4 = new ofPoint();
	p3p4->set(p3.x - p4.x, p3.y - p4.y);
	ofPoint * p3p1 = new ofPoint();
	p3p1->set(p3.x - p1.x, p3.y - p1.y);

	double det = determinant(*p2p1, *p3p4);
	double t = determinant(*p3p1, *p3p4) / det;
	double u = determinant(*p2p1, *p3p1) / det;

	if ((t < 0) || (u < 0) || (t > 1) || (u > 1))
	{
		output = false;
	}
	else
	{
		output = true;
	}

	delete p2p1;
	delete p3p4;
	delete p3p1;

	return output;
}
bool Object2D::isPointInsideRectangle(int x, int y, const ofRectangle & rectangle)
{
	ofVec3f translation;
	ofQuaternion rotation;
	ofVec3f scale;
	ofQuaternion so;
	this->getFinalTransformationMatrix().decompose(translation, rotation, scale, so);

	ofPoint * traslated = new ofPoint();
	Object2D::translatePoint((x - translation.x), (y - translation.y), 360 - angleOffset, traslated);
	bool output = traslated->x >= rectangle.getX() && traslated->x <= rectangle.getX() + rectangle.getWidth() &&
		traslated->y >= rectangle.getY() && traslated->y <= rectangle.getY() + rectangle.getHeight();
	delete traslated;

	return output;

}
;
