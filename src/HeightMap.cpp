#include "HeightMap.h"
//https://forum.openframeworks.cc/t/how-to-generate-meshes-models-from-points-in-fbo-image/18551

HeightMap::HeightMap()
{
	this->mesh = new ofMesh();
}

HeightMap::~HeightMap()
{
	delete this->mesh;
}

void HeightMap::Draw()
{
	ofPushMatrix();
	this->applyTransformationMatrix();
	this->mesh->draw();
	ofPopMatrix();
}

void HeightMap::Setup(ofImage* _image)
{
	float extrusion = 25.0;
	int w = _image->getWidth();
	int h = _image->getHeight();

	//Create the vertices
	for (int x = 0;x < w;x++)
	{
		for (int y = 0; y < h; y++)
		{
			int index = (x*w) + y;
			ofFloatColor col(_image->getColor(x, y));
			this->mesh->addVertex(ofVec3f(x, y, ofMap(col.getBrightness(), 0, 1.0, 0, extrusion)));
			this->mesh->addColor(col.getBrightness());
		}
	}

	//Create the triangles
	for (int y = 0; y<h - 1; y++)
	{
		for (int x = 0; x<w - 1; x++)
		{
			mesh->addIndex(x + y* w);               // 0
			mesh->addIndex((x + 1) + y* w);           // 1
			mesh->addIndex(x + (y + 1)* w);           // 10
				
			mesh->addIndex((x + 1) + y* w);           // 1
			mesh->addIndex((x + 1) + (y + 1)* w);       // 11
			mesh->addIndex(x + (y + 1)* w);           // 10
				
		}
	}
}
