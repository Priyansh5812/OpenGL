#version 330 core

layout (location = 1) in vec3 position;
out vec4 vertexColor;

void main()
{
	gl_Position = vec4(position , 1.0);
	vertexColor = vec4(0.0,1.0,0.0,1.0);
}