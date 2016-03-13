#pragma once
#ifndef SHAPE_H
#define SHAPE_H
#include "ofMain.h"
#include <climits>
class Shape
{
public:

    void SetSelected(bool isSelected) { shouldShowBorders = isSelected; }
    bool GetSelected() { return shouldShowBorders; }
    virtual void        Draw() = 0;
    virtual bool        IsPointWithinBounds(int x, int y) = 0;


protected:
    bool        shouldShowBorders = false;
};

#endif // SHAPE_H
