#include "Structure.h"

void Structure::Draw()
{
	ofColor colours[4] = {ofColor::red, ofColor::green, ofColor::blue, ofColor::purple};
	ofLight* light = this->shadersManager->GetLight(0);
	//ofEnableLighting();
	light->setPointLight();
	light->setAttenuation(0.5f);
	light->setPosition(ofVec3f(500, 500, -500));
	//light->enable();
	//this->shadersManager->EnableShaders();
    ofPushMatrix();
	for (Structure* child : *(this->children))
	{
		child->Draw();
	}
	for (Shape* shape : *(this->elements))
	{
		shape->Draw();
	}
	ofPopMatrix();
	//this->shadersManager->DisableShaders();
	light->disable();

    ofDisableLighting();
}

bool Structure::IsPointWithinBounds(float x, float y)
{
    throw std::runtime_error("Not yet implemented");
}

void Structure::AddTranslation(ofVec3f _draggedPixelVector)
{

    throw std::runtime_error("Not yet implemented");
}

void Structure::AddRotation(ofVec3f _draggedPixelVector, int _axis)
{

    throw std::runtime_error("Not yet implemented");
}

void Structure::AddScale(bool _zoomIn)
{
	if (_zoomIn)
	{
		this->preMultScale(ofVec3f(1.1));
	}
	else
	{
		this->preMultScale(ofVec3f((1 / 1.1)));
	}
}

ofMatrix4x4 Structure::GetFinalTransformationMatrix()
{
	if (this->parent != NULL)
	{
		return (this->getInverse()*this->parent->getInverse()).getInverse();
	}
	else
	{
		return this->getInverse().getInverse();
	}
}

Structure::Structure() : ofMatrix4x4()
{
	this->children = new std::vector<Structure*>();
	this->elements = new std::vector<Shape*>();
	this->shadersManager = new ShadersManager();
	this->parent = NULL;
	ofLog(ofLogLevel::OF_LOG_VERBOSE) << "Created structure at adresse: " << this << " with parent structure NULL";
}

Structure::Structure(Structure* _parent) : ofMatrix4x4()
{
	this->children = new std::vector<Structure*>();
	this->elements = new std::vector<Shape*>();
	this->shadersManager = new ShadersManager();
	this->parent = _parent;
	ofLog(ofLogLevel::OF_LOG_VERBOSE) << "Created structure at adresse: " << this << " with parent structure " << _parent;
}

Structure::~Structure()
{
	ofLog(ofLogLevel::OF_LOG_VERBOSE) << "Deleting structure at adresse: " << this;
	for (size_t i = 0; i < this->GetChildrenCount(); i++)
	{
		this->DeleteChild(i);
	}
	this->children->clear();
	delete this->children;
	for (size_t i = 0; i < this->GetElementsCount(); i++)
	{
		this->DeleteElement(i);
	}
	this->elements->clear();
	delete this->elements;
	ofLog(ofLogLevel::OF_LOG_VERBOSE) << "Deleted structure at adresse: " << this;
}

std::vector<Shape*>* Structure::GetElements()
{
	return this->elements;
}

Shape * Structure::GetElement(int _position)
{
	if (_position < this->GetElementsCount())
	{
		return this->elements->at(_position);
	}
	else
	{
		return NULL;
	}
}

bool Structure::AddElement(Shape * _newElement)
{
	_newElement->SetParent(this);
	this->elements->push_back(_newElement);
	return true;
}

bool Structure::DeleteElement(int _position)
{
	if (_position < this->GetElementsCount())
	{
		delete this->elements->operator[](_position);
		this->elements->operator[](_position) = NULL;
		this->elements->erase(this->elements->begin() + _position);
		return true;
	}
	return false;
}

Shape* Structure::RemoveElement(int _position)
{
	Shape* element = NULL;
	if (_position < this->GetElementsCount())
	{
		element = this->elements->operator[](_position);
		this->elements->erase(this->elements->begin() + _position);

	}
	return element;
}

Structure * Structure::GetParent()
{
	return this->parent;
}

std::vector<Structure*>* Structure::GetChildren()
{
	return this->children;
}

Structure * Structure::GetChild(int _position)
{
	if (_position < this->GetChildrenCount())
	{
		return this->children->at(_position);
	}
	else
	{
		return NULL;
	}
}

Structure * Structure::CreateNewChild()
{
	Structure* child = new Structure(this);
	this->children->push_back(child);
	return child;
}

bool Structure::DeleteChild(int _position)
{
	if (_position < this->GetChildrenCount())
	{
		delete (*(this->children))[_position];
		//(*(this->children))[_position] = NULL;
		this->children->erase(this->children->begin() + _position);
		return true;
	}
	return false;
}

Structure * Structure::RemoveChild(int _position)
{
	Structure* child = NULL;
	if (_position < this->GetChildrenCount())
	{
		child = this->children->operator[](_position);
		this->children->erase(this->children->begin() + _position);

	}
	return child;
}

size_t Structure::GetElementsCount() const
{
	return this->elements->size();
}

size_t Structure::GetChildrenCount() const
{
	return this->children->size();
}
