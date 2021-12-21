#ifndef GRAPHICS_APP_H
#define GRAPHICS_APP_H

// sys libraries
#include <iterator>
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
#include "camera/camera.h"
#include "geometry.h"

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
  Geometry *geometry;
  GLFWwindow *window{};

  mat4 model = mat4(1.0f);

public:
    App() {
        initialiseWindow();
	geometry = new Geometry();
    }

    void printVec(vec3 vec) { printf("%f %f %f\n", vec.x, vec.y, vec.z); }

    /*
     *
     */
    void run() {

        while (!glfwWindowShouldClose(window)) {
            float currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            Camera::processInput(window);

            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	    // make call to draw
	    geometry->draw(model);
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        close();
    }

    /*
     *
     */
    void setup() {
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
      
    }

private:
    /*
     *
     */
    void draw(vector<float> data, vec3 color) {
        // glDrawArrays(GL_LINES, 0, data.size() / 3);

    }


    /*
     *
     */
    static void setVertexAttrs(GLuint index, GLint size, GLenum type,
                               GLboolean normalized, GLsizei stride,
                               const void *pointer) {
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
    static void framebuffer_size_callback(GLFWwindow *window, int width,
                                          int height) {
        glViewport(0, 0, width, height);
    }

    /*
     *
     */
    void close() const {
      geometry->destroy();
      glfwTerminate();
    }
};

#endif //GRAPHICS_APP_H
