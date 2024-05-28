#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>



inline bool InitializeGLFW();
GLFWwindow* GetWindowContext(const char* title, int resX, int resY, GLFWmonitor* monitor, GLFWwindow* share);
bool InitializeGLEW();
void OnTick(GLFWwindow* window);
void SetKeyCallbacks(GLFWwindow* window, int key, int scancode, int action, int mods);
void SetupBufferSystem();