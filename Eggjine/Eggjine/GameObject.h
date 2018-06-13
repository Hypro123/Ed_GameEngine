#ifndef __GAMEOBJECT_H_
#define __GAMEOBJECT_H_

#include"Mesh.h"
#include"OBJMesh.h"
#include"FlyCamera.h"
#include"Shader.h"
#include"Light.h"
#include<vector>

class GameObject
{
public:
	GameObject(Mesh*, FlyCamera*, aie::ShaderProgram*);
	GameObject(aie::OBJMesh*, FlyCamera*, aie::ShaderProgram*);
	~GameObject();

	void CreateLight(glm::vec3 lightDirection, glm::vec3 lightDiffuse, glm::vec3 lightSpecular, glm::vec3 ambLight);

	void update();

	glm::mat4 getTransform() { return m_transform; }
	void SetTransform(glm::mat4 m) { m_transform = m; }

private:
	//gameobject
	GameObject() {}

	Mesh* m_myMesh;
	aie::OBJMesh* m_myImportedMesh;
	aie::ShaderProgram* m_shaderReference;
	FlyCamera *camReference;

	glm::mat4 m_transform;
	
	//lights
	std::vector<Light> lightsList;
	glm::vec3 ambientLight;
};
#endif