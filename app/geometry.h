#ifndef GRAPHICS_GEOMETRY_H
#define GRAPHICS_GEOMETRY_H

// sys libraries
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <experimental/filesystem>

// OpenGL
#include <glad.h>
#include <glfw3.h>
// glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/ext.hpp>

#include "shader.h"

using glm::mat4;

class Geometry {
 public:
  GLuint VAO{};
  GLuint VBO{};
  GLuint EBO{};

  Shader *shader;

  Geometry(float vertices[], int verticesSize,
	   unsigned int indices[], int indicesSize){

    shader = new Shader("./assets/shaders/vertex.frag", "./assets/shaders/fragment.frag");

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices,
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered
    // VBO as the vertex attribute's bound vertex buffer object so afterwards we
    // can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound
    // element buffer object IS stored in the VAO; keep the EBO bound.
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally
    // modify this VAO, but this rarely happens. Modifying other VAOs requires a
    // call to glBindVertexArray anyways so we generally don't unbind VAOs (nor
    // VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    glUseProgram(shader->ID);
  }

  
  void draw(mat4 model) {
    shader->use();
    glBindVertexArray(VAO);

    shader->setMat4("model", model);

    // fix 6
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  }

  /*
   *
   */
  void bindEBO(GLuint data[], int dataSize) const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
  }

  void destroy() const {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    delete shader;
  }
};

#endif //GRAPHICS_GEOMETRY_H
