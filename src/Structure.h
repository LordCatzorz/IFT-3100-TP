#ifndef STRUCTURE_H
#define STRUCTURE_H

#include "ShadersManager.h"
#include "Shape.h"
#include <vector>

class Structure : public Shape, public ofMatrix4x4
{
public:

	ofMatrix4x4 GetFinalTransformationMatrix();
	ShadersManager* shadersManager;

	Structure();
	Structure(Structure* _parent);
	~Structure();

	std::vector<Shape*>* GetElements();
	Shape* GetElement(int _position);
	bool AddElement(Shape* _newElement);
	bool DeleteElement(int _position);
	Shape* RemoveElement(int _position);

	Structure* GetParent();
	std::vector<Structure*>* GetChildren();
	Structure* GetChild(int _position);
	Structure* CreateNewChild();
	bool DeleteChild(int _position);
	Structure* RemoveChild(int _position);

	size_t GetElementsCount() const;
	size_t GetChildrenCount() const;

	// Inherited via Shape
	bool IsPointWithinBounds(float x, float y);

    void AddTranslation(int x, int y, ofVec3f _draggedPixelVector);

	void AddRotation(ofVec3f _draggedPixelVector, int _axis);

	void AddScale(bool _zoomIn);


	void Draw();
	static ofVec3f calculateCenter(ofMeshFace *face)
	{
		int lastPointIndex = 3;
		ofVec3f result;
		for (unsigned int i = 0; i < 3; i++)
		{
			result += face->getVertex(i);
		}
		result /= lastPointIndex;
		return result;
	}
private:
	int iteration = 0;
	std::vector<Shape*>* elements;
	Structure* parent;
	std::vector<Structure*>* children;

	
	// Inherited via of3dPrimitive
	//virtual ofPoint * TopLeftPoint() override;
	//virtual ofPoint * TopRightPoint() override;
	//virtual ofPoint * BottomLeftPoint() override;
	//virtual ofPoint * BottomRightPoint() override;
	//virtual bool IsPointWithinBounds(int x, int y) override;
	////virtual void AffectVector(int x, int y, ofVec3f * actionVector, bool isRotation = false) override;
	//virtual void ShowBorders(bool shouldShow) override;
	

	

};


#endif // !STRUCTURE_H

