#include "Structure.h"

void Structure::Draw()
{
	ofColor colours[4] = {ofColor::red, ofColor::green, ofColor::blue, ofColor::purple};
	ofLight* light = this->shadersManager->GetLight(0);
	ofShader* shader = this->shadersManager->GetShader(0);

    ofEnableLighting();

    light->setPointLight();
    light->setAttenuation(0.5f);
    light->setPosition(ofVec3f(500,500,-500));
light->enable();

    ofPushMatrix();
    ofTranslate(300, 300);


    ofFill();
            ofSetColor(180);
            ofDrawBox(100);


            ofPopMatrix();



            shader->begin();
            ofPushMatrix();
            ofTranslate(600, 600);
            ofRotateY(iteration++);
            ofScale(100,100,100);
           /* for (of3dPrimitive* shape : *(this->elements))
            {
                shape->draw();
            }*/
            ofPopMatrix();
            shader->end();
    light->disable();

    ofDisableLighting();

    /*ofPushMatrix();
	// afficher un repère visuel pour les lumières
    light->draw();
	ofPopMatrix();

	ofPushMatrix();

	ofTranslate(300, 300);
	ofRotateY(iteration++);

    ofEnableLighting();
    light->enable();

	shader->begin();
	ofPushMatrix();
	ofScale(100,100,100);
	for (of3dPrimitive* shape : *(this->elements))
	{
		shape->draw();
	}
	ofPopMatrix();
	shader->end();
    light->disable();
    ofDisableLighting();
    ofPopMatrix();

	ofPushMatrix();

	ofTranslate(600, 600);
	ofRotateY(iteration);

    ofEnableLighting();
    light->enable();

	shader->begin();
	ofPushMatrix();
	ofScale(100, 100, 100);
    ofDrawBox(1, 1, 1);
	ofPopMatrix();
	shader->end();
    light->disable();
	ofDisableLighting();
    ofPopMatrix();*/


    //ofPushMatrix();
	//// position
	////ofTranslate(this->shadersManager->GetLight(0)->getPosition());

	//// afficher un rep�re visuel pour la lumi�re
	//this->shadersManager->GetLight(0)->draw();
	//ofPopMatrix();

	//// activer l'�clairage dynamique
	//ofEnableLighting();

	//// activer la lumi�re dynamique
	//this->shadersManager->GetLight(0)->enable();
	//
	//ofPushMatrix();
	//ofTranslate(500, 500);
	////ofScale(100, 100);
	////ofScale(200, 200);
	//ofRotateY(iteration++);
	//ofPushMatrix();
 //   for (of3dPrimitive* shape : *(this->elements))
	//{
	//	ofEnableLighting();
	//	ofSetColor(ofColor::orange);
	//	//shape->draw();
	//	ofEnableDepthTest();

	//	shadersManager->GetShader(0)->begin();
	//	//ofDisableLighting();
	//	ofSetLineWidth(100);
	//	shape->draw(ofPolyRenderMode::OF_MESH_FILL);

	//	ofSetColor(0, 0, 255);
	//	vector<ofMeshFace> faces = shape->getMesh().getUniqueFaces();
	//	ofMeshFace face;
	//	ofVec3f c, n;
	//	for (unsigned int i = 0; i < faces.size(); i++)
	//	{
	//		face = faces[i];
	//		c = calculateCenter(&face);
	//		n = face.getFaceNormal();
	//		ofSetColor(colours[i]);
	//		ofLine(c.x, c.y, c.z, c.x + n.x*0.1f, c.y + n.y*0.1f, c.z + n.z*0.1f);
	//	}
	//	vector<ofPoint> vertices = shape->getMeshPtr()->getVertices();
	//	ofPoint v;
	//	for (unsigned int i = 0; i < vertices.size(); i++)
	//	{
	//		v = vertices[i];
	//		n = shape->getMesh().getNormal(i);
	//		//ofLine(v.x, v.y, v.z, v.x + n.x*0.1f, v.y + n.y*0.1f, v.z + n.z*0.1f);
	//	}
	//}
 //   for(Structure* structure : *(this->children))
	//{
	//	structure->Draw();
	//}
	///*ofDrawSphere(1);*/
	//shadersManager->GetShader(0)->end();
	//ofPopMatrix();
}

ofMatrix4x4 Structure::GetFinalTransformationMatrix()
{
	if (this->parent != NULL)
	{
		return (this->getInverse()*this->parent->getInverse()).getInverse();
	} else
	{
		return this->getInverse().getInverse();
	}
}

Structure::Structure() : ofMatrix4x4()
{
	this->children = new std::vector<Structure*>();
	this->elements = new std::vector<Shape3D*>();
	this->shadersManager = new ShadersManager();
	this->parent = NULL;
	ofLog(ofLogLevel::OF_LOG_VERBOSE) << "Created structure at adresse: " << this << " with parent structure NULL";
}

Structure::Structure(Structure* _parent) : ofMatrix4x4()
{
	this->children = new std::vector<Structure*>();
	this->elements = new std::vector<Shape3D*>();
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

std::vector<Shape3D*>* Structure::GetElements()
{
	return this->elements;
}

Shape3D * Structure::GetElement(int _position)
{
	if (_position < this->GetElementsCount())
	{
		return this->elements->at(_position);
	} else
	{
		return NULL;
	}
}

bool Structure::AddElement(Shape3D * _newElement)
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

Shape3D* Structure::RemoveElement(int _position)
{
	Shape3D* element = NULL;
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
	} else
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