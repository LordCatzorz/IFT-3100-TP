#pragma once
#include "Shape.h"

class Structure;
class Shape3D : public Shape
{
public:
	virtual void AddTranslation(ofVec3f _draggedPixelVector) = 0;
	virtual void AddRotation(ofVec3f _draggedPixelVector, int _axis) = 0;
	virtual void AddScale(bool _zoomIn) = 0;
	virtual void Draw() = 0;
	void SetParent(Structure* _parent) { this->parent = _parent; };
protected:
	Structure* parent;



};