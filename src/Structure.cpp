#include "Structure.h"

void Structure::Draw()
{
	ofColor colours[4] = {ofColor::red, ofColor::green, ofColor::blue, ofColor::purple};
	ofPushMatrix();
	// position
	ofTranslate(this->shadersManager->GetLight(0)->getPosition());

	// afficher un rep�re visuel pour la lumi�re
	this->shadersManager->GetLight(0)->draw();
	ofPopMatrix();


	// activer l'�clairage dynamique
	ofEnableLighting();

	// activer la lumi�re dynamique
	this->shadersManager->GetLight(0)->enable();
	ofPushMatrix();
	ofTranslate(500, 500);
	//ofScale(100, 100);
	ofScale(200, 200);
	ofRotateY(iteration++);
	shadersManager->GetShader(0)->begin();
	for each (of3dPrimitive* shape in *this->elements)
	{
		ofEnableLighting();
		ofSetColor(ofColor::orange);
		//shape->draw();
		ofEnableDepthTest();
		ofDisableLighting();
		ofSetLineWidth(100);
		ofSetColor(ofColor::red);
		shape->draw(ofPolyRenderMode::OF_MESH_FILL);

		ofSetColor(0, 0, 255);
		vector<ofMeshFace> faces = shape->getMesh().getUniqueFaces();
		ofMeshFace face;
		ofVec3f c, n;
		for (unsigned int i = 0; i < faces.size(); i++)
		{
			face = faces[i];
			c = calculateCenter(&face);
			n = face.getFaceNormal();
			ofSetColor(colours[i]);
			//ofLine(c.x, c.y, c.z, c.x + n.x*0.1f, c.y + n.y*0.1f, c.z + n.z*0.1f);
		}
		vector<ofPoint> vertices = shape->getMeshPtr()->getVertices();
		ofPoint v;
		for (unsigned int i = 0; i < vertices.size(); i++)
		{
			v = vertices[i];
			n = shape->getMesh().getNormal(i);
			ofLine(v.x, v.y, v.z, v.x + n.x*0.1f, v.y + n.y*0.1f, v.z + n.z*0.1f);
		}
	}
	for each (Structure* structure in *this->children)
	{
		structure->Draw();
	}
	/*ofDrawSphere(1);*/
	shadersManager->GetShader(0)->end();
	ofPopMatrix();
}

Structure::Structure()
{
	this->children = new std::vector<Structure*>();
	this->elements = new std::vector<of3dPrimitive*>();
	this->shadersManager = new ShadersManager();
	this->parent = NULL;
	ofLog(ofLogLevel::OF_LOG_VERBOSE) << "Created structure at adresse: " << this << " with parent structure NULL";
}

Structure::Structure(Structure* _parent)
{
	this->children = new std::vector<Structure*>();
	this->elements = new std::vector<of3dPrimitive*>();
	this->shadersManager = new ShadersManager();
	this->parent = _parent;
	ofLog(ofLogLevel::OF_LOG_VERBOSE) << "Created structure at adresse: " << this << " with parent structure " << _parent;
}

Structure::~Structure()
{
	ofLog(ofLogLevel::OF_LOG_VERBOSE) << "Deleting structure at adresse: " << this;
	for (size_t i = 0; i < this->GetChildrenCount(); i++)
	{
		this->RemoveChild(i);
	}
	this->children->clear();
	delete this->children;
	for (size_t i = 0; i < this->GetElementsCount(); i++)
	{
		this->RemoveElement(i);
	}
	this->elements->clear();
	delete this->elements;
	ofLog(ofLogLevel::OF_LOG_VERBOSE) << "Deleted structure at adresse: " << this;
}

std::vector<of3dPrimitive*>* Structure::GetElements()
{
	return this->elements;
}

of3dPrimitive * Structure::GetElement(int _position)
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

bool Structure::AddElement(of3dPrimitive * _newElement)
{
	this->elements->push_back(_newElement);
	return true;
}

bool Structure::RemoveElement(int _position)
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

bool Structure::RemoveChild(int _position)
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

size_t Structure::GetElementsCount() const
{
	return this->elements->size();
}

size_t Structure::GetChildrenCount() const
{
	return this->children->size();
}
