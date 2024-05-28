#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>


unsigned int CreateProgram(const char* vertexShaderSource, const char* fragmentShaderSource);
unsigned int GetCompiledProgram(unsigned int type, const char* shaderSource);


