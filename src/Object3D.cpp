#include "Object3D.h"
#include "Structure.h"

Object3D::Object3D() : ofMatrix4x4()
{
	this->topLeftFrontPoint = ofVec3f(0, 0, 0);
	this->topRightFrontPoint = ofVec3f(0, 0, 0);
	this->bottomLeftFrontPoint = ofVec3f(0, 0, 0);
	this->bottomRightFrontPoint = ofVec3f(0, 0, 0);
	this->topLeftBackPoint = ofVec3f(0, 0, 0);
	this->topRightBackPoint = ofVec3f(0, 0, 0);
	this->bottomLeftBackPoint = ofVec3f(0, 0, 0);
	this->bottomRightBackPoint = ofVec3f(0, 0, 0);
	this->parent = NULL;

	refreshBorders();
}

Object3D::Object3D(ofMesh* _mesh) : Object3D()
{
	LoadObject(_mesh);
}

Object3D::~Object3D()
{
}

void Object3D::LoadObject(ofMesh * _mesh)
{
	this->object = _mesh;


	refreshBorders();
}

void Object3D::SetParent(Structure * _parent)
{
	this->parent = _parent;
}

ofVec3f Object3D::GetCentre()
{
	return (this->topLeftFrontPoint + this->bottomRightBackPoint)*0.5;
}

ofPoint * Object3D::TopLeftPoint()
{
	setBondingCube();
	return &topLeftPoint;
}

ofPoint * Object3D::TopRightPoint()
{
	setBondingCube();
	return &topRightPoint;
}

ofPoint * Object3D::BottomLeftPoint()
{
	setBondingCube();
	return &bottomLeftPoint;;
}

ofPoint * Object3D::BottomRightPoint()
{
	setBondingCube();
	return &bottomRightPoint;
}

bool Object3D::IsPointWithinBounds(int x, int y)
{
	setBondingCube();
	return isPointInsideRectangle(x, y, ofRectangle(topLeftPoint, bottomRightPoint));
}

bool Object3D::DoesRectangleOverlap(int x1, int y1, int x2, int y2)
{//TODO: this wont work if the selection rectangle goes trough inside teh shape and parallel to 2 sides of the shape
	setBondingCube();
	bool output = false;

	ofPoint * p1 = new ofPoint();
	ofPoint * p2 = new ofPoint();
	ofPoint * p3 = new ofPoint();
	ofPoint * p4 = new ofPoint();

	ofPoint * p5 = new ofPoint();
	ofPoint * p6 = new ofPoint();

	Shape::translatePoint(topLeftPoint.x, topLeftPoint.y, angleOffset - 360, p5);

	ofRectangle * boundingBox = new ofRectangle(topLeftPoint.x, topLeftPoint.y, topRightPoint.x - topLeftPoint.x, bottomLeftPoint.y - topLeftPoint.y);


	Shape::translatePoint((x1 - xOffset), (y1 - yOffset), 360 - angleOffset, p1);
	Shape::translatePoint((x2 - xOffset), (y1 - yOffset), 360 - angleOffset, p2);
	Shape::translatePoint((x1 - xOffset), (y2 - yOffset), 360 - angleOffset, p3);
	Shape::translatePoint((x2 - xOffset), (y2 - yOffset), 360 - angleOffset, p4);

	ofRectangle * selectionBox = new ofRectangle(x1, y1, x2 - x1, y2 - y1);

	output = Shape::DoEdgesIntersect(*p1, *p2, topLeftPoint, topRightPoint) ||
		Shape::DoEdgesIntersect(*p1, *p2, topLeftPoint, bottomLeftPoint) ||
		Shape::DoEdgesIntersect(*p1, *p2, bottomLeftPoint, bottomRightPoint) ||
		Shape::DoEdgesIntersect(*p1, *p2, topRightPoint, bottomRightPoint) ||

		Shape::DoEdgesIntersect(*p3, *p4, topLeftPoint, topRightPoint) ||
		Shape::DoEdgesIntersect(*p3, *p4, topLeftPoint, bottomLeftPoint) ||
		Shape::DoEdgesIntersect(*p3, *p4, bottomLeftPoint, bottomRightPoint) ||
		Shape::DoEdgesIntersect(*p3, *p4, topRightPoint, bottomRightPoint) ||

		isPointInsideRectangle(x1, y1, *boundingBox) ||
		isPointInsideRectangle(x2, y2, *boundingBox) ||

		(p5->x >= selectionBox->x && p5->x <= selectionBox->x + selectionBox->width &&
			p5->y >= selectionBox->y && p5->y <= selectionBox->y + selectionBox->height);

	/*isPointInsideRectangle(p5->x - xOffset - xOffset, p5->y - yOffset - yOffset, *selectionBox) ||
	isPointInsideRectangle(bottomRightPoint.x, bottomRightPoint.y, *selectionBox);*/

	delete p1;
	delete p2;
	delete p3;
	delete p4;
	delete boundingBox;
	delete selectionBox;

	return output;
}

