#include "FlyCamera.h"
#include"defines.h"

FlyCamera::FlyCamera(GLFWwindow* win)
{
	window = win;
	m_fspeed = 100.0f;
	m_up = glm::vec3(0, 1, 0);

	worldTransform = glm::mat4(1);
	viewTransform = glm::mat4(1);
	projectionTransform = glm::mat4(1);
	projectionViewTransform = glm::mat4(1);

	setPosition(glm::vec3(glm::vec3(20, 20, 20)));
	setLookAt(worldTransform[3], glm::vec3(0), m_up);
	setPerspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);

	canMoveCamera = true;

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	glfwSetCursorPos(window, resolutionX/2, resolutionY/2);
}


FlyCamera::~FlyCamera()
{
}

void FlyCamera::update(float deltaTime)
{	
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		if (canMoveCamera == true)
		{
			glfwSetCursorPos(window, resolutionX / 2, resolutionY / 2);
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		}
		
		canMoveCamera = false;
		//mouse
		glfwGetCursorPos(window, &m_mouseX, &m_mouseY);

		m_deltaMouseX = (resolutionX / 2 - m_mouseX) * 0.9f;
		m_deltaMouseY = (resolutionY / 2 - m_mouseY) * 0.9f;

		//lock cursor - hardcoded
		glfwSetCursorPos(window, resolutionX / 2, resolutionY / 2);
		//rotate around world up
		glm::vec4 up = glm::inverse(worldTransform) * glm::vec4(0, 1, 0, 0);

		glm::mat4 rotmat(1);
		//rotate around world up
		rotmat = glm::rotate((float)-m_deltaMouseX * deltaTime, glm::vec3(up[0], up[1], up[2]));
		viewTransform = rotmat * viewTransform;
		//rotate up/down
		rotmat = glm::rotate((float)-m_deltaMouseY * deltaTime, glm::vec3(1, 0, 0));
		viewTransform = rotmat * viewTransform;
		//world transform update
		worldTransform = glm::inverse(viewTransform);
		//keyboard
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			worldTransform[3] += worldTransform[2] * deltaTime * -m_fspeed;
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			worldTransform[3] += worldTransform[2] * deltaTime * m_fspeed;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			worldTransform[3] += worldTransform[0] * deltaTime * -m_fspeed;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			worldTransform[3] += worldTransform[0] * deltaTime * m_fspeed;
		}
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			worldTransform[3] += worldTransform[1] * deltaTime * m_fspeed;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			worldTransform[3] += worldTransform[1] * deltaTime * -m_fspeed;
		}

		worldTransform[3][3] = 1.0f;
		viewTransform = glm::inverse(worldTransform);
		updateProjectionViewTransform();
	}
	else
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		canMoveCamera = true;
	}
}