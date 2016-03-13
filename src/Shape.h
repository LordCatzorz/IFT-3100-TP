#pragma once

#include "ofMain.h"
class Shape
{
public:

	void SetSelected(bool isSelected) { shouldShowBorders = isSelected; }
	bool GetSelected() { return shouldShowBorders; }
	virtual void        Draw() = 0;
	virtual bool		IsPointWithinBounds(float x, float y) = 0;
protected: 
	bool shouldShowBorders = false;
};