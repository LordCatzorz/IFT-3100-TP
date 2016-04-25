#pragma once
#include "TransformableObject.h"

class HeightMap : public TransformableObject
{
public:
	HeightMap ();
	~HeightMap ();
	void Draw();
	void Setup(ofImage* _image);
private:
	ofMesh* mesh;
	
};
