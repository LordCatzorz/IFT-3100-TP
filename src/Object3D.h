#pragma once

#ifdef _WIN32
#define M_PI PI
#endif

#include "Shape3D.h"
#include "Shape.h"
class Structure;

class Object3D : public Shape3D, public ofMatrix4x4
{
public:
	Object3D();
	Object3D(ofMesh* _mesh);
	~Object3D();

	void LoadObject(ofMesh* _mesh);

	void SetParent(Structure* _parent);
	ofVec3f GetCentre();
	// Inherited via Shape3D
	void AddTranslation(ofVec3f _draggedPixelVector);
	void AddRotation(ofVec3f _draggedPixelVector, int _axis);
	void AddScale(bool _zoomIn);
	void SetSelected(bool isSelected);
	bool GetSelected();
	void Draw();
	bool IsPointWithinBounds(float x, float y);
private:
	ofPoint getScreenPosition(ofVec3f _point);
	ofPoint getWorldPosition(ofVec3f _point);
	void refreshBorders();

	int         borderSize = 10, xOffset = 0, yOffset = 0;
	double      angleOffset = 0, referenceAngleOffset = 0, prevAngle = 0;
	bool        shouldShowBorders = false;
	ofMesh*     object;
	ofRectangle horizontalBorder1,
		horizontalBorder2,
		verticalBorder1,
		verticalBorder2;
	ofPoint
		topLeftFrontPoint,
		topRightFrontPoint,
		bottomLeftFrontPoint,
		bottomRightFrontPoint,
		topLeftBackPoint,
		topRightBackPoint,
		bottomLeftBackPoint,
		bottomRightBackPoint,
		topLeftPoint,
		topRightPoint,
		bottomLeftPoint,
		bottomRightPoint;


	Structure* parent;

	ofMatrix4x4 getFinalTransformationMatrix();

	float minX, maxX, minY, maxY, minZ, maxZ;
	void setBondingCube();


};