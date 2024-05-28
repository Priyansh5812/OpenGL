#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Shaders.h"

void IniGLFW();
void IniGLEW();
GLFWwindow* GetWindow();
void ProcessEvents(GLFWwindow* win);

const char* vertexShaderSource1 = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource1 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.0f, 0.0f, 0.85f);\n"

"}\n\0";const char* fragmentShaderSource2 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 0.2f, 1.0f);\n"
"}\n\0";


bool isWireframe = false;

int main() 
{	
	
	IniGLFW();
	
	GLFWwindow* win = GetWindow();
	IniGLEW();

	Shaders* sh[] =
	{
		new Shaders(),
		new Shaders()
	};

	unsigned int vertexShaders[2], fragmentShaders[2];


	vertexShaders[0] = sh[0]->CompileShader(VERTEX, vertexShaderSource1);	
	vertexShaders[1] = sh[1]->CompileShader(VERTEX, vertexShaderSource1);	

	fragmentShaders[0] = sh[0]->CompileShader(FRAGMENT, fragmentShaderSource1);	
	fragmentShaders[1] = sh[1]->CompileShader(FRAGMENT, fragmentShaderSource2);	

	sh[0]->AttachShader(vertexShaders[0]);
	sh[0]->AttachShader(fragmentShaders[0]);

	sh[0]->LinkProgram();

	sh[1]->AttachShader(vertexShaders[1]);
	sh[1]->AttachShader(fragmentShaders[1]);

	sh[1]->LinkProgram();



	float vertices1[] =
	{
		-0.7f,  0.4f , 0.0f,
		-1.0f, -0.2f , 0.0f,
		-0.4f, -0.2f , 0.0f


	};

	 
	float vertices2[] = 
	{
		0.7f,  0.4f , 0.0f,
		1.0f, -0.2f , 0.0f,
		0.4f, -0.2f , 0.0f
	};



	unsigned int VBO[2], VAO[2];

	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);

	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9, vertices1, GL_STATIC_DRAW); 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glEnableVertexAttribArray(0); 

	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9, vertices2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0); 
	glEnableVertexAttribArray(0); 
	 
	

	while (win && !glfwWindowShouldClose(win)) 
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		 

		glUseProgram(sh[0]->shaderProgram);
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(sh[1]->shaderProgram);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		ProcessEvents(win); 
		glfwSwapBuffers(win);
		glfwPollEvents();
	}

	return 0;
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
	GLFWwindow* win = glfwCreateWindow(800, 600, "Dual_VAO_VBO_Test", NULL, NULL);
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



