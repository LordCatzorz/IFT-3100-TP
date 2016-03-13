#ifndef SHADERS_MANAGER_H
#define SHADERS_MANGER_H
#include "ofMain.h"
class ShadersManager
{
public:
	ShadersManager();
	~ShadersManager();

	void AddLight(ofLight* _light);
	void AddShader(ofShader* _shader);

	bool RemoveLight(int _position);
	bool RemoveShader(int _position);

	ofShader* GetShader(int _position);
	ofLight* GetLight(int _position);

	void EnableShaders();
	void DisableShaders();

private:
	std::vector<ofLight*>* lights;
	std::vector<ofShader*>* shaders;
};

#endif