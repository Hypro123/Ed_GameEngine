#include "Application.h"
#include"defines.h"
#include"Mesh.h"

Application::Application() {}


Application::~Application() {}

int Application::Initialise()
{
	m_IsRunning = true;
	m_startTime = myClock.now();
	m_currentTime = myClock.now();
	m_prevTime = myClock.now();

	//If, we can hook into the GPU
	if (glfwInit() == false)
	{
		//-1 is failure code
		return -1;
	}
	window = glfwCreateWindow(resolutionX, resolutionY, "Eggjine", nullptr, nullptr); //last 2 pointers allow for fullscreen/windowed, screen pointer

	if (window == nullptr)
	{
		//Clean up window and GPU linkage
		glfwTerminate();
		return -2;
	}

	//bring to front
	glfwMakeContextCurrent(window);

	// before loading interface functions
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED) {
		glfwDestroyWindow(window);
		glfwTerminate();
		return -3;
	}

	//Open GL version
	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();
	printf("GL: %i.%i\n", major, minor);
}

void Application::run()
{

	glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	aie::Gizmos::create(10000, 10000, 10000, 10000);
	Mesh::Create();

	if (startup())
	{

		while (glfwWindowShouldClose(window) == false &&
			m_IsRunning) {
			//DeltaTime calculations
			m_prevTime = m_currentTime;
			m_currentTime = myClock.now();
			auto difference = m_currentTime - m_prevTime;
			float deltaTime = difference.count() * NANO_TO_SECONDS;

			//Clearing buffer - Colour and depth checks
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// our game logic and update code goes here!
			// so does our render code!

			aie::Gizmos::clear();

			if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			{
				m_IsRunning = false;
			}

			update(deltaTime);
			draw();

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		//cleanup
		shutdown();
		terminate();
	}
}

void Application::clearScreen() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Application::terminate()
{	
	aie::Gizmos::destroy();
	Mesh::Destroy();
	glfwDestroyWindow(window);
	glfwTerminate();
}