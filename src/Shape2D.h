#ifndef SHAPE2D_H
#define SHAPE2D_H
#include "Shape.h"
#ifdef _WIN32
#define M_PI PI
#endif

class Shape2D : public Shape
{
public:
	ofPoint * TopLeftPoint() { return &topLeftPoint; }
	ofPoint * TopRightPoint() { return &topRightPoint; }
	ofPoint * BottomLeftPoint() { return &bottomLeftPoint; }
	ofPoint * BottomRightPoint() { return &bottomRightPoint; }

    virtual void Create(int x1, int y1, int width, int height) = 0;
	virtual bool        DoesRectangleOverlap(int x1, int y1, int x2, int y2) = 0;

    void ActionStop(){currentAction = Action::Rest;}

    void AffectVector(int x, int y, ofVec3f * actionVector, bool isRotation = false){
        if(currentAction == Action::Rotate || isRotation){
            currentAction = Action::Rotate;
            double side = (double)(x - xOffset - topLeftPoint.x);
            double adj = (double)(y - yOffset - topLeftPoint.y);

            double currentAngle = atan((adj / side)) * 180/M_PI;


            if(referenceAngleOffset <= 0){
                referenceAngleOffset = currentAngle;
                if(side < 0){
                    referenceAngleOffset += 180;
                }
                angleOffset -= referenceAngleOffset;
            }

            if(side < 0){
                currentAngle = currentAngle - 180;
            }
            angleOffset += currentAngle - previousAngle;

            previousAngle = currentAngle;

            angleOffset = fmod(angleOffset, 360);
        }else{
            previousAngle = referenceAngleOffset = 0;
            if(currentAction == Action::Rest){
                if(isPointInsideRectangle(x, y, horizontalBorder1)){
                    currentAction = Action::Resize;
                    selectedResizeBar = 1;
                }else if(isPointInsideRectangle(x, y, horizontalBorder2)){
                    currentAction = Action::Resize;
                    selectedResizeBar = 2;
                }else if(isPointInsideRectangle(x, y, verticalBorder1)){
                    currentAction = Action::Resize;
                    selectedResizeBar = 3;
                }else if(isPointInsideRectangle(x, y, verticalBorder2)){
                    currentAction = Action::Resize;
                    selectedResizeBar = 4;
                }else{//Not trying to resize
                    currentAction = Action::Move;
                }
            }

            if(currentAction == Action::Resize){
                if(selectedResizeBar == 1){
                    topLeftPoint.y += actionVector->y;
                    topRightPoint.y += actionVector->y;
                } else if(selectedResizeBar == 2){
                    bottomLeftPoint.y += actionVector->y;
                    bottomRightPoint.y += actionVector->y;
                } else if(selectedResizeBar == 3){
                    topLeftPoint.x += actionVector->x;
                    bottomLeftPoint.x += actionVector->x;
                } else if(selectedResizeBar == 4){
                    topRightPoint.x += actionVector->x;
                    bottomRightPoint.x += actionVector->x;
                }
            }else{//Not trying to resize
                xOffset += actionVector->x; yOffset += actionVector->y;
                for(Shape2D * child : children){
                    child->AffectVector(x, y, actionVector, isRotation);
                }
            }
            refreshBorders();
            refreshPoints();
        }
    }

    void Draw(){
        ofDisableDepthTest();
        ofPushMatrix();
        if(parentShape != nullptr)
            ofTranslate(parentXOffset, parentYOffset);
        else
            ofTranslate(xOffset, yOffset);
        ofRotate(angleOffset);
        ofFill();
        ofSetColor(drawColor);
        drawShape();
        if(parentShape != nullptr)
            SetSelected(parentShape->GetSelected());
        if(shouldShowBorders){
            ofFill();
            if(children.size() <= 0 && parentShape == nullptr){
                borderColor = ofColor::gray;
            }else{
                if(children.size() > 0){
                    borderColor.g = 0;
                    borderColor.r = 255;
                    borderColor.b = 0;
                }
                if(parentShape != nullptr){
                    borderColor.b = parentShape->getBlueVal();
                    borderColor.r = (int)(parentShape->getBlueVal() * 0.75);
                }
            }
            ofSetColor(borderColor);
            ofDrawRectangle(horizontalBorder1);
            ofDrawRectangle(horizontalBorder2);
            ofDrawRectangle(verticalBorder1);
            ofDrawRectangle(verticalBorder2);
        }else{
        }
        for(Shape * child : children)
            child->Draw();
        ofPopMatrix();

        ofEnableDepthTest();
    }

    bool IsPointWithinBounds(float x, float y){
        return isPointInsideRectangle(x, y, ofRectangle(topLeftPoint, bottomRightPoint));
    }

    void SetColor(ofColor * newColor){drawColor = *newColor;}
    Shape * GetParent(){ return  parentShape;}
    void AddChild(Shape2D * child){
        if(child->parentShape == nullptr){
            children.push_back(child);
            child->notifyAttachedToParen(this);
        }
    }
    void RemoveChild(Shape2D * child){
        for(std::vector<Shape2D*>::iterator toDel = children.begin(); toDel != children.end(); toDel++){
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
        for(Shape2D * toDel : children){
            toDel->parentShape = nullptr;
            toDel->xOffset = toDel->parentXOffset + xOffset;
            toDel->yOffset = toDel->parentYOffset + yOffset;
            toDel->SetSelected(false);
            toDel->angleOffset += angleOffset;
        }
        children.clear();
    }

protected:

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

    ofColor     drawColor = ofColor(0,0,0);
    ofColor     borderColor = ofColor::gray;
    Shape2D     * parentShape = nullptr;
    std::vector<Shape2D*> children;

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

        ofPoint * traslated = new ofPoint();
        Shape2D::translatePoint((x - xOffset), (y - yOffset), 360 - angleOffset, traslated);
        bool output = traslated->x>= rectangle.getX() && traslated->x <= rectangle.getX() + rectangle.getWidth() &&
                traslated->y>= rectangle.getY() && traslated->y <= rectangle.getY() + rectangle.getHeight();
        delete traslated;

        return output;

    }
private:
    static double determinant(const ofPoint & p1, const ofPoint & p2){
        return p1.x * p2.y - p1.y * p2.x;
    }
    void notifyAttachedToParen(Shape2D * parent){
        parentShape = parent;
        parentXOffset = xOffset - parent->xOffset;
        parentYOffset = yOffset - parent->yOffset;
    }

    virtual void    drawShape() = 0;
    virtual void    refreshPoints() = 0;
};

#endif // SHAPE2D_H
