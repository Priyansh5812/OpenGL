#pragma 
#include <iostream>
#include <GL/glew.h>
#include <string>
#include <fstream>
enum ShaderType
{
	VERTEX,
	FRAGMENT
};

class Shaders
{	

public:

	

	unsigned int shaderProgram;

	//-------- Functions-----------
	bool ParseShader(std::string path, ShaderType type);
	unsigned int CompileShader(ShaderType type);
	void AttachShader(unsigned int shader);
	bool LinkProgram();
	std::string GetShader(ShaderType type);

	Shaders();

private:
	std::string vertexShader;	
	std::string fragmentShader;	
	bool CheckShaderCompilation(unsigned int shader, ShaderType type);
	
};