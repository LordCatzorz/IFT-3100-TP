#pragma once

#include "ofMain.h"
class Shape
{
public:
	virtual void        SetSelected(bool isSelected) = 0;
	virtual bool        GetSelected() = 0;
	virtual void        Draw() = 0;
	//virtual bool		IsPointWithinBounds(float x, float y) = 0;
};