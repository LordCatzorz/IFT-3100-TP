#include "Object3D.h"
#include "Structure.h"

Object3D::Object3D()
{
	this->parent = NULL;
	this->model = new ofxAssimpModelLoader();
}


Object3D::Object3D(string _path) : Object3D()
{
	loadModel(_path);
}

Object3D::~Object3D()
{
	delete model;
}

void Object3D::loadModel(string _path)
{
	this->model->loadModel(_path);
}


void Object3D::Draw()
{
	
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
	if (this->model->getMeshCount() > 0)
	{
		this->model->drawFaces();
	}
	ofPopMatrix();
	if (GetSelected())
	{
		this->parent->shadersManager->DisableShaders();
		ofFill();
		ofSetColor(ofColor::grey);
		this->boundingBox->drawWireframe();
		this->parent->shadersManager->EnableShaders();
	}
}
