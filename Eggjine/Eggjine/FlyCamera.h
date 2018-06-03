#ifndef __FLYCAMERA_H_
#define __FLYCAMERA_H_

#include"Camera.h"
#include"glfw3.h"

class FlyCamera : public Camera
{
public:
	FlyCamera(GLFWwindow* win);
	~FlyCamera();

	void update(float deltaTime);
	void setSpeed(float speed) { m_fspeed = speed; }

protected:
	float m_fspeed;
	glm::vec3 m_up;

	double m_mouseX;
	double m_mouseY;

	double m_deltaMouseX;
	double m_deltaMouseY;
};

#endif