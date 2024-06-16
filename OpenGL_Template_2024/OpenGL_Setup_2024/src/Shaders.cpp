#include "Shaders.h"

Shaders::Shaders() : shaderProgram(glCreateProgram()) 
{}


bool Shaders::ParseShader(std::string path, ShaderType type)
{
	std::ifstream myfile(path);
	std::string str, shader;
	if (myfile.is_open())
	{
		while (std::getline(myfile, str))
		{
			shader += str;
			shader += "\n";
			//...
		}

		std::cout << "File read on path " << path << " was Successful" << std::endl;
		
		((type == ShaderType::VERTEX) ? (this->vertexShader) : (this->fragmentShader)) = shader;	
		return true;
	}
	else
	{	
		std::cout << "File on path " << path << " not found";
		return false;
	}
}

unsigned int Shaders :: CompileShader(ShaderType type)
{
	unsigned int shader = glCreateShader(type == VERTEX ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
	const char* src = (type == ShaderType::VERTEX) ? (&this->vertexShader[0]) : (&this->fragmentShader[0]);
	glShaderSource(shader, 1 ,&src, NULL);
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

std::string Shaders::GetShader(ShaderType type)
{
	return ((type == ShaderType::VERTEX) ? (this->vertexShader) : (this->fragmentShader));
}