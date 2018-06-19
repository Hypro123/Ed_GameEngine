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

void GameObject::CreateLight(glm::vec3 lightDirection, glm::vec3 lightDiffuse, glm::vec3 lightSpecular, glm::vec3 ambLight)
{
	Light l;
	l.direction = lightDirection;
	l.diffuse = lightDiffuse;
	l.specular = lightSpecular;
	ambientLight = ambLight;

	lightsList.push_back(l);
}

void GameObject::CreateLight(Light l, glm::vec3 amb)
{
	ambientLight = amb;
	lightsList.push_back(l);
}

void GameObject::update(FlyCamera* f, aie::RenderTarget* rt)
{
	rt->bind();
	camReference = f;
	m_shaderReference->bind();
	m_shaderReference->bindUniform("cameraPosition", camReference->getWorldTransform()[3]);

	for (int i = 0; i < lightsList.size(); i++)
	{
		m_shaderReference->bindUniform("lightDirection", lightsList[i].direction);
		m_shaderReference->bindUniform("Ia", ambientLight);
		m_shaderReference->bindUniform("Id", lightsList[i].diffuse);
		m_shaderReference->bindUniform("Is", lightsList[i].specular);

		auto pvm = camReference->getProjection() * camReference->getView() * m_transform;
		m_shaderReference->bindUniform("ProjectionViewModel", pvm);

		m_shaderReference->bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_transform)));
		m_myImportedMesh->draw();
	}
	rt->unbind();

}

void GameObject::drawNormal(FlyCamera* f, aie::RenderTarget* rt)
{
	camReference = f;
	m_shaderReference->bind();
	auto pvm = camReference->getProjection() * camReference->getView() * m_transform;
	m_shaderReference->bindUniform("ProjectionViewModel", pvm);
	m_shaderReference->bindUniform("diffuseTexture", 0);
	rt->getTarget(0).bind(0);
	m_myImportedMesh->draw();
}