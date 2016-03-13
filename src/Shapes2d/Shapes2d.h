#ifndef SHAPES2D_H
#define SHAPES2D_H
#include "../Shape.h"

class Shapes2d: public Shape
{
public:
    virtual void Create(int x1, int y1, int width, int height) = 0;
protected:
};

#endif // SHAPES2D_H
