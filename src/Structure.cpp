#include "Structure.h"

ofPoint * Structure::TopLeftPoint()
{
	throw std::runtime_error("Not yet implemented");
}

ofPoint * Structure::TopRightPoint()
{
	throw std::runtime_error("Not yet implemented");
}

ofPoint * Structure::BottomLeftPoint()
{
	throw std::runtime_error("Not yet implemented");
}

ofPoint * Structure::BottomRightPoint()
{
	return nullptr;
}

bool Structure::IsPointWithinBounds(int x, int y)
{
	throw std::runtime_error("Not yet implemented");
}

void Structure::AffectVector(int x, int y, ofVec3f * actionVector, bool isRotation = false)
{
	throw std::runtime_error("Not yet implemented");
}

void Structure::ShowBorders(bool shouldShow)
{
	throw std::runtime_error("Not yet implemented");
}

void Structure::Draw()
{
	throw std::runtime_error("Not yet implemented");
}

Structure::Structure()
{
}

Structure::~Structure()
{
}

std::list<Shape*> Structure::GetElements()
{
	throw std::runtime_error("Not yet implemented");
}

Shape * Structure::GetElement(size_t _position)
{
	throw std::runtime_error("Not yet implemented");
}

bool Structure::AddElement(Shape * _newElement)
{
	throw std::runtime_error("Not yet implemented");
}

bool Structure::RemoveElement(size_t _position)
{
	throw std::runtime_error("Not yet implemented");
}

Structure * Structure::GetParent()
{
	throw std::runtime_error("Not yet implemented");
}

std::list<Structure*> Structure::GetChildren()
{
	throw std::runtime_error("Not yet implemented");
}

Structure * Structure::GetChild(size_t _position)
{
	throw std::runtime_error("Not yet implemented");
}

Structure * Structure::CreateNewChild()
{
	throw std::runtime_error("Not yet implemented");
}

bool Structure::RemoveChild(size_t _position)
{
	throw std::runtime_error("Not yet implemented");
}

size_t Structure::GetElementsCount() const
{
	throw std::runtime_error("Not yet implemented");
}

size_t Structure::GetChildrenCount() const
{
	throw std::runtime_error("Not yet implemented");
}
