#pragma once
#include "Shape.h"

class Object2D : public Shape, public ofMatrix4x4
{
public:
    //enum Shape{Rectangle, Triangle, Ellipse};

    Object2D();
    //Object2D(const Shape & shape);

	~Object2D();

    ofPoint * TopLeftPoint() { return &topLeftPoint; }
    ofPoint * TopRightPoint() { return &topRightPoint; }
    ofPoint * BottomLeftPoint() { return &bottomLeftPoint; }
    ofPoint * BottomRightPoint() { return &bottomRightPoint; }

    virtual void Create(int x1, int y1, int width, int height, bool isXInverted = false, bool isYInverted = false) = 0;

    void AddTranslation(int x, int y, ofVec3f _draggedPixelVector);
    void AddRotation(ofVec3f _draggedPixelVector, int _axis);
    void AddScale(bool _zoomIn);

    void ActionStop(){currentAction = Action::Rest;}
	void Draw();
	bool IsPointWithinBounds(float x, float y);

	void SetColor(ofColor * newColor);
	Shape * GetParent();
	void AddChild(Object2D * child);
	void RemoveChild(Object2D * child);

	void ClearChildren();

private:

    // Inherited via Object2D
	
    //virtual void Create(int x1, int y1, int width, int height) = 0;
    //virtual bool DoesRectangleOverlap(int x1, int y1, int x2, int y2) =0;
    virtual void drawShape()=0;
    virtual void refreshPoints()=0;

	static double determinant(const ofPoint & p1, const ofPoint & p2);
	void notifyAttachedToParen(Object2D * parent);

protected:

    ofMatrix4x4 getFinalTransformationMatrix();
    ofPoint getWorldPosition(ofVec3f _point);

    int         borderSize = 10, xOffset = 0, yOffset = 0, parentXOffset = 0, parentYOffset = 0, redVal = 255, blueVal = 255;
    double      angleOffset = 0, referenceAngleOffset = 0, previousAngle = 0;
    ofRectangle horizontalBorder1,
        horizontalBorder2,
        verticalBorder1,
        verticalBorder2;
    ofPoint     topLeftPoint,
        topRightPoint,
        bottomLeftPoint,
        bottomRightPoint;

    ofColor *   drawColor = new ofColor(0,0,0);
    ofColor     borderColor = ofColor::gray;
    Object2D     * parentShape = nullptr;
    std::vector<Object2D*> children;

    bool shapeHasBorders = true;

    enum Action{Move, Resize, Rotate, Rest};
    Action currentAction = Action::Rest;
    int selectedResizeBar = -1;

	int getBlueVal();
	void refreshBorders();

	static ofPoint * translatePoint(int x, int y, double angleInDegrees, ofPoint * translated);

    /** Source: http://content.gpwiki.org/index.php/Polygon_Collision
     * @brief DoEdgesIntersect Determines whether 2 edges intersect
     * @param p1 First point of first edge
     * @param p2 Second point of first edge
     * @param p3 First point of second edge
     * @param p4 Second point of second edge
     * @return true if edges intersect
     */
	static bool DoEdgesIntersect(const ofPoint & p1, const ofPoint & p2, const ofPoint & p3, const ofPoint & p4);
   
	bool isPointInsideRectangle(int x, int y, const ofRectangle & rectangle);
};
