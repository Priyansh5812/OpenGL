#include "ShaderHandler.h"


unsigned int CreateProgram(const char* vertexShaderSource, const char* fragmentShaderSource)
{
	unsigned int programId = glCreateProgram();

	unsigned int vertexShaderId = GetCompiledProgram(GL_VERTEX_SHADER , vertexShaderSource);
	unsigned int fragmentShaderId = GetCompiledProgram(GL_FRAGMENT_SHADER , fragmentShaderSource);

	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glLinkProgram(programId);
	glValidateProgram(programId);
	return programId;
}
unsigned int GetCompiledProgram(unsigned int type, const char* shaderSource)
{
	unsigned int shaderId = glCreateShader(type);
	glShaderSource(shaderId,1,&shaderSource,NULL);

	glCompileShader(shaderId);

	int result; 
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result); 

	if (!result) 
	{ 
		int length;  
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length); 
		char* message = (char*)alloca(length * sizeof(char)); 
		glGetShaderInfoLog(shaderId, length, &length, message);  
		std::cout << "Failed to Compile " << ((type == GL_VERTEX_SHADER) ? ("Vertex") : ("Fragment")) << " Shader" << std::endl; 
		std::cout << message << std::endl; 
	} 
	return shaderId;

}