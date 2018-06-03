#include "ProjectFile.h"



ProjectFile::ProjectFile() {}


ProjectFile::~ProjectFile() {}

bool ProjectFile::startup()
{
	m_shader.loadShader(aie::eShaderStage::VERTEX, "./simple.vert");
	m_shader.loadShader(aie::eShaderStage::FRAGMENT, "./simple.frag");

	if (m_shader.link() == false)
	{
		printf("shader error %s", m_shader.getLastError());
		return false;
	}

	if (m_bunnyMesh.load("../stanford/Bunny.obj") == false)
	{
		printf("Bunny mesh Error!\n");
		return false;
	}

	m_bunnyTransform = 
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	//drawing mesh
	m_quadtransform = 
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	m_quadmesh.drawBox(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), glm::vec4(1, 1, 1, 1), &m_quadtransform);
	//m_circle.drawCylinder(glm::vec3(0, 0, 0), 5, 3, 3, glm::vec4(1, 1, 1, 1), &m_quadtransform);
	
	//camera initialisation
	fCam = new FlyCamera(window);
	//planetoid initialisation
	//p = new Planetoid(glm::mat4(1), glm::vec4(1, 1, 0, 1), 2);
	//q = new Planetoid(glm::mat4(1), glm::vec4(0, 1, 0, 1), 1);
	//s = new Planetoid(glm::mat4(1), glm::vec4(0, 0, 1, 1), 0.5f);
	//set position of planetoids
	//q->setPosition(glm::vec3(0, 0, -7));
	//p->setPosition(glm::vec3(0, 0, 5));
	//s->setPosition(glm::vec3(0, 0, 2.5f));

	//parenting of planetoids in order to create an orbit
	//q->setParent(p);
	//s->setParent(q);
	
	return true;
}

void ProjectFile::shutdown()
{
	delete fCam;
	//delete s;
	//delete q;
	//delete p;
}

void ProjectFile::update(float deltaTime)
{
	//glm::mat4 rot(1);
	////rotate around point
	//rot = glm::rotate(deltaTime * 10, glm::vec3(0, 1, 0));
	//p->localMatrix = rot * p->localMatrix;
	////rotate around obj
	//rot = glm::rotate(deltaTime * 10, glm::vec3(0, 1, 0));
	//p->localMatrix = p->localMatrix * rot;

	//rot = rot = glm::rotate(deltaTime * 10, glm::vec3(0, 1, 0));
	//q->localMatrix = rot * q->localMatrix;

	//rot = rot = glm::rotate(deltaTime * 50, glm::vec3(0, 1, 0));
	//q->localMatrix = q->localMatrix * rot;

	////updating objects
	//p->updatePlanetoid(deltaTime);
	//q->updatePlanetoid(deltaTime);
	//s->updatePlanetoid(deltaTime);
	fCam->update(deltaTime);
}

void ProjectFile::draw()
{
	//p->drawPlanetoid();
	//q->drawPlanetoid();
	//s->drawPlanetoid();

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

	auto pvm = fCam->getProjection() * fCam->getView() *  m_quadtransform;
	m_shader.bindUniform("ProjectionViewModel", pvm);

	m_quadmesh.draw();
	//m_circle.draw();

	//draw bunny
	m_bunnyMesh.draw();

	aie::Gizmos::draw(fCam->getProjectionView());
}