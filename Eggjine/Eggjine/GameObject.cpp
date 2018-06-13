#include "GameObject.h"



GameObject::GameObject(Mesh* m, FlyCamera *c, aie::ShaderProgram* s)
{
	m_myMesh = m;
	m_shaderReference = s;
	camReference = c;
	m_myImportedMesh = nullptr;
}

GameObject::GameObject(aie::OBJMesh* m, FlyCamera *c, aie::ShaderProgram* s)
{
	m_myMesh = nullptr;
	m_shaderReference = s;
	camReference = c;
	m_myImportedMesh = m;
}

GameObject::~GameObject()
{
	delete m_shaderReference;
	delete camReference;
	
	if (m_myMesh != nullptr)
		delete m_myMesh;
	else
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

void GameObject::update()
{
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

		if (m_myMesh != nullptr)
		{
			m_shaderReference->bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_transform)));
			m_myMesh->draw();
		}
		else
		{
			m_shaderReference->bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_transform)));
			m_myImportedMesh->draw();
		}
	}
}