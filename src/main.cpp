#define GLFW_INCLUDE_NONE

#include <filesystem>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include <fstream>


std::string readFile(std::filesystem::path path)
{
    std::ifstream in(path, std::ios::binary);
    const auto sz = std::filesystem::file_size(path);
    std::string result(sz, '\0');
    in.read(result.data(), sz);

    return result;

}

unsigned int compileShader(unsigned int shaderType, const std::string& src)
{
    unsigned id = glCreateShader(shaderType);
    const char* raw = src.c_str();
    glShaderSource(id, 1, &raw, nullptr);
    glCompileShader(id);
    return id;
}

unsigned int createShader(std::string& vertex, std::string& fragmet)
{
    unsigned vs = compileShader(GL_VERTEX_SHADER, vertex);
    unsigned fs = compileShader(GL_FRAGMENT_SHADER, fragmet);

    unsigned program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}


int main()
{

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow *window = glfwCreateWindow(1280, 720, "GraphX", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cout << "Failde to initialize OpenGL context" << std::endl;
        return -1;
    }


    const GLfloat quadVertices[] = { 1.0, -1.0, 1.0, 1.0, -1.0, -1.0, -1.0, 1.0 };

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), quadVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    std::string vertex = readFile(R"(C:\Users\zzoom\CLionProjects\GraphX\src\vertical.shader)");
    std::string fragment = readFile(R"(C:\Users\zzoom\CLionProjects\GraphX\src\fragment.shader)");

    unsigned int shader = createShader(vertex, fragment);

    glUseProgram(shader);

    glUniform2f(glGetUniformLocation(shader, "iResolution"), 1280, 720);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glUniform1f(glGetUniformLocation(shader, "iTime"), glfwGetTime());
        glUseProgram(shader);

        glVertexPointer(3, GL_FLOAT, 0, quadVertices);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();


    }

    glfwTerminate();
    return 0;
}