#ifndef __PROJ_H_
#define __PROJ_H_

#include"Application.h"
#include"planetoid.h"
#include"FlyCamera.h"

#include"Shader.h"
#include"Mesh.h"
#include"OBJMesh.h"
#include"Texture.h"
#include"RenderTarget.h"

#include"Light.h"

class ProjectFile : public Application
{
public:
	ProjectFile();
	~ProjectFile();

	bool startup();
	void shutdown();

	void update(float deltaTime);
	void draw();

protected:

	FlyCamera* fCam;

	//soulspear
	aie::OBJMesh m_spearMesh;
	glm::mat4 m_SpearTransform;

	//Rabbit
	aie::OBJMesh m_RabbitMesh;
	glm::mat4 m_rabbitTransform;

	//Dragon
	aie::OBJMesh m_dragonMesh;
	glm::mat4 m_dragonTransform;

	//shaders
	aie::ShaderProgram m_shader;
	aie::ShaderProgram m_texturedshader;

	float m_lTime;
	Light m_light;
	//Light m_lightL;
	//Light m_lightR;

	//ambient light in scene
	glm::vec3 ambientLight;

	//array of objects
	glm::mat4* transformsArray;
	aie::OBJMesh* objs;
	//Light* lightsArray;
};

#endif