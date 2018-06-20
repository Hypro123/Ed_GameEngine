#include "GameObject.h"

GameObject::GameObject(aie::OBJMesh* m, FlyCamera *c, aie::ShaderProgram* s)
{
	m_shaderReference = s;
	camReference = c;
	m_myImportedMesh = m;
}

GameObject::~GameObject()
{
	delete m_shaderReference;
	delete camReference;
	delete m_myImportedMesh;

	lightsList.clear();
}

void GameObject::CreateLight(glm::vec3 lightDirection, glm::vec3 lightDiffuse, glm::vec3 lightSpecular, glm::vec3 ambLight, float spec)
{
	Light l;
	l.direction = lightDirection;
	l.diffuse = lightDiffuse;
	l.specular = lightSpecular;
	ambientLight = ambLight;
	m_specLight = spec;

	lightsList.push_back(l);
}

void GameObject::CreateLight(Light l, glm::vec3 amb, float spec)
{
	ambientLight = amb;
	m_specLight = spec;
	lightsList.push_back(l);
}

void GameObject::draw(FlyCamera* f, aie::ShaderProgram* rt)
{
	camReference = f;
	rt->bind();
	rt->bindUniform("cameraPosition", camReference->getWorldTransform()[3]);

	for (int i = 0; i < lightsList.size(); i++)
	{
		rt->bindUniform("lightDirection", lightsList[i].direction);
		rt->bindUniform("Ia", ambientLight);
		rt->bindUniform("Id", lightsList[i].diffuse);
		rt->bindUniform("Is", lightsList[i].specular);
		rt->bindUniform("specularPower", m_specLight);

		auto pvm = camReference->getProjection() * camReference->getView() * m_transform;
		m_shaderReference->bindUniform("ProjectionViewModel", pvm);

		m_shaderReference->bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_transform)));
		m_myImportedMesh->draw();
	}
}