#pragma once

#ifdef _WIN32
#define M_PI PI
#endif

#include "Shape.h"
class Structure;

class Object3D : public Shape, public ofMatrix4x4
{
public:
	Object3D();
	Object3D(ofMesh* _mesh);
	~Object3D();

	void LoadObject(ofMesh* _mesh);

	void SetParent(Structure* _parent);

	// Inherited via Shape
	ofPoint * TopLeftPoint();

	ofPoint * TopRightPoint();

	ofPoint * BottomLeftPoint();

	ofPoint * BottomRightPoint();

	bool IsPointWithinBounds(int x, int y);

	bool DoesRectangleOverlap(int x1, int y1, int x2, int y2);

	void AffectVector(int x, int y, ofVec3f * actionVector, bool isRotation = false);

	void SetSelected(bool isSelected);

	bool GetSelected();

	void Draw();
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


	bool        isPointInsideRectangle(int x, int y, const ofRectangle & rectangle);

	Structure* parent;

	ofMatrix4x4 getFinalTransformationMatrix();
	
	float minX, maxX, minY, maxY, minZ, maxZ;
	void setBondingCube();
};