<<<<<<< HEAD
=======
#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "Shapes2d.h"

namespace Shapes2d
{
	class Rectangle : public Shapes2d
	{
	public:
		Rectangle();
		bool        IsPointWithinBounds(float x, float y);
		bool        DoesRectangleOverlap(int x1, int y1, int x2, int y2);
		void        AffectVector(int x, int y, ofVec3f * actionVector, bool isRotation = false);
		void        Draw();
		void        Create(int x1, int y1, int width, int height);
	protected:
		ofPoint     point1,
			point2,
			point3,
			point4;
		bool isPointInsideRectangle(int x, int y, const ofRectangle & rectangle);
		void refreshPoints();
	};
}
#endif // RECTANGLE_H
>>>>>>> d669d46d93e04f57c860b9fb0fc8747d691bd977
