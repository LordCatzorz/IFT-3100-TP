#include "Ellipse2D.h"

	Ellipse2D::Ellipse2D()
	{
		topLeftPoint.set(INT_MIN, INT_MIN);
		topRightPoint.set(INT_MIN, INT_MIN);
		bottomLeftPoint.set(INT_MIN, INT_MIN);
		bottomRightPoint.set(INT_MIN, INT_MIN);
	}

    void Ellipse2D::drawShape(){
        ofEllipse(point1.x + (int)((point2.x - point1.x) / 2), point1.y + (int)((point3.y - point1.y) / 2), point2.x - point1.x, point4.y - point2.y);
    }

