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

    virtual void Create(int x1, int y1, int width, int height) = 0;

    void AddTranslation(int x, int y, ofVec3f _draggedPixelVector);
    void AddRotation(ofVec3f _draggedPixelVector, int _axis);
    void AddScale(bool _zoomIn);

    void ActionStop(){currentAction = Action::Rest;}
    void Draw(){
        ofFill();
        ofSetColor(255);
        ofPushMatrix();
        ofVec3f translation;
        ofQuaternion rotation;
        ofVec3f scale;
        ofQuaternion so;
        this->getFinalTransformationMatrix().decompose(translation, rotation, scale, so);
        float f;
        ofVec3f v;
        rotation.getRotate(f, v);
        ofTranslate(translation);
        ofScale(scale.x, scale.y, scale.z);
        ofRotate(f, v.x, v.y, v.z);

        drawShape();

        if(shouldShowBorders){
            ofFill();
            ofSetColor(borderColor);
            ofDrawRectangle(horizontalBorder1);
            ofLog() << "rect1: (" << horizontalBorder1.x << ", " << horizontalBorder1.y << ") w: " << horizontalBorder1.width << " h: " << horizontalBorder1.height;
            ofDrawRectangle(horizontalBorder2);
            ofDrawRectangle(verticalBorder1);
            ofDrawRectangle(verticalBorder2);
        }
        ofPopMatrix();

    }
    bool IsPointWithinBounds(float x, float y){
        return isPointInsideRectangle(x, y, ofRectangle(topLeftPoint, bottomRightPoint));
    }

    void SetColor(ofColor * newColor){
        delete drawColor;
        drawColor = new ofColor();
        (*drawColor).r = newColor->r;
        (*drawColor).g = newColor->g;
        (*drawColor).b = newColor->b;
        (*drawColor).a = newColor->a;
        bool a = true;
    }
    Shape * GetParent(){ return  parentShape;}
    void AddChild(Object2D * child){
        if(child->parentShape == nullptr){
            children.push_back(child);
            child->notifyAttachedToParen(this);
        }
    }
    void RemoveChild(Object2D * child){
        for(std::vector<Object2D*>::iterator toDel = children.begin(); toDel != children.end(); toDel++){
            if(*toDel == child){
                (*toDel)->parentShape = nullptr;
                (*toDel)->xOffset = (*toDel)->parentXOffset + xOffset;
                (*toDel)->yOffset = (*toDel)->parentYOffset + yOffset;
                (*toDel)->SetSelected(false);
                //(*toDel)->angleOffset += angleOffset;
                children.erase(toDel);
                break;
            }
        }
    }

    void ClearChildren(){
        for(Object2D * toDel : children){
            toDel->parentShape = nullptr;
            toDel->xOffset = toDel->parentXOffset + xOffset;
            toDel->yOffset = toDel->parentYOffset + yOffset;
            toDel->SetSelected(false);
            toDel->angleOffset += angleOffset;
        }
        children.clear();
    }

private:

    // Inherited via Object2D
	
    //virtual void Create(int x1, int y1, int width, int height) = 0;
    //virtual bool DoesRectangleOverlap(int x1, int y1, int x2, int y2) =0;
    virtual void drawShape()=0;
    virtual void refreshPoints()=0;

    static double determinant(const ofPoint & p1, const ofPoint & p2){
        return p1.x * p2.y - p1.y * p2.x;
    }
    void notifyAttachedToParen(Object2D * parent){
        parentShape = parent;
        parentXOffset = xOffset - parent->xOffset;
        parentYOffset = yOffset - parent->yOffset;
    }

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

    enum Action{Move, Resize, Rotate, Rest};
    Action currentAction = Action::Rest;
    int selectedResizeBar = -1;

    int getBlueVal(){
        if(parentShape != nullptr)
            return parentShape->getBlueVal() - 10;
        else
            return 265;
    }
    void refreshBorders()
    {
        horizontalBorder1.set(topLeftPoint.x, topLeftPoint.y, topRightPoint.x - topLeftPoint.x, borderSize);
        horizontalBorder2.set(topLeftPoint.x, bottomLeftPoint.y - borderSize, bottomRightPoint.x - bottomLeftPoint.x, borderSize);
        verticalBorder1.set(topLeftPoint.x, topLeftPoint.y, borderSize, bottomLeftPoint.y - topLeftPoint.y);
        verticalBorder2.set(topRightPoint.x - borderSize, topRightPoint.y, borderSize, bottomRightPoint.y - topRightPoint.y);
    }

    static ofPoint * translatePoint(int x, int y, double angleInDegrees, ofPoint * translated)
    {
        double angleRad = angleInDegrees * M_PI / 180;
        double px = cos(angleRad) * x - sin(angleRad) * y;
        double py = sin(angleRad) * x + cos(angleRad) * y;

        translated->set(px, py);

        return  translated;
    };

    /** Source: http://content.gpwiki.org/index.php/Polygon_Collision
     * @brief DoEdgesIntersect Determines whether 2 edges intersect
     * @param p1 First point of first edge
     * @param p2 Second point of first edge
     * @param p3 First point of second edge
     * @param p4 Second point of second edge
     * @return true if edges intersect
     */
    static bool DoEdgesIntersect(const ofPoint & p1, const ofPoint & p2, const ofPoint & p3, const ofPoint & p4)
    {
        bool output;
        ofPoint * p2p1 = new ofPoint();
        p2p1->set(p2.x - p1.x, p2.y - p1.y);
        ofPoint * p3p4 = new ofPoint();
        p3p4->set(p3.x - p4.x, p3.y - p4.y);
        ofPoint * p3p1 = new ofPoint();
        p3p1->set(p3.x - p1.x, p3.y - p1.y);

        double det = determinant(*p2p1, *p3p4);
        double t = determinant(*p3p1, *p3p4) / det;
        double u = determinant(*p2p1, *p3p1) / det;

        if ((t < 0) || (u < 0) || (t > 1) || (u > 1))
        {
            output = false;
        }
        else
        {
            output = true;
        }

        delete p2p1;
        delete p3p4;
        delete p3p1;

        return output;
    }
    bool isPointInsideRectangle(int x, int y, const ofRectangle & rectangle){
        ofVec3f translation;
        ofQuaternion rotation;
        ofVec3f scale;
        ofQuaternion so;
        this->getFinalTransformationMatrix().decompose(translation, rotation, scale, so);

        ofPoint * traslated = new ofPoint();
        Object2D::translatePoint((x - translation.x), (y - translation.y), 360 - angleOffset, traslated);
        bool output = traslated->x>= rectangle.getX() && traslated->x <= rectangle.getX() + rectangle.getWidth() &&
                traslated->y>= rectangle.getY() && traslated->y <= rectangle.getY() + rectangle.getHeight();
        delete traslated;

        return output;

    }};
