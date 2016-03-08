#ifndef STRUCTURE_H
#define STRUCTURE_H

#include "Shape.h"
#include <vector>

class Structure //: Shape
{
public:
	Structure();
	Structure(Structure* _parent);
	~Structure();

	std::vector<Shape*>* GetElements();
	Shape* GetElement(size_t _position);
	bool AddElement(Shape* _newElement);
	bool RemoveElement(size_t _position);

	Structure* GetParent();
	std::vector<Structure*>* GetChildren();
	Structure* GetChild(size_t _position);
	Structure* CreateNewChild();
	bool RemoveChild(size_t _position);

	size_t GetElementsCount() const;
	size_t GetChildrenCount() const;

private:
	std::vector<Shape*>* elements;
	Structure* parent;
	std::vector<Structure*>* children;

	// Inherited via Shape
	//virtual ofPoint * TopLeftPoint() override;
	//virtual ofPoint * TopRightPoint() override;
	//virtual ofPoint * BottomLeftPoint() override;
	//virtual ofPoint * BottomRightPoint() override;
	//virtual bool IsPointWithinBounds(int x, int y) override;
	////virtual void AffectVector(int x, int y, ofVec3f * actionVector, bool isRotation = false) override;
	//virtual void ShowBorders(bool shouldShow) override;
	//virtual void Draw() override;
};


#endif // !STRUCTURE_H

