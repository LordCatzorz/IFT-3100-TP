#include "Renderer.h"
#include "Shapes.h"
#include "ofxAssimpModelLoader.h"

Renderer::Renderer()
{
	this->sceneStructure = new Structure();
}

Renderer::~Renderer()
{
	delete this->sceneStructure;
}

void Renderer::Setup()
{
	ofSetFrameRate(60);
	ofSetSphereResolution(12);
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofEnableDepthTest();

	ofLight* light = new ofLight();
	light->setDiffuseColor(ofColor(255, 255, 255));
	light->setSpecularColor(ofColor(191, 191, 191));
	light->setPointLight();
	this->sceneStructure->shadersManager->AddLight(light);

	ofShader* colorFillShader = new ofShader();
	this->sceneStructure->shadersManager->AddShader(colorFillShader);
	colorFillShader->load("shader/v330/PhongVS.glsl", "shader/v330/PhongFS.glsl");
	this->sceneStructure->AddElement(Shapes::createCube());

	reset();
	ofSetLogLevel(ofLogLevel::OF_LOG_WARNING);
}

void Renderer::Update()
{
	ofShader* shader = this->sceneStructure->shadersManager->GetShader(0);
	shader->begin();
	shader->setUniform3f("colorAmbient", 0.1f, 0.1f, 0.1f);
	shader->setUniform3f("colorDiffuse", 0.0f, 0.5f, 0.5f);
	shader->setUniform3f("colorSpecular", 1.0f, 1.0f, 0.0f);
	shader->setUniform3f("color", 1.0f, 1.0f, 0.0f);
	shader->setUniform1f("brightness", 400.0f);
	shader->end();

	ofLight* light = this->sceneStructure->shadersManager->GetLight(0);
	light->setGlobalPosition(
		ofMap(ofGetMouseX() / (float) framebufferWidth, 0.0f, 1.0f, -framebufferWidth / 2.0, framebufferWidth / 2.0),
		ofMap(ofGetMouseY() / (float) framebufferHeight, 0.0f, 1.0f, -framebufferHeight / 2.0, framebufferHeight / 2.0),
		-zOffset * 1.5f);
}

void Renderer::Draw()
{
	this->sceneStructure->Draw();
}

void Renderer::reset()
{
	// initialisation des variables
	framebufferWidth = ofGetWidth();
	framebufferHeight = ofGetHeight();

	// centre du framebuffer
	xCenter = framebufferWidth / 2.0f;
	yCenter = framebufferHeight / 2.0f;

	// configurer la lumi�re ponctuelle
	ofLight* light = this->sceneStructure->shadersManager->GetLight(0);
	light->setDiffuseColor(ofColor(255, 255, 255));
	light->setSpecularColor(ofColor(191, 191, 191));
	light->setPointLight();

	ofLog() << "<reset>";
}