void Object3D::AffectVector(int x, int y, ofVec3f * actionVector, bool isRotation)
{
	setBondingCube();
	if (isRotation)
	{
		double side = (double) (x - xOffset - topLeftPoint.x);
		double adj = (double) (y - yOffset - topLeftPoint.y);

		double currentAngle = atan((adj / side)) * 180 / M_PI;


		if (referenceAngleOffset <= 0)
		{
			referenceAngleOffset = currentAngle;
			if (side < 0)
			{
				referenceAngleOffset += 180;
			}
			angleOffset -= referenceAngleOffset;
		}

		if (side < 0)
		{
			currentAngle = currentAngle - 180;
		}
		angleOffset += currentAngle - prevAngle;

		prevAngle = currentAngle;

		angleOffset = fmod(angleOffset, 360);
		//this->glRotate(angleOffset, 0, 0, 1);
	}
	else
	{
		prevAngle = referenceAngleOffset = 0;
		if (isPointInsideRectangle(x, y, horizontalBorder1))
		{
			topLeftPoint.y += actionVector->y;
			topRightPoint.y += actionVector->y;
		}
		else if (isPointInsideRectangle(x, y, horizontalBorder2))
		{
			bottomLeftPoint.y += actionVector->y;
			bottomRightPoint.y += actionVector->y;
		}
		else if (isPointInsideRectangle(x, y, verticalBorder1))
		{
			topLeftPoint.x += actionVector->x;
			bottomLeftPoint.x += actionVector->x;
		}
		else if (isPointInsideRectangle(x, y, verticalBorder2))
		{
			topRightPoint.x += actionVector->x;
			bottomRightPoint.x += actionVector->x;
		}
		else
		{//Not trying to resize

			ofVec3f translation;
			ofQuaternion rotation;
			ofVec3f scale;
			ofQuaternion so;
			this->getFinalTransformationMatrix().decompose(translation, rotation, scale, so);
			xOffset += actionVector->x;
			yOffset += actionVector->y;
			translation += getWorldPosition(ofVec2f(xOffset, yOffset));
			this->setTranslation(translation);
			//this->glTranslate(xOffset, yOffset, 0);
		}
		refreshBorders();
	}
}


void Object3D::SetSelected(bool isSelected)
{
	this->shouldShowBorders = isSelected;
}

bool Object3D::GetSelected()
{
	return this->shouldShowBorders;
}
void Object3D::Draw()
{
	setBondingCube();
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

	//ofRotate(rot)
	ofSetColor(255);
	this->object->draw();
	ofPopMatrix();
	if (shouldShowBorders)
	{
		ofFill();
		ofSetColor(ofColor::grey);
		ofDrawRectangle(horizontalBorder1);
		ofDrawRectangle(horizontalBorder2);
		ofDrawRectangle(verticalBorder1);
		ofDrawRectangle(verticalBorder2);
	}
}

bool Object3D::isPointInsideRectangle(int x, int y, const ofRectangle & rectangle)
{
	ofPoint * translated = new ofPoint();
	Shape::translatePoint((x - xOffset), (y - yOffset), 360 - angleOffset, translated);
	bool output = translated->x >= rectangle.getX() && translated->x <= rectangle.getX() + rectangle.getWidth() &&
		translated->y >= rectangle.getY() && translated->y <= rectangle.getY() + rectangle.getHeight();
	delete translated;

	return output;
}

ofMatrix4x4 Object3D::getFinalTransformationMatrix()
{
	ofMatrix4x4 matrix = this->getInverse().getInverse(); // I don't know how to get the matrix.
	if (this->parent != NULL)
	{
		matrix = matrix * (this->parent->GetFinalTransformationMatrix());
	}
	return matrix;
}

