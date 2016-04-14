#pragma once
#include "Shape.h"

class TransformableObject : public Shape, public ofMatrix4x4
{
public:
	TransformableObject();
	~TransformableObject();

	ofVec3f GetCentre();

	// Inherited via Shape
	void AddTranslation(ofVec3f _draggedPixelVector);

	void AddRotation(ofVec3f _draggedPixelVector, int _axis);

	void AddScale(bool _zoomIn);

	void Draw() =0;

	bool IsPointWithinBounds(float x, float y);

protected:
	void setBondingCube(ofMesh* _mesh);
	ofBoxPrimitive* boundingBox;
	ofMatrix4x4 getFinalTransformationMatrix();
	void applyTransformationMatrix();
private:


	ofPoint getScreenPosition(ofVec3f _point);
	ofPoint getWorldPosition(ofVec3f _point);


	int borderSize = 10;


};
