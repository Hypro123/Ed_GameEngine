#ifndef __APP_H_
#define __APP_H_

#include<glm.hpp>
#include<ext.hpp>

#include"../dependencies/glCore/gl_core_4_5.h"
#include"glfw3.h"
#include<chrono>

#include"Gizmos.h"

using ullong = unsigned long long;
using nanoseconds = std::chrono::nanoseconds;

static const double NANO_TO_SECONDS = 0.0000000001;
static const ullong NANO_IN_SECONDS = 1000000000ULL;

namespace egg
{
	using clock = std::chrono::high_resolution_clock;
	using time = std::chrono::time_point<clock>;
};

class Application
{
public:
	Application();
	~Application();

	int Initialise(); //initialise
	void run(); //runs main loop
	void terminate(); //Clean Up

protected:
	virtual bool startup() = 0;
	virtual void shutdown() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void draw() = 0;

	void clearScreen();

protected:
	GLFWwindow * window;
	
	egg::clock myClock;
	egg::time m_startTime;
	egg::time m_currentTime;
	egg::time m_prevTime;

	bool m_IsRunning;
};

#endif