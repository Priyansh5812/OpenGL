#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Shaders.h"

void IniGLFW();
void IniGLEW();
GLFWwindow* GetWindow();
void ProcessEvents(GLFWwindow* win);
void ToggleWireframe(GLFWwindow* win, int key, int scanCode, int action, int mods);

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

bool isWireframe = false;

int main()
{

	IniGLFW();

	GLFWwindow* win = GetWindow();
	IniGLEW();

	float vertices[] =
	{
		-0.75f, 0.75f, 0.0f,
		-0.75f, -0.75f , 0.0f,
		0.75f, -0.75f, 0.0f,
		0.75f, 0.75f, 0.0f

	};

	unsigned int indices[] =
	{
		0 , 1 , 2,
		0 , 2 , 3
	};

	unsigned int VBO = -1, VAO, EBO;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


#pragma region Shader

	Shaders sh;
	unsigned int vertexShaderProg, fragShaderProg;
	vertexShaderProg = sh.CompileShader(VERTEX, vertexShaderSource);
	fragShaderProg = sh.CompileShader(FRAGMENT, fragmentShaderSource);

	sh.AttachShader(vertexShaderProg);
	sh.AttachShader(fragShaderProg);
	sh.LinkProgram();

	glUseProgram(sh.shaderProgram);
#pragma endregion Shader
	glfwSetKeyCallback(win, ToggleWireframe);

	while (win && !glfwWindowShouldClose(win))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		std::cout << glfwGetTime() << std::endl;

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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

void ToggleWireframe(GLFWwindow* win, int key, int scanCode, int action, int mods)
{
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		if (isWireframe)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		isWireframe = !isWireframe;
	}
}

