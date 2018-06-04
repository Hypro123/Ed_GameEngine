#include "ProjectFile.h"
#include<iostream>


ProjectFile::ProjectFile() {}


ProjectFile::~ProjectFile() {}

bool ProjectFile::startup()
{
	m_shader.loadShader(aie::eShaderStage::VERTEX, "../shaders/normalmap.vert");
	m_shader.loadShader(aie::eShaderStage::FRAGMENT, "../shaders/normalmap.frag");

	if (m_shader.link() == false)
	{
		printf("shader error %s", m_shader.getLastError());
		return false;
	}

	//if (m_gridTexture.load("../textures/numbered_grid.tga") == false)
	//{
	//	printf("Failed to load texture!\n");
	//	return false;
	//}

	//if(m_modelTexture.load("../soulspear/soulspear_specular.tga") == false)
	//{
	//	printf("texture failed to load\n");
	//	return false;
	//}

	//../soulspear/soulspear.obj
	//../stanford/Bunny.obj
	if (m_spearMesh.load("../soulspear/soulspear.obj") == false)
	{
		printf("Mesh Error!\n");
		return false;
	}

	//if (m_BunnyMesh.load("../stanford/Bunny.obj") == false)
	//{
	//	printf("Bunny Mesh Error!\n");
	//	return false;
	//}

	//initialise quad
	//m_quadmesh.initialiseQuad();

	//drawing mesh
	m_SpearTransform = 
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	
	//m_BunnyTransform =
	//{
	//	1, 0, 0, 0,
	//	0, 1, 0, 0,
	//	0, 0, 1, 0,
	//	0, 0, 0, 1
	//};

	//material


	//light
	m_light.diffuse = { 1, 0, 1 };
	m_light.specular = {1, 1, 1};
	m_light.direction = {-1, -0.5, -1};
	ambientLight = { 0.75f, 0.75f, 0.75f};

	//camera initialisation
	fCam = new FlyCamera(window);
	
	return true;
}

void ProjectFile::shutdown()
{
	delete fCam;
}

void ProjectFile::update(float deltaTime)
{
	fCam->update(deltaTime);
	m_lTime = glfwGetTime();
	
	m_light.direction = glm::vec3(glm::sin(m_lTime * 0.2f), glm::cos(m_lTime * 0.2f), 0);
}

void ProjectFile::draw()
{
	aie::Gizmos::addTransform(glm::mat4(1));
	glm::vec4 white(1);
	glm::vec4 black(0, 0, 0, 1);
	for (int i = 0; i < 21; ++i)
	{
		aie::Gizmos::addLine(glm::vec3(-10 + i, 0, 10),
			glm::vec3(-10 + i, 0, -10),
			i == 10 ? white : black);
		aie::Gizmos::addLine(glm::vec3(10, 0, -10 + i),
			glm::vec3(-10, 0, -10 + i),
			i == 10 ? white : black);
	}

	//shaders
	m_shader.bind();

	//m_shader.bindUniform("diffuseTexture", 0);
	//m_modelTexture.bind(0);

	//binding
	m_shader.bindUniform("cameraPosition", fCam->getWorldTransform()[3]);

	m_shader.bindUniform("lightDirection", m_light.direction);
	m_shader.bindUniform("Ia", ambientLight);
	m_shader.bindUniform("Id", m_light.diffuse);
	m_shader.bindUniform("Is", m_light.specular);

	//camera and normal mapping
	auto pvm = fCam->getProjection() * fCam->getView() *  m_SpearTransform;
	m_shader.bindUniform("ProjectionViewModel", pvm);
	m_shader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_SpearTransform)));

	m_spearMesh.draw();
	//m_BunnyMesh.draw();

	aie::Gizmos::draw(fCam->getProjectionView());
}