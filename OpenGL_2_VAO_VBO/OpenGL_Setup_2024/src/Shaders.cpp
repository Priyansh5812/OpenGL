#include "Shaders.h"

Shaders::Shaders() : shaderProgram(glCreateProgram()) 
{}


unsigned int Shaders :: CompileShader(ShaderType type, const char* source)
{
	unsigned int shader = glCreateShader(type == VERTEX ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
	glShaderSource(shader, 1 ,&source, NULL);
	glCompileShader(shader);
	CheckShaderCompilation(shader , type);
	return shader;
}

bool Shaders::CheckShaderCompilation(unsigned int shader, ShaderType type)
{	
	int success;
	char infoLog[512];
	glGetShaderiv(shader,GL_COMPILE_STATUS, &success);

	if(!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << infoLog << std::endl;
		return false;
	}
	else
	{
		std::cout << (type == VERTEX ? "Vertex Shader " : "Fragment Shader ") << "Compiled Successfully" << std::endl;
		return true;
	}
}

void Shaders::AttachShader(unsigned int shader)
{
	glAttachShader(shaderProgram, shader);
}

bool Shaders::LinkProgram()
{
	glLinkProgram(shaderProgram);
	//--------- Checking Link Status ------------
	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << infoLog << std::endl;
		return false;
	}
	else
	{
		std::cout << "Shader Program Linking Success" << std::endl;
		return true;
	}

}