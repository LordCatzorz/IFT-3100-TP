#pragma once

#include "Structure.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Setup();
	void Update();
	void Draw();
private:
	Structure* sceneStructure;
};
