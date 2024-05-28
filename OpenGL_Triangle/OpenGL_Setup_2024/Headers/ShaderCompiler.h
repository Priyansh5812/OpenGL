#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>

typedef unsigned int ui;

class ShaderHandler
{
public:
	static ui CreateProgram(const std :: string& vertexShader , const std :: string& fragmentShader);
	static ui CompileShader(const std::string& source, const ui& type);

};