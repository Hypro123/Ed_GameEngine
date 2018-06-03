#ifndef __PROJ_H_
#define __PROJ_H_

#include"Application.h"
#include"planetoid.h"
#include"FlyCamera.h"

#include"Shader.h"
#include"Mesh.h"
#include"OBJMesh.h"

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
	//Planetoid* p;
	//Planetoid* q;
	//Planetoid* s;

	FlyCamera* fCam;

	//shaders
	aie::ShaderProgram m_shader;
	
	//bunny
	aie::OBJMesh m_bunnyMesh;
	glm::mat4 m_bunnyTransform;

	//object rendering
	Mesh m_quadmesh;
	glm::mat4 m_quadtransform;
	//Mesh m_circle;
};

#endif