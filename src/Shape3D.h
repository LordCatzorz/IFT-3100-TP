#pragma once
#include "Shape.h"
class Shape3D : public Shape
{
public:
	virtual void AddTranslation(ofVec3f _draggedPixelVector) = 0;
	virtual void AddRotation(ofVec3f _draggedPixelVector, int _axis) = 0;
	virtual void AddScale(bool _zoomIn) = 0;
	virtual void SetSelected(bool isSelected) = 0;
	virtual bool GetSelected() = 0;
	virtual void Draw() = 0;
private:


	

};