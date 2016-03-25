#pragma once
#include "../Shape2D.h"

class Object2D : public Shape2D, public ofMatrix4x4
{
public:
    enum Shape{Rectangle, Triangle, Ellipse};

    Object2D();
    Object2D(const Shape & shape);

	~Object2D();
	void AddTranslation(ofVec3f _draggedPixelVector);

	void AddRotation(ofVec3f _draggedPixelVector, int _axis);

	void AddScale(bool _zoomIn);

private:

	// Inherited via Shape2D
	
    virtual void Create(int x1, int y1, int width, int height) = 0;
    virtual bool DoesRectangleOverlap(int x1, int y1, int x2, int y2) =0;
    virtual void drawShape()=0;
    virtual void refreshPoints()=0;

protected:

    ofMatrix4x4 getFinalTransformationMatrix();
    ofPoint getWorldPosition(ofVec3f _point);
};
