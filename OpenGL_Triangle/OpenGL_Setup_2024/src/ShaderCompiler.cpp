#include "ShaderCompiler.h"


ui ShaderHandler::CreateProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
{
	ui programId = glCreateProgram();
	ui vertexShader = CompileShader(vertexShaderSource, GL_VERTEX_SHADER);
	ui fragmentShader = CompileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

	//Attach both the Shaders in order to link them into one single Shader program object can be run.
	glAttachShader(programId, vertexShader); 
	glAttachShader(programId, fragmentShader);
	glLinkProgram(programId); // Links all attached shaders in one single shader program object.
	glValidateProgram(programId);  // Checks whether the Linked program is fine for execution or not.

	return programId; 
	
}


ui ShaderHandler::CompileShader(const std::string& source, const ui& type)
{ 
	ui shaderId = glCreateShader(type); 
	const char* srcPtr = source.c_str();
	glShaderSource(shaderId,1,&srcPtr,nullptr); 
	glCompileShader(shaderId);

	int result;
	glGetShaderiv(shaderId , GL_COMPILE_STATUS, &result);

	if(!result)
	{ 
		int length;
		glGetShaderiv(shaderId , GL_INFO_LOG_LENGTH , &length);
		char* message = (char*)alloca(length * sizeof(char)); 
		glGetShaderInfoLog(shaderId, length, &length, message);
		std::cout << "Failed to Compile " << ((type == GL_VERTEX_SHADER)?("Vertex"):("Fragment")) <<  " Shader" << std::endl;
 		std::cout << message << std::endl;
	} 


	return shaderId; 
}
