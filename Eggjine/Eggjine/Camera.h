#ifndef __CAMERA_H_
#define __CAMERA_H_

#include<ext.hpp>
#include"glfw3.h"
#include"gtc\quaternion.hpp"
#include"gtx\quaternion.hpp"

class Camera
{
public:
	Camera();
	~Camera();

	virtual void update(float deltaTime) = 0;
	void updateProjectionViewTransform();
	
	void setPerspective(float fieldOfView, float aspectRatio, float near, float far);
	void setLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up);
	void setPosition(glm::vec3 position);
	glm::mat4 getWorldTransform() { return worldTransform; }
	glm::mat4 getView() { return viewTransform; }
	glm::mat4 getProjection() { return projectionTransform; }
	glm::mat4 getProjectionView() { return projectionViewTransform; }


protected:
	glm::mat4 worldTransform;
	glm::mat4 viewTransform;
	glm::mat4 projectionTransform;
	glm::mat4 projectionViewTransform;
	GLFWwindow* window;
};

#endif