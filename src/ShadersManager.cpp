#include "ShadersManager.h"

ShadersManager::ShadersManager()
{
	this->lights = new vector<ofLight*>();
	this->shaders = new vector<ofShader*>();
}

ShadersManager::~ShadersManager()
{
	delete[] this->lights;
	delete[] this->shaders;
}

void ShadersManager::AddLight(ofLight * _light)
{
	this->lights->push_back(_light);
}

void ShadersManager::AddShader(ofShader * _shader)
{
	this->shaders->push_back(_shader);
}

bool ShadersManager::RemoveLight(int _position)
{
	if (_position < this->lights->size())
	{
		delete this->lights->operator[](_position);
		this->lights->operator[](_position) = NULL;
		this->lights->erase(this->lights->begin() + _position);
		return true;
	}
	return false;
}

bool ShadersManager::RemoveShader(int _position)
{
	if (_position < this->shaders->size())
	{
		delete this->shaders->operator[](_position);
		this->shaders->operator[](_position) = NULL;
		this->shaders->erase(this->shaders->begin() + _position);
		return true;
	}
	return false;
}

ofShader * ShadersManager::GetShader(int _position)
{
	if (_position < this->shaders->size())
	{
		return this->shaders->at(_position);
	} else
	{
		return NULL;
	}
}


ofLight * ShadersManager::GetLight(int _position)
{
	if (_position < this->lights->size())
	{
		return this->lights->at(_position);
	} else
	{
		return NULL;
	}
}
