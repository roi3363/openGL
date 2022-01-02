#ifndef GRAPHICS_APP_H
#define GRAPHICS_APP_H

// sys libraries
#include <algorithm>
#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
// OpenGL
#include <glad.h>
#include <glfw3.h>
// glm
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <unistd.h>

// Namespaces
using glm::lookAt;
using glm::mat4;
using glm::radians;
using glm::vec3;
using std::string;
using std::vector;

// App files
#include "shader.h"
#include "camera.h"
#include "geometry.h"


float deltaTime = 0.0f;
float lastFrame = 0.0f;
const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;

class App {
  Geometry *axisGeometry;
  Geometry *functionGeometry;
  Geometry *derivativeGeometry;
  GLFWwindow *window{};
  mat4 model = mat4(1.0f);

public:
  App() { initialiseWindow(); }

  void setup() {
    vector<float> axisCenter = {0.0f, 0.0f};
    vector<float> domain = {-6.0, 6.0};
    vector<float> functionPoints = getFunctionPoints(sinf, domain, 0.1);
    vector<float> derivativePoints = getFunctionPoints(sinf, domain, 0.1);

    axisGeometry =
        new Geometry(axisCenter, "assets/shaders/axis.vert", "assets/shaders/axis.geom", "assets/shaders/axis.frag");
    functionGeometry =
        new Geometry(functionPoints,
                     "assets/shaders/func.vert",
                     "assets/shaders/func.geom",
                     "assets/shaders/func.frag");
    derivativeGeometry =
        new Geometry(derivativePoints,
                     "assets/shaders/derivative.vert",
                     "assets/shaders/derivative.geom",
                     "assets/shaders/derivative.frag");
  }

  /*
   *
   */
  void run() {
    while (!glfwWindowShouldClose(window)) {
      auto currentFrame = (float) glfwGetTime();
      deltaTime = currentFrame - lastFrame;
      lastFrame = currentFrame;

      Camera::processInput(window);
      axisGeometry->shader->reload();
      functionGeometry->shader->reload();
      derivativeGeometry->shader->reload();
      usleep(100000);
      glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      axisGeometry->draw(model, GL_POINTS, currentFrame * 0.5f);
      functionGeometry->draw(model, GL_LINE_STRIP, currentFrame * 0.5f);
      derivativeGeometry->draw(model, GL_LINES, currentFrame * 0.5f);

      glfwSwapBuffers(window);
      glfwPollEvents();
    }
    close();
  }

private:
  /*
   *
   */
  void initialiseWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if (strcmp(PLATFORM, "APPLE") == 0) {
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    }

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

  vector<float> getFunctionPoints(std::function<float(float)> func,
                                  vector<float> domain, float stepSize) {
    vector<float> functionHeights = {};
    vector<float> functionSteps = {};
    float step = domain[0];

    while (step < domain[1]) {
      functionSteps.push_back(step);
      functionHeights.push_back(func(step));

      step += stepSize;
    }

    float heightMax =
        *std::max_element(functionHeights.begin(), functionHeights.end());
    float domainMax = std::max(abs(domain[0]), abs(domain[1]));

    std::for_each(functionHeights.begin(), functionHeights.end(), [&heightMax](float &el){
      el *= 1.0f / heightMax; });
    std::for_each(functionSteps.begin(), functionSteps.end(), [&domainMax](float &el){
      el *= 1.0f / domainMax; });

    vector<float> functionPoints = {};

    for(int i = 0; i < functionSteps.size(); i++){
      functionPoints.push_back(functionSteps[i]);
      functionPoints.push_back(functionHeights[i]);
    }

    return functionPoints;
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
    axisGeometry->destroy();
    functionGeometry->destroy();
    glfwTerminate();
  }
};

#endif // GRAPHICS_APP_H
