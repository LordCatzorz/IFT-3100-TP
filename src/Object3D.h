#pragma once

#ifdef _WIN32
#define M_PI PI
#endif

#include "Shape3D.h"
#include "ofxAssimpModelLoader.h"

class Object3D : public Shape3D, public ofMatrix4x4
{
public:
	Object3D();
	Object3D(string _path);
	Object3D(ofMesh* _mesh);
	~Object3D();

	

	ofVec3f GetCentre();
	// Inherited via Shape3D
    void AddTranslation(int x, int y, ofVec3f _draggedPixelVector);
	void AddRotation(ofVec3f _draggedPixelVector, int _axis);
	void AddScale(bool _zoomIn);
	void Draw();
	bool IsPointWithinBounds(float x, float y);
private:
	void loadObject(ofMesh* _mesh);
	void loadModel(string _path);
	ofPoint getScreenPosition(ofVec3f _point);
	ofPoint getWorldPosition(ofVec3f _point);
	void refreshBorders();

	int         borderSize = 10, xOffset = 0, yOffset = 0;
	double      angleOffset = 0, referenceAngleOffset = 0, prevAngle = 0;
	bool        shouldShowBorders = false;
	ofMesh*     object;
	ofxAssimpModelLoader* model;
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


	ofMatrix4x4 getFinalTransformationMatrix();

	float minX, maxX, minY, maxY, minZ, maxZ;
	void setBondingCube();


};
