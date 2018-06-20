#include "ProjectFile.h"
#include<iostream>


ProjectFile::ProjectFile() {}


ProjectFile::~ProjectFile() {}

bool ProjectFile::startup()
{
	//fix oren-nayer
	m_shader.loadShader(aie::eShaderStage::VERTEX, "../shaders/simple.vert");
	m_shader.loadShader(aie::eShaderStage::FRAGMENT, "../shaders/simple.frag");
	
	//transformsArray = new glm::mat4[3];
	//objs = new aie::OBJMesh[3];

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

	m_fullscreenQuad.initialiseFullscreenQuad();

	m_texturedshader.loadShader(aie::eShaderStage::VERTEX, "../shaders/simplePP.vert");
	m_texturedshader.loadShader(aie::eShaderStage::FRAGMENT, "../shaders/simplePP.frag");

	if (m_texturedshader.link() == false) {
		printf("Post Shader Error: %s\n",
			m_texturedshader.getLastError());
		return false;
	}

	m_spearshader.loadShader(aie::eShaderStage::VERTEX, "../shaders/normalmap.vert");
	m_spearshader.loadShader(aie::eShaderStage::FRAGMENT, "../shaders/normalmap.frag");

	if (m_spearshader.link() == false)
	{
		printf("shader error %s", m_spearshader.getLastError());
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
		0, 0, 0, 1
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
		0, 0, 10, 1
	};

	//Object Storage
	//objs[0] = m_dragonMesh;
	//objs[1] = m_spearMesh;
	//objs[2] = m_RabbitMesh;

	//Transforms Storage
	//transformsArray[0] = m_dragonTransform;
	//transformsArray[1] = m_rabbitTransform;
	//transformsArray[2] = m_SpearTransform;

	//light
	m_light.diffuse = { 1, 1, 1 };
	m_light.specular = {1, 0, 1};
	m_light.direction = {-1, 3.14f, -1.5};
	ambientLight = { 1.0f, 1.0f, 1.0f};
	m_SpecularPower = 100;

	//light 2
	m_light1.diffuse = { 1, 1, 1 };
	m_light1.specular = { 0, 1, 0 };
	m_light1.direction = { -1, -3.14f, -2.5f };
	ambientLight1 = { 1.0f, 1.0f, 1.0f };
	m_SpecularPower1 = 200;
	
	//light 3
	m_light2.diffuse = { 1, 1, 0.3 };
	m_light2.specular = { 0, 1, 0 };
	m_light2.direction = { 21, -3.14f, -2.5f };
	ambientLight2 = { 1.0f, 0.5f, 1.0f };
	m_SpecularPower2 = 50;


	m_GSpear = new GameObject(&m_spearMesh, fCam, &m_shader);
	m_GSpear->SetTransform(m_SpearTransform);
	m_GSpear->CreateLight(m_light, ambientLight, m_SpecularPower);
	m_GSpear->CreateLight(m_light1, ambientLight, m_SpecularPower);

	m_GRabbit = new GameObject(&m_RabbitMesh, fCam, &m_shader);
	m_GRabbit->SetTransform(m_rabbitTransform);
	m_GRabbit->CreateLight(m_light1, ambientLight1, m_SpecularPower1);
	m_GRabbit->CreateLight(m_light, ambientLight, m_SpecularPower);

	m_GDragon = new GameObject(&m_dragonMesh, fCam, &m_shader);
	m_GDragon->SetTransform(m_dragonTransform);
	m_GDragon->CreateLight(m_light2, ambientLight2, m_SpecularPower2);
	m_GDragon->CreateLight(m_light1, ambientLight, m_SpecularPower);

	//camera initialisation
	fCam = new FlyCamera(window);
	
	return true;
}

void ProjectFile::shutdown()
{
	delete fCam;
	//delete transformsArray;
}

void ProjectFile::update(float deltaTime)
{
	fCam->update(deltaTime);
	m_lTime = glfwGetTime();
}

void ProjectFile::draw()
{
	
	//Grid
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

	m_renderTarget.bind();

	clearScreen();

	auto pvm = fCam->getProjection() * fCam->getView() * m_SpearTransform;
	//m_spearshader.bindUniform("ProjectionViewModel", pvm);
	m_spearshader.bindUniform("ModelMatrix", m_SpearTransform);
	m_spearshader.bindUniform("diffuseTexture", 0);
	m_spearshader.bindUniform("specularTexture", 0);
	m_spearshader.bindUniform("normalTexture", 0);
	m_spearshader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_SpearTransform)));

	m_GSpear->draw(fCam, &m_spearshader);

	//m_spearMesh.draw();

	//shaders
	m_shader.bind();

	//binding
	m_shader.bindUniform("cameraPosition", fCam->getWorldTransform()[3]);

	//camera and normal mapping
	pvm = fCam->getProjection() * fCam->getView() *  m_dragonTransform;
	m_shader.bindUniform("ProjectionViewModel", pvm);
	m_shader.bindUniform("ModelMatrix", m_dragonTransform);
	m_shader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_dragonTransform)));
	//m_dragonMesh.draw();

	m_GDragon->draw(fCam, &m_shader);

	//binding
	m_shader.bindUniform("cameraPosition", fCam->getWorldTransform()[3]);

	//camera and normal mapping
	pvm = fCam->getProjection() * fCam->getView() *  m_rabbitTransform;
	m_shader.bindUniform("ProjectionViewModel", pvm);
	m_shader.bindUniform("ModelMatrix", m_rabbitTransform);
	m_shader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_rabbitTransform)));

	m_GRabbit->draw(fCam, &m_shader);

	m_renderTarget.unbind();

	clearScreen();

	m_texturedshader.bind();
	m_texturedshader.bindUniform("colourTarget", 0);
	m_renderTarget.getTarget(0).bind(0);

	m_fullscreenQuad.draw();

	aie::Gizmos::draw(fCam->getProjectionView());
}