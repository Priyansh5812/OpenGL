#include <Main.h>
#include <ShaderHandler.h>


int main(void)
{   
    
    GLFWwindow* window;

    InitializeGLFW();

    window = GetWindowContext("Triangle With Indices", 800, 600, NULL, NULL);

    InitializeGLEW();
    glfwSetKeyCallback(window, SetKeyCallbacks);
    SetupBufferSystem();

    const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
    const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";

    unsigned int shaderProgram = CreateProgram(vertexShaderSource, fragmentShaderSource);
    glUseProgram(shaderProgram);


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


#pragma region Function Definations

inline bool InitializeGLFW()
{
    return glfwInit();
}

GLFWwindow* GetWindowContext(const char* title , int resX , int resY, GLFWmonitor* monitor, GLFWwindow* share)
{   

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_RESIZABLE, true);

    GLFWwindow* window = glfwCreateWindow(resX, resY, title, monitor, share);

    if (!window)
        std::cout << "Window not created" << std::endl;
    else
        glfwMakeContextCurrent(window);
    

    glViewport(0, 0, resX, resY);
    return window;


}

bool InitializeGLEW()
{   

    bool res;
    if (glewInit() != GLEW_OK)
        res = false;
    else
    {
        res = true;
        std::cout << "GLEW Initialized Sucessfully \nversion : " << glGetString(GL_VERSION) << std::endl;
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

    float vertices[] =
    {
        -0.5f , 0.5f, 0.0f,
        -0.5f , -0.5f, 0.0f,
        0.5f , -0.5f, 0.0f,
        0.5f , 0.5f, 0.0f,
       


    };

    unsigned int buffer, array;
    glGenBuffers(1, &buffer);
    glGenVertexArrays(1, &array);
    glBindBuffer(GL_ARRAY_BUFFER, buffer); 
    glBindVertexArray(array); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 18, vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(float) , (void*)0);
    glEnableVertexAttribArray(0);
}

void OnTick(GLFWwindow* window)
{   

    glDrawArrays(GL_LINE_LOOP, 0, 6); 

}





#pragma endregion Function Definations
