#ifndef __GAMEOBJECT_H_
#define __GAMEOBJECT_H_

//#include"Mesh.h"
#include"OBJMesh.h"
#include"FlyCamera.h"
#include"Shader.h"
#include"Light.h"
#include<vector>
#include"RenderTarget.h"

class GameObject
{
public:
	GameObject() { m_myImportedMesh = nullptr; m_shaderReference = nullptr; camReference = nullptr; }
	GameObject(aie::OBJMesh*, FlyCamera*, aie::ShaderProgram*);
	~GameObject();

	void CreateLight(glm::vec3 lightDirection, glm::vec3 lightDiffuse, glm::vec3 lightSpecular, glm::vec3 ambLight, float m_SpecularPower);
	void CreateLight(Light l, glm::vec3 amb, float m_SpecularPower);
	
	void draw(FlyCamera*, aie::ShaderProgram*);
	//void drawNormal(FlyCamera* f, aie::RenderTarget*);

	glm::mat4 getTransform() { return m_transform; }
	void SetTransform(glm::mat4 m) { m_transform = m; }

private:
	aie::OBJMesh* m_myImportedMesh;
	aie::ShaderProgram* m_shaderReference;
	FlyCamera *camReference;

	glm::mat4 m_transform;
	
	//lights
	std::vector<Light> lightsList;
	glm::vec3 ambientLight;
	float m_specLight;
};
#endif