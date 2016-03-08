#include "Structure.h"

//ofPoint * Structure::TopLeftPoint()
//{
//	throw std::runtime_error("Not yet implemented");
//}
//
//ofPoint * Structure::TopRightPoint()
//{
//	throw std::runtime_error("Not yet implemented");
//}
//
//ofPoint * Structure::BottomLeftPoint()
//{
//	throw std::runtime_error("Not yet implemented");
//}
//
//ofPoint * Structure::BottomRightPoint()
//{
//	throw std::runtime_error("Not yet implemented");
//}
//
//bool Structure::IsPointWithinBounds(int x, int y)
//{
//	throw std::runtime_error("Not yet implemented");
//}
//
//void Structure::AffectVector(int x, int y, ofVec3f * actionVector, bool isRotation = false)
//{
//	throw std::runtime_error("Not yet implemented");
//}
//
//void Structure::ShowBorders(bool shouldShow)
//{
//	throw std::runtime_error("Not yet implemented");
//}
//
//void Structure::Draw()
//{
//	throw std::runtime_error("Not yet implemented");
//}

Structure::Structure()
{
	this->children = new std::vector<Structure*>();
	this->elements = new std::vector<Shape*>();
	this->parent = NULL;
}

Structure::Structure(Structure* _parent)
{
	this->children = new std::vector<Structure*>();
	this->elements = new std::vector<Shape*>();
	this->parent = _parent;
}

Structure::~Structure()
{
	for (size_t i = this->GetChildrenCount(); i >= 0; i--)
	{
		this->RemoveChild(i);
	}
	this->children->clear();

	for (size_t i = this->GetElementsCount(); i >= 0; i--)
	{
		this->RemoveElement(i);
	}
	this->elements->clear();
}

std::vector<Shape*>* Structure::GetElements()
{
	return this->elements;
}

Shape * Structure::GetElement(size_t _position)
{
	return this->elements->at(_position);
}

bool Structure::AddElement(Shape * _newElement)
{
	this->elements->push_back(_newElement);
	return true;
}

bool Structure::RemoveElement(size_t _position)
{
	if (_position < this->GetElementsCount())
	{
		delete this->elements->at(_position);
		this->elements->at(_position) = NULL;
		this->elements->erase(this->elements->begin() + _position);
		return true;
	}
	return false;
}

Structure * Structure::GetParent()
{
	return this->parent;
}

std::vector<Structure*>* Structure::GetChildren()
{
	return this->children;
}

Structure * Structure::GetChild(size_t _position)
{
	return this->children->at(_position);
}

Structure * Structure::CreateNewChild()
{
	Structure* child = new Structure(this);
	this->children->push_back(child);
	return child;
}

bool Structure::RemoveChild(size_t _position)
{
	if (_position < this->GetChildrenCount())
	{
		delete this->children->at(_position);
		this->children->at(_position) = NULL;
		this->children->erase(this->children->begin() + _position);
		return true;
	}
	return false;
}

size_t Structure::GetElementsCount() const
{
	return this->elements->size();
}

size_t Structure::GetChildrenCount() const
{
	return this->children->size();
}
