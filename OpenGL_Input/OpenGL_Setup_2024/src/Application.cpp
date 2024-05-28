#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include <iostream>
#include "GetTime.h"
#include <future>
#pragma region OpenGL Initialization
bool InitializeGLFW();
GLFWwindow* SetGLFWContext(bool glfwStatus, int verMajor, int verMinor, bool isCoreProfile);
void Update(GLFWwindow* win);
#pragma endregion



int main()
{	
	GLFWwindow* window = SetGLFWContext(InitializeGLFW(), 4, 4 , true);
	
	Update(window);

	glfwTerminate();
}



bool InitializeGLFW()
{

	if (glfwInit() != GLFW_TRUE)
	{
		std::cout << "GLFW not Initialized" << std::endl;
		return false;
	}

	return true;

}

GLFWwindow* SetGLFWContext(bool glfwStatus , int verMajor, int verMinor , bool isCoreProfile)
{	
	

	GLFWwindow* window = NULL;
	if (!glfwStatus)
	{
		std::cout << "GLFW not initialized" << std::endl;
		return window;
	}

	// Setting Hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, verMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, verMinor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, (isCoreProfile) ? (GLFW_OPENGL_CORE_PROFILE) : (GLFW_OPENGL_COMPAT_PROFILE));
	glfwWindowHint(GLFW_RESIZABLE, true);
	if (!isCoreProfile)
		std::cout << "Compat profile hinted, Deprecated features included" << std::endl;

	window = glfwCreateWindow(800, 600, "InputDemo", NULL, NULL);

	if (!window)
	{
		std::cout << "Window not created" << std::endl;
		return window;
	}
		

	glfwMakeContextCurrent(window);
	return window;

}

void Update(GLFWwindow* win)
{	
	GetTime::StartCalculateDeltaTime();

	
	while (!glfwWindowShouldClose(win))
	{	
		/*GetTime::currTime = std::chrono::high_resolution_clock::now();
		std::cout << std :: chrono :: duration<float>(GetTime::currTime - GetTime :: lastTime).count() << std::endl;*/
		std::cout << GetTime::deltaTime << std::endl;
		glClearColor(1, 0, 0, 1); 
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(win);
		glfwPollEvents();
		//GetTime::lastTime = GetTime::currTime;

	}

	GetTime::StopCalculateDeltaTime();
}

