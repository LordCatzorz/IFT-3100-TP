#include "Renderer.h"

Renderer::Renderer()
{
	this->sceneStructure = new Structure();
}

Renderer::~Renderer()
{
	delete this->sceneStructure;
}
