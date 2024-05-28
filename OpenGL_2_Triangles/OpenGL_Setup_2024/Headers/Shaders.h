#pragma 
#include <iostream>
#include <GL/glew.h>
enum ShaderType
{
	VERTEX,
	FRAGMENT
};

class Shaders
{	

public:
	unsigned int shaderProgram;
	unsigned int CompileShader(ShaderType type, const char* source);
	void AttachShader(unsigned int shader);
	bool LinkProgram();
	Shaders();

private:
	
	bool CheckShaderCompilation(unsigned int shader, ShaderType type);
	
};