void Object3D::setBondingCube()
{
	float maxX = this->object->getVertex(0).x;
	float maxY = this->object->getVertex(0).y;
	float maxZ = this->object->getVertex(0).z;
	float minX = this->object->getVertex(0).x;
	float minY = this->object->getVertex(0).y;
	float minZ = this->object->getVertex(0).z;

	for (ofVec3f v : this->object->getVertices())
	{
		maxX = max(maxX, v.x);
		maxY = max(maxY, v.y);
		maxZ = max(maxZ, v.z);

		minX = min(minX, v.x);
		minY = min(minY, v.y);
		minZ = min(minZ, v.z);
	}

	this->topLeftFrontPoint = getScreenPosition(ofVec3f(minX, minY, minZ));
	this->topRightFrontPoint = getScreenPosition(ofVec3f(maxX, minY, minZ));
	this->bottomLeftFrontPoint = getScreenPosition(ofVec3f(minX, maxY, minZ));
	this->bottomRightFrontPoint = getScreenPosition(ofVec3f(maxX, maxY, minZ));
	this->topLeftBackPoint = getScreenPosition(ofVec3f(minX, minY, maxZ));
	this->topRightBackPoint = getScreenPosition(ofVec3f(maxX, minY, maxZ));
	this->bottomLeftBackPoint = getScreenPosition(ofVec3f(minX, maxY, maxZ));
	this->bottomRightBackPoint = getScreenPosition(ofVec3f(maxX, maxY, maxZ));

	//ofEasyCam cam = ofEasyCam();
	//cam.setTransformMatrix(
	//	ofGetCurrentMatrix(ofMatrixMode::OF_MATRIX_PROJECTION));
	//this->topLeftFrontPoint = cam.worldToScreen(ofVec3f(minX, minY, minZ));
	//this->topRightFrontPoint = cam.worldToScreen(ofVec3f(maxX, minY, minZ));
	//this->bottomLeftFrontPoint = cam.worldToScreen(ofVec3f(minX, maxY, minZ));
	//this->bottomRightFrontPoint = cam.worldToScreen(ofVec3f(maxX, maxY, minZ));
	//this->topLeftBackPoint = cam.worldToScreen(ofVec3f(minX, minY, maxZ));
	//this->topRightBackPoint = cam.worldToScreen(ofVec3f(maxX, minY, maxZ));
	//this->bottomLeftBackPoint = cam.worldToScreen(ofVec3f(minX, maxY, maxZ));
	//this->bottomRightBackPoint = cam.worldToScreen(ofVec3f(maxX, maxY, maxZ));


	minX = min(topRightBackPoint.x, topRightFrontPoint.x);
	minX = min(minX, bottomRightFrontPoint.x);
	minX = min(minX, bottomRightBackPoint.x);
	minX = min(minX, topLeftFrontPoint.x);
	minX = min(minX, topLeftBackPoint.x);
	minX = min(minX, bottomLeftFrontPoint.x);
	minX = min(minX, bottomLeftBackPoint.x);

	maxX = max(topRightBackPoint.x, topRightFrontPoint.x);
	maxX = max(maxX, bottomRightFrontPoint.x);
	maxX = max(maxX, bottomRightBackPoint.x);
	maxX = max(maxX, topLeftFrontPoint.x);
	maxX = max(maxX, topLeftBackPoint.x);
	maxX = max(maxX, bottomLeftFrontPoint.x);
	maxX = max(maxX, bottomLeftBackPoint.x);

	maxY = max(bottomLeftBackPoint.y, bottomLeftFrontPoint.y);
	maxY = max(maxY, bottomRightBackPoint.y);
	maxY = max(maxY, bottomRightFrontPoint.y);
	maxY = max(maxY, topLeftFrontPoint.y);
	maxY = max(maxY, topLeftBackPoint.y);
	maxY = max(maxY, topRightBackPoint.y);
	maxY = max(maxY, topRightFrontPoint.y);

	minY = min(bottomLeftBackPoint.y, bottomLeftFrontPoint.y);
	minY = min(minY, bottomRightBackPoint.y);
	minY = min(minY, bottomRightFrontPoint.y);
	minY = min(minY, topLeftFrontPoint.y);
	minY = min(minY, topLeftBackPoint.y);
	minY = min(minY, topRightBackPoint.y);
	minY = min(minY, topRightFrontPoint.y);



	this->topLeftPoint = ofVec3f(minX, minY);
	this->topRightPoint = ofVec3f(maxX, minY);
	this->bottomLeftPoint = ofVec3f(minX, maxY);
	this->bottomRightPoint = ofVec3f(maxX, maxY);

	refreshBorders();
}

void Object3D::AddTranslation(ofVec3f _draggedPixelVector)
{
	ofVec3f vec = getWorldPosition(_draggedPixelVector);
	this->setTranslation(vec + this->getTranslation());
}

void Object3D::AddRotation(ofVec3f _draggedPixelVector, int _axis)
{
	this->GetCentre();
	float length = _draggedPixelVector.length();
	if (abs(_draggedPixelVector.x) < abs(_draggedPixelVector.y))
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
	}
	double angle = atan((_draggedPixelVector.length() / ofGetWindowWidth())) * 180 / M_PI;
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

void Object3D::AddScale(bool _zoomIn)
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


//http://webglfactory.blogspot.ca/2011/05/how-to-convert-world-to-screen.html
ofPoint Object3D::getScreenPosition(ofVec3f _point)
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
ofPoint Object3D::getWorldPosition(ofVec3f _point)
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

void Object3D::refreshBorders()
{
	horizontalBorder1.set(topLeftPoint.x, topLeftPoint.y, topRightPoint.x - topLeftPoint.x, borderSize);
	horizontalBorder2.set(topLeftPoint.x, bottomLeftPoint.y - borderSize, bottomRightPoint.x - bottomLeftPoint.x, borderSize);
	verticalBorder1.set(topLeftPoint.x, topLeftPoint.y, borderSize, bottomLeftPoint.y - topLeftPoint.y);
	verticalBorder2.set(topRightPoint.x - borderSize, topRightPoint.y, borderSize, bottomRightPoint.y - topRightPoint.y);
}
