#include "Camera.h"



Camera::Camera()
{

}


Camera::~Camera()
{
}

void Camera::updateProjectionViewTransform()
{
	projectionViewTransform = projectionTransform * viewTransform;
}

void Camera::setPerspective(float fieldOfView, float aspectRatio, float near, float far) 
{
	projectionTransform = glm::perspective(fieldOfView, aspectRatio, near, far);
	updateProjectionViewTransform();
}

void Camera::setLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up) 
{
	viewTransform = glm::lookAt(from, to, up);
	updateProjectionViewTransform();
}

void Camera::setPosition(glm::vec3 position) 
{
	worldTransform[3] = glm::vec4(position, worldTransform[3][3]);
	updateProjectionViewTransform();
}