#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shaders.h"


void IniGLFW();
void IniGLEW();
GLFWwindow* GetWindow();
void ProcessEvents(GLFWwindow* win);
Shaders* SetupShaders();

bool isWireframe = false;

typedef unsigned int Uint;

int main() 
{	
	
	IniGLFW();
	
	GLFWwindow* win = GetWindow();
	IniGLEW();

	Shaders* sh = SetupShaders();	


	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // left  
		 0.5f, -0.5f, 0.0f, // right 
		 0.0f,  0.5f, 0.0f  // top   
	};

	Uint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);


	while (win && !glfwWindowShouldClose(win)) 
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(sh->shaderProgram);
		glBindVertexArray(VAO);	
		glDrawArrays(GL_TRIANGLES, 0, 3);	
		ProcessEvents(win); 
		glfwSwapBuffers(win);
		glfwPollEvents();
	}

	return 0;
}



Shaders* SetupShaders()
{
	Shaders* sh = new Shaders();

	sh->ParseShader("src/shaders/vertex.shader", ShaderType::VERTEX);
	sh->ParseShader("src/shaders/fragment.shader", ShaderType::FRAGMENT);

	Uint vertexShader, fragmentShader;

	vertexShader = sh->CompileShader(ShaderType::VERTEX);
	fragmentShader = sh->CompileShader(ShaderType::FRAGMENT);

	sh->AttachShader(vertexShader);
	sh->AttachShader(fragmentShader);

	sh->LinkProgram();	

	return sh;
}




void IniGLFW()
{
	if (!glfwInit())
	{
		std::cout << "GLFW not Initialized" << std::endl;
		return;
	}

	//----- Making Hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
}

void IniGLEW()
{
	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW not initialized" << std::endl;
	}
	else
	{
		std::cout << "GLEW Initialized with version : " << glGetString(GL_VERSION) << std::endl;
	}

	
}

GLFWwindow* GetWindow()
{
	GLFWwindow* win = glfwCreateWindow(800, 600, "Quad", NULL, NULL);
	if (!win)
		std::cout << "Window not created, returned NULL" << std::endl;
	else
	{
		glfwMakeContextCurrent(win);
		glViewport(0, 0, 800, 600);
	}
	return win;	
}


void ProcessEvents(GLFWwindow* win)
{
	if (glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(win, true);
		
	}

}



