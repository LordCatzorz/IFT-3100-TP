#include "Renderer.h"
#include "Shapes.h"

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
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofSetLogLevel(ofLogLevel::OF_LOG_WARNING);


}

void Renderer::Update()
{
}

void Renderer::Draw()
{
	float width = ofGetWindowWidth();
	float height = ofGetWindowHeight();
	ofLight light = ofLight();

	light.setDiffuseColor(ofColor(255, 255, 255));
	light.setSpecularColor(ofColor(191, 191, 191));
	light.setPointLight();
	light.setGlobalPosition(
		ofMap(ofGetMouseX() / (float) width, 0.0f, 1.0f, -width / 2.0, width / 2.0),
		ofMap(ofGetMouseY() / (float) height, 0.0f, 1.0f, -height / 2.0, height / 2.0),
		100 * 1.5f);

	ofEnableLighting();

	// activer la lumi�re dynamique
	light.enable();


	ofShader shader = ofShader();
	shader.load(
		"shader/v330/BlinnPhongVerticesShader.glsl",
		"shader/v330/BlinnPhongFacesShader.glsl");

	

	ofPushMatrix();
	
	ofMesh* mesh = Shapes::createIcosahedron();
	ofTranslate(width / 2.0, height / 2.0);
	shader.begin();
	shader.setUniform3f("colorAmbient", 0.1f, 0.1f, 0.1f);
	shader.setUniform3f("colorDiffuse", 0.0f, 0.5f, 0.5f);
	shader.setUniform3f("colorSpecular", 1.0f, 1.0f, 0.0f);
	shader.setUniform1f("brightness", oscillate(ofGetElapsedTimeMillis(), 32, 5000, 0, 32));
	shader.setUniform3f("lightPosition", light.getGlobalPosition() * ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));
	mesh->draw();
	shader.end();
	ofPopMatrix();
}
