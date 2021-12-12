#ifndef GRAPHICS_APP_H
#define GRAPHICS_APP_H

// sys libraries
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <experimental/filesystem>
// OpenGL
#include <glad.h>
#include <glfw3.h>
// glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <vector>
// App files
#include "shaders/shader.h"
#include "textures/texture.h"
#include "textures/texture.h"
#include "camera/camera.h"

using glm::mat4;
using glm::vec3;
using glm::radians;
using glm::lookAt;
using std::vector;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

class App {
    const int SCR_WIDTH = 800;
    const int SCR_HEIGHT = 600;
    Shader *shader;
    Texture *texture;
    GLFWwindow *window{};
    GLuint VAO{};
    GLuint VBO{};
    GLuint EBO{};

    mat4 transform = mat4(1.0f);
    vec3 color = vec3(1.0f, 0.4f, 0.2f);

    vec3 xStart = vec3(-1.0f, 0.0f, 0.0f);
    vec3 xEnd = vec3(1.0f, 0.0f, 0.0f);
    vec3 yStart = vec3(0.0f, 1.0f, 0.0f);
    vec3 yEnd = vec3(0.0f, -1.0f, 0.0f);

    vector<float> vertices;
    vector<float> verticesY;

public:
    App() {
        initialiseWindow();
        shader = new Shader("../app/shaders/vertex.frag", "../app/shaders/fragment.frag");
        texture = new Texture();
        vertices = {
                xStart.x, xStart.y, xStart.z,
                xEnd.x, xEnd.y, xEnd.z,
                yStart.x, yStart.y, yStart.z,
                yEnd.x, yEnd.y, yEnd.z,
        };
        verticesY = {
                yStart.x, yStart.y, yStart.z,
                yEnd.x, yEnd.y, yEnd.z,
        };
    }

    static vector<vec3> f(int n) {
        vector<vec3> data;
        for (int i = 0; i <= n; i++) {
            data[i] = vec3(i, i + 12, 0.0f);
        }
        return data;
    }

    /*
     *
     */
    void run() {
        glUseProgram(shader->ID);

        while (!glfwWindowShouldClose(window)) {

            float currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            Camera::processInput(window);

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            draw();

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        close();
    }

    /*
     *
     */
    void setup() {
        initBuffers();
        bindVBO();
        printf("%d\n", GL_LINE_WIDTH);

        glLineWidth(50);
        printf("%d\n", GL_LINE_WIDTH);
//        glEnable(GL_LINE_WIDTH);
        setVertexAttrs(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    }

private:
    /*
     *
     */
    void draw() {
        shader->use();
        
        shader->setMat4("transform", transform * 20.0f);
        shader->setVec3("color", color);

        glBindVertexArray(VAO);
        glDrawArrays(GL_LINES, 0, 4);
    }



    /*
     *
     */
    void initBuffers() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
    }

    /*
     *
     */
    void bindVBO() const {
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    }

    /*
     *
     */
    void bindEBO(GLuint data[], int dataSize) const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
    }

    /*
     *
     */
    static void
    setVertexAttrs(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer) {
        glVertexAttribPointer(index, size, type, normalized, stride, pointer);
        glEnableVertexAttribArray(index);
    }

    /*
     *
     */
    void initialiseWindow() {
        // glfw: initialize and configure
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        if (IS_APPLE) {
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        }

        // glfw window creation
        window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Graph", nullptr, nullptr);
        if (window == nullptr) {
            std::cout << "Failed to create GLFW createWindow" << std::endl;
            glfwTerminate();
            exit(1);
        }

        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwSetCursorPosCallback(window, Camera::mouseCallback);
        glfwSetScrollCallback(window, Camera::scrollCallback);

//        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            std::cout << "Failed to initialize GLAD" << std::endl;
            exit(1);
        }

        glEnable(GL_DEPTH_TEST);
    }

    /*
     *
     */
    static void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
        glViewport(0, 0, width, height);
    }

    /*
     *
     */
    void close() const {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
//        glDeleteBuffers(1, &EBO);
        delete shader;
        delete texture;
        glfwTerminate();
    }


};


#endif //GRAPHICS_APP_H
