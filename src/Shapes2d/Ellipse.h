#ifndef ELLIPSE_H
#define ELLIPSE_H
#include "Rectangle2D.h"
namespace Shapes2d
{
    class Ellipse : public Rectangle2D
	{
    public:
        Ellipse();
        //void        Draw();
    private:
        void drawShape();
    };
}
#endif // ELLIPSE_H
