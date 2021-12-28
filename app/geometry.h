#ifndef GRAPHICS_GEOMETRY_H
#define GRAPHICS_GEOMETRY_H

#include <string>
class Geometry {
public:
  GLuint VAO{};
  GLuint VBO{};
  GLuint EBO{};
  int verticesSize;
  vector<float> vertices;

  Shader *shader;

  Geometry(vector<float> vertices, const char *vsPath, const char *gsPath,
           const char *fsPath) {
    shader = new Shader(vsPath, fsPath, gsPath);
    this->verticesSize = vertices.size() * sizeof(float);
    this->vertices = vertices;
    genBuffers();
    bindVBO(verticesSize, vertices.data());
    //    bindEBO(indicesSize, indices);
    setVertexAttrs(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
    //    setVertexAttrs(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2
    //    * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glUseProgram(shader->ID);
  }

  void genBuffers() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    //    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
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


  void draw(mat4 model, GLenum primitive) {
    shader->use();
    glBindVertexArray(VAO);
    glDrawArrays(primitive, 0, vertices.size() / 2);
  }

  /*
   *
   */
  void bindEBO(int dataSize, GLuint data[]) const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
  }

  /*
   *
   */
  void bindVBO(int dataSize, GLfloat data[]) const {
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
  }

  void destroy() const {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    //    glDeleteBuffers(1, &EBO);
    delete shader;
  }
};

#endif // GRAPHICS_GEOMETRY_H
