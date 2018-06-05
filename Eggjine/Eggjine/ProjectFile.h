#ifndef __PROJ_H_
#define __PROJ_H_

#include"Application.h"
#include"planetoid.h"
#include"FlyCamera.h"

#include"Shader.h"
#include"Mesh.h"
#include"OBJMesh.h"
#include"Texture.h"

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

	//Bunny
	//aie::OBJMesh m_BunnyMesh;
	//glm::mat4 m_BunnyTransform;
	//aie::Texture m_modelTexture;

	//shaders
	aie::ShaderProgram m_shader;

	//object rendering
	//Mesh m_quadmesh;
	//glm::mat4 m_quadtransform;
	//aie::Texture m_gridTexture;

	float m_lTime;
	Light m_light;

	//ambient light in scene
	glm::vec3 ambientLight;

	//quaternion testing
	glm::vec3 m_positions[2];
	glm::quat m_rotations[2];
};

#endif