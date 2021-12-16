#ifndef GRAPHICS_APP_H
#define GRAPHICS_APP_H

// sys libraries
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <experimental/filesystem>
#include "functional"
// OpenGL
#include <glad.h>
#include <glfw3.h>
// glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/ext.hpp>
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
    const int SCR_WIDTH = 1920;
    const int SCR_HEIGHT = 1080;
    Shader *shader;
    Texture *texture;
    GLFWwindow *window{};
    GLuint VAO{};
    GLuint VBO{};
    GLuint EBO{};

    mat4 model = mat4(1.0f);
    vec3 colorAxes = vec3(0.0f, 0.0f, 0.0f);
    vec3 colorFunc = vec3(0.8f, 0.2f, 0.4f);

    vec3 xStart = vec3(-1.0f, 0.0f, 0.0f);
    vec3 xEnd = vec3(1.0f, 0.0f, 0.0f);
    vec3 yStart = vec3(0.0f, 1.0f, 0.0f);
    vec3 yEnd = vec3(0.0f, -1.0f, 0.0f);

    vector<float> axesData;
  vector<float> planeCorners;
    vector<float> funcData;

public:
    App() {
        initialiseWindow();
        shader = new Shader("./app/shaders/vertex.frag", "./app/shaders/fragment.frag");
        texture = new Texture();
        planeCorners = {
	  -1.0, 1.0, 0.0,
	  -1.0, -1.0, 0.0,
	  1.0, 1.0, 0.0
        };
        //axesData.insert(axesData.end(), funcData.begin(), funcData.end());
    }

    void printVec(vec3 vec) {
        printf("%f %f %f\n", vec.x, vec.y, vec.z);
    }

    static float f(float x) {
        return sin(x);
    }

    void addToFuncData(vec3 vec) {
        funcData.emplace_back(vec.x);
        funcData.emplace_back(vec.y);
        funcData.emplace_back(vec.z);
    }

    void initFunc(std::function<float(float)> func, int n) {
        int a = 10;
        for (int x = 0; x <= n; x++) {
            float y = func(x);
            vec3 vec = vec3(x, y, 0.0f) / (float) n;
            printVec(vec);
            if (x == 0) {
                addToFuncData(vec);
            } else {
                addToFuncData(vec);
                addToFuncData(vec);
            }
        }
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

            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


            shader->use();
            glBindVertexArray(VAO);
            draw(planeCorners, colorAxes);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        close();
    }

    /*
     *
     */
    void setup() {
        // VAO
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        // VBO
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(planeCorners) * planeCorners.size(), planeCorners.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);
    }

private:
    /*
     *
     */
    void draw(vector<float> data, vec3 color) {
        shader->setVec3("color", color);
        shader->setMat4("model", model);
        //glDrawArrays(GL_LINES, 0, data.size() / 3);
	glDrawArrays(GL_TRIANGLES, 0, 3);
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

        //if (IS_APPLE) {
        //    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        //}

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
