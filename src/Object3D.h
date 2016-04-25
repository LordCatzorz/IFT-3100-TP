#pragma once

#include "TransformableObject.h"
#include "ofxAssimpModelLoader.h"

class Object3D : public TransformableObject
{
public:
	Object3D();
	Object3D(string _path);
	~Object3D();

    void Draw();
private:
	void loadModel(string _path);

	int xOffset = 0, yOffset = 0;
	double      angleOffset = 0, referenceAngleOffset = 0, prevAngle = 0;
	bool        shouldShowBorders = false;
	ofxAssimpModelLoader* model;



};
