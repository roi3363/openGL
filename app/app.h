#ifndef GRAPHICS_APP_H
#define GRAPHICS_APP_H

// sys libraries
#include <algorithm>
#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <math.h>
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
  Geometry *curveGeometry;
  Geometry *derivativeGeometry;
  GLFWwindow *window{};
  mat4 model = mat4(1.0f);

public:
  App() { initialiseWindow(); }

  void setup() {
    vector<float> axisCenter = {0.0f, 0.0f};
    vector<float> domain = {- 4.0f * M_PI, 4.0f * M_PI};

    // getting scaled parametrized curve values
    vector<std::function<float(float)>> circle = {
      [](float time){ return cosf(2.0f * time) + sinf(0.5f * time);},
      [](float time){return sinf(2.0f * time) + 0.3 * sinf(0.5f * time);},
    };
    
    vector<float> steps = getSteps(domain, 0.1f);
    vector<float> curveValues = getParametrizedCurvePoints(circle, steps);

    // scale step afterwards
    float domainMax = std::max(abs(domain[0]), abs(domain[1]));
    std::for_each(steps.begin(), steps.end(), [&domainMax](float &el){
	  el *= 1.0f / (domainMax + 1.0f); });

    vector<float> curvePointsAndSteps = zipValuesWithSteps(steps, curveValues, 2);
    
    axisGeometry =
      new Geometry(axisCenter, "assets/shaders/axis.vert", "assets/shaders/axis.geom", "assets/shaders/axis.frag", 2);

    axisGeometry->setVertexAttrs(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
    
    curveGeometry =  new Geometry(curvePointsAndSteps,
				  "assets/shaders/curve.vert",
				  "assets/shaders/curve.geom",
				  "assets/shaders/curve.frag",
				  3);
    
    curveGeometry->setVertexAttrs(0, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    curveGeometry->setVertexAttrs(1, 1, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
				  (void*)(2* sizeof(float)));
    
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
      curveGeometry->shader->reload();
      //functionGeometry->shader->reload();
      //derivativeGeometry->shader->reload();
      usleep(100000);
      glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      axisGeometry->draw(model, GL_POINTS, currentFrame * 0.5f);
      curveGeometry->draw(model, GL_LINE_STRIP, currentFrame * 0.5f);
      //functionGeometry->draw(model, GL_LINE_STRIP, currentFrame * 0.5f);
      //derivativeGeometry->draw(model, GL_LINES, currentFrame * 0.5f);

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

  vector<float> zipValuesWithSteps (vector<float> steps,
				    vector<float> values,
				    int numValuesPerStep) {
    vector<float> zipped = {};
    int valueIndex = 0;

    for(int i = 0; i < steps.size(); i++){
      for(int j = 0; j < numValuesPerStep; j++) {
	zipped.push_back(values[valueIndex]);
	valueIndex += 1;
      }

      zipped.push_back(steps[i]);
    }

    return zipped;
  }

  vector<float> getSteps(vector<float> domain, float stepSize) {
    vector<float> steps = {};
    float stepValue = domain[0];

    while (stepValue < domain[1]) {
      steps.push_back(stepValue);

      stepValue += stepSize;
    }

    return steps;
  }

  /*
   * returns scaled function values on step
   */
  vector<float> getFunctionOnSteps(std::function<float(float)> func, vector<float> steps){
    vector<float> values = {};
    vector<float> absValues = {};
    
    for(int i = 0; i < steps.size(); i++){
      values.push_back(func(steps[i]));
      absValues.push_back(abs(func(steps[i])));
    }

    float absValuesMax =
      *std::max_element(absValues.begin(), absValues.end());

    std::for_each(values.begin(), values.end(), [&absValuesMax](float &el){
      el *= 1.0f / (absValuesMax + 2.0f); });


    return values;
  }

  vector<float> getParametrizedCurvePoints(vector<std::function<float(float)>> curve,
					   vector<float> steps) {
    vector<float> values[curve.size()];
    
    for(int j = 0; j < curve.size(); j++){
      values[j] = getFunctionOnSteps(curve[j], steps);
    }

    // this will need to be fixed for 3d I am lazy right now
    return zipValuesWithSteps(values[0], values[1], 1);
  }


  //
  //
  //    vector<float> functionPoints = {};
  //
  //    for(int i = 0; i < functionSteps.size(); i++){
  //      functionPoints.push_back(functionSteps[i]);
  //      functionPoints.push_back(functionHeights[i]);
  //    }
  //
  //    return functionPoints;

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
    curveGeometry->destroy();
    //functionGeometry->destroy();
    glfwTerminate();
  }
};

#endif // GRAPHICS_APP_H
