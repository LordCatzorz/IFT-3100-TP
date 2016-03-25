#pragma once
#ifndef SHAPE_H
#define SHAPE_H
#include "ofMain.h"
#include <climits>
class Structure;
class Shape
{
public:

    void SetSelected(bool isSelected) { shouldShowBorders = isSelected; }
    bool GetSelected() { return shouldShowBorders; }
	virtual void AddTranslation(ofVec3f _draggedPixelVector) = 0;
	virtual void AddRotation(ofVec3f _draggedPixelVector, int _axis) = 0;
	virtual void AddScale(bool _zoomIn) = 0;
    virtual void        Draw() = 0;
    virtual bool		IsPointWithinBounds(float x, float y) = 0;
	void SetParent(Structure* _parent) { this->parent = _parent; };
protected:
    bool shouldShowBorders = false;
	Structure* parent;
};
#endif // SHAPE_H
