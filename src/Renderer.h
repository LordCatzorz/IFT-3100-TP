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
	float oscillate(float time, float amplitude, float period, float shift, float offset)
	{
		return amplitude * sin((time - shift) * 2 * PI / period) + offset;
	}
};
