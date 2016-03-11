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
	float cameraOffset;

	float oscillation;

	float scaleCube;
	float scaleSphere;
	float scaleTeapot;

	float xCenter;
	float yCenter;

	float speedMotion;
	float speedOscillation;

	float xOffset;
	float zOffset;

	float xDelta;
	float zDelta;

	float xInitial;
	float yInitial;

	int framebufferWidth;
	int framebufferHeight;

	int glVersionMajor;
	int glVersionMinor;

	bool isActiveLightAmbient;
	bool isActiveLightDirectional;
	bool isActiveLightPoint;
	bool isActiveLightSpot;

	bool isFlipAxisY;

	bool isVerbose;
	float oscillate(float time, float amplitude, float period, float shift, float offset)
	{
		return amplitude * sin((time - shift) * 2 * PI / period) + offset;
	}

	void reset();
};
