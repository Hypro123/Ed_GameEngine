#include "ProjectFile.h"
#include<iostream>


ProjectFile::ProjectFile() {}


ProjectFile::~ProjectFile() {}

bool ProjectFile::startup()
{
	//fix oren-nayer
	m_shader.loadShader(aie::eShaderStage::VERTEX, "../shaders/simple.vert");
	m_texturedshader.loadShader(aie::eShaderStage::VERTEX, "../shaders/normalmap.vert");
	m_shader.loadShader(aie::eShaderStage::FRAGMENT, "../shaders/simple.frag");
	m_texturedshader.loadShader(aie::eShaderStage::FRAGMENT, "../shaders/normalmap.frag");
	
	transformsArray = new glm::mat4[3];
	objs = new aie::OBJMesh[3];

	if (m_shader.link() == false)
	{
		printf("shader error %s", m_shader.getLastError());
		return false;
	}
	int H;
	int W;
	glfwGetWindowSize(window, &W, &H);

	if (m_renderTarget.initialise(1, W, H) == false) {
		printf("Render Target Error!\n");
		return false;
	}

	//../soulspear/soulspear.obj
	//../stanford/Bunny.obj
	if (m_dragonMesh.load("../stanford/dragon.obj") == false)
	{
		printf("Mesh Error!\n");
		return false;
	}
	
	if (m_RabbitMesh.load("../stanford/Bunny.obj") == false)
	{
		printf("Mesh Error!\n");
		return false;
	}

	if (m_spearMesh.load("../soulspear/soulspear.obj") == false)
	{
		printf("Mesh Error!\n");
		return false;
	}

	//drawing mesh
	m_dragonTransform =
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 10, 1
	};

	//drawing mesh
	m_rabbitTransform =
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		10, 0, 0, 1
	};

	//drawing mesh
	m_SpearTransform = 
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	//Object Storage
	objs[0] = m_dragonMesh;
	objs[1] = m_spearMesh;
	objs[2] = m_RabbitMesh;

	//Transforms Storage
	transformsArray[0] = m_dragonTransform;
	transformsArray[1] = m_rabbitTransform;
	transformsArray[2] = m_SpearTransform;

	//light
	m_light.diffuse = { 1, 1, 1 };
	m_light.specular = {0.9f, 0.1f, 0.1f};
	m_light.direction = {-1, 0, -1.5};
	ambientLight = { 0.1f, 0.1f, 0.1f};
	m_SpecularPower = 5;

	m_GSpear = new GameObject(&m_spearMesh, fCam, &m_shader);
	m_GSpear->SetTransform(m_SpearTransform);
	m_GSpear->CreateLight(m_light, ambientLight);
	
	m_GRabbit = new GameObject(&m_RabbitMesh, fCam, &m_shader);
	m_GRabbit->SetTransform(m_rabbitTransform);
	m_GRabbit->CreateLight(m_light, ambientLight);
	
	m_GDragon = new GameObject(&m_dragonMesh, fCam, &m_shader);
	m_GDragon->SetTransform(m_dragonTransform);
	m_GDragon->CreateLight(m_light, ambientLight);


	//camera initialisation
	fCam = new FlyCamera(window);
	
	return true;
}

void ProjectFile::shutdown()
{
	delete fCam;
	delete transformsArray;
}

void ProjectFile::update(float deltaTime)
{
	fCam->update(deltaTime);
	m_lTime = glfwGetTime();
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
	
	m_GRabbit->update(fCam, &m_renderTarget);
	m_GSpear->drawNormal(fCam, &m_renderTarget);
	//m_GDragon->update(fCam, m_renderTarget);

	////shaders
	//m_shader.bind();

	////binding
	//m_shader.bindUniform("cameraPosition", fCam->getWorldTransform()[3]);

	//m_shader.bindUniform("lightDirection", m_light.direction);
	//m_shader.bindUniform("Ia", ambientLight);
	//m_shader.bindUniform("Id", m_light.diffuse);
	//m_shader.bindUniform("Is", m_light.specular);
	//m_shader.bindUniform("specularPower", m_SpecularPower);

	//for(int i = 0; i < 3; ++i)
	//{
	//	//camera and normal mapping
	//	auto pvm = fCam->getProjection() * fCam->getView() *  transformsArray[i];
	//	m_shader.bindUniform("ProjectionViewModel", pvm);

	//	m_shader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(transformsArray[i])));
	//	objs[i].draw();
	//}

	aie::Gizmos::draw(fCam->getProjectionView());
}