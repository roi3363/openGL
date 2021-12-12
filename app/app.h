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
// App files
#include "shaders/shader.h"
#include "textures/texture.h"
#include "textures/texture.h"
#include "camera/camera.h"


float vertices[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
};

// world space positions of our cubes
glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)
};

float deltaTime = 0.0f;
float lastFrame = 0.0f;

class App {
    const int SCR_WIDTH = 800;
    const int SCR_HEIGHT = 600;
    Shader *shader;
    Texture *texture;
public:
    GLFWwindow *window{};
    GLuint VAO{};
    GLuint VBO{};
    GLuint EBO{};

    App() {
        initialiseWindow();
        shader = new Shader("../app/shaders/vertex.frag", "../app/shaders/fragment.frag");
        texture = new Texture();
    }

    /*
     *
     */
    void run() const {
        glUseProgram(shader->ID);

        GLuint texture1 = Texture::loadTexture("../images/container.jpg", GL_RGB, shader, 0);
        GLuint texture2 = Texture::loadTexture("../images/awesomeface.png", GL_RGBA, shader, 1);

        while (!glfwWindowShouldClose(window)) {
            float currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            Camera::processInput(window);

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            Texture::activateTexture(texture1, GL_TEXTURE0);
            Texture::activateTexture(texture2, GL_TEXTURE1);

            shader->use();

            // Projection
            glm::mat4 projection = glm::mat4(1.0f);
            projection = glm::perspective(glm::radians(fov), (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f, 100.0f);
            shader->setMat4("projection", projection);

            // View
            glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
            shader->setMat4("view", view);

            glBindVertexArray(VAO);
            for (auto & cubePosition : cubePositions) {
                // Model
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, cubePosition);
                model = glm::rotate(model, (float) glfwGetTime(), glm::vec3(1.0f, 0.3f, 0.5f));
                shader->setMat4("model", model);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    /*
     *
     */
    void setup() {
        initBuffers();
        bindVBO(vertices, sizeof(vertices));
//        bindEBO(indices, sizeof(indices));
        // Position attribute
        setVertexAttrs(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
        // Texture coordinates attribute
        setVertexAttrs(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    }

    /*
     *
     */
    void initBuffers() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
//        glGenBuffers(1, &EBO);
        glBindVertexArray(VAO);
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
        window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
        if (window == nullptr) {
            std::cout << "Failed to create GLFW createWindow" << std::endl;
            glfwTerminate();
            exit(1);
        }

        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwSetCursorPosCallback(window, Camera::mouseCallback);
        glfwSetScrollCallback(window, Camera::scrollCallback);

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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
    void bindVBO(GLfloat data[], int dataSize) const {
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
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
    void bindEBO(GLuint data[], int dataSize) const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
    }

    /*
     *
     */
    void close() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
//        glDeleteBuffers(1, &EBO);
        delete shader;
        delete texture;
        glfwTerminate();
    }
};


#endif //GRAPHICS_APP_H
