#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "ShaderCompiler.h"

inline bool InitializeGLFW();
GLFWwindow* GetWindowContext(const char* title, int resX, int resY, GLFWmonitor* monitor, GLFWwindow* share);
bool InitializeGLEW();
void OnTick(GLFWwindow* window);
void SetKeyCallbacks(GLFWwindow* window, int key, int scancode, int action, int mods);
void SetupBufferSystem();

int main(void)
{   
    
    GLFWwindow* window;

    InitializeGLFW();

    window = GetWindowContext("Triangle", 800, 600, NULL, NULL);

    InitializeGLEW();
    glfwSetKeyCallback(window, SetKeyCallbacks);


    SetupBufferSystem();


    const char* vertexShaderSource = "#version 330 core\n" 
        "layout (location = 0) in vec4 position;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = position;\n"
        "}\0";
    const char* fragmentShaderSource = "#version 330 core\n" 
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";


    ui shader = ShaderHandler::CreateProgram(vertexShaderSource , fragmentShaderSource);
    glUseProgram(shader);




    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);



        OnTick(window);



        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    

    glfwTerminate();
    return 0;
}


inline bool InitializeGLFW()
{
    bool res = true;
    if (!glfwInit())
        res = false;
    return res;
}

GLFWwindow* GetWindowContext(const char* title , int resX , int resY, GLFWmonitor* monitor, GLFWwindow* share)
{   

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, true);

    GLFWwindow* window = glfwCreateWindow(resX, resY, title, monitor, share);

    if (!window)
    {
        std::cout << "Window not created" << std::endl; 
        return window;
    }
    glfwMakeContextCurrent(window);
    glViewport(0, 0, resX, resY);
    return window;

}

bool InitializeGLEW()
{   
    bool res = true;
    if (glewInit() != GLEW_OK)
    {   
        res = false;
        std::cout << "GLEW not Initialized" << std::endl;
    }
    else
    {
        std::cout << "GLEW Initialized Successfully \nversion : " << glGetString(GL_VERSION) << std::endl;
        
    }
    return res;
}


void SetKeyCallbacks(GLFWwindow* window , int key , int scancode, int action , int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

}


void SetupBufferSystem()
{   

    float vertices[9] =
    {
     -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
    };

    unsigned int buffer , array;
    glGenBuffers(1,&buffer); // VBO
    glBindBuffer(GL_ARRAY_BUFFER , buffer); //VBO
    glGenVertexArrays(1, &array); //VAO 
    glBindVertexArray(array);//VAO 
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), vertices, GL_STATIC_DRAW); //VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3 , 0); //VAO
    glEnableVertexAttribArray(0); //VAO
    

}

void OnTick(GLFWwindow* window)
{   

    glDrawArrays(GL_TRIANGLES, 0, 3);

}
//Vertex Buffer Objects(VBOs) and Vertex Array Objects(VAOs) are both crucial components in modern OpenGL rendering, but they serve different purposes and represent different aspects of the rendering pipeline.
//
//Here's how they differ:
//
//Vertex Buffer Object(VBO) :
//
//    A VBO is a buffer object used to store vertex data, such as positions, colors, normals, and texture coordinates.
//    It provides efficient storage for large amounts of vertex data on the GPU.
//    VBOs are bound to the GL_ARRAY_BUFFER target using glBindBuffer.
//    Vertex attribute data is uploaded to VBOs using glBufferData or glBufferSubData.
//    VBOs are associated with vertex attribute pointers using glVertexAttribPointer.
//    Vertex Array Object(VAO) :
//
//    A VAO is an object that encapsulates the configuration of vertex attribute pointers and their associated VBOs.
//    It stores the state of the vertex attribute configuration, including the format of vertex data and the VBO bindings.
//    VAOs are bound using glBindVertexArray.
//    Vertex attribute pointers are configured within the VAO using glVertexAttribPointer.
//    VAOs can be used to quickly switch between different sets of vertex attribute configurations without re - specifying vertex attribute pointers.
//    In summary, VBOs are used to store vertex data on the GPU, while VAOs are used to encapsulate and manage the configuration of vertex attribute pointers.VBOs and VAOs work together to efficiently render geometry in modern OpenGL applications.
//


