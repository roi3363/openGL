#ifndef GRAPHICS_GEOMETRY_H
#define GRAPHICS_GEOMETRY_H

class Geometry {
public:
  GLuint VAO{};
  GLuint VBO{};
  GLuint EBO{};
  int verticesSize;
  vector<float> vertices;
  int numAttrsPerVertex;
  Shader *shader;

  Geometry(vector<float> vertices, const char *vsPath, const char *gsPath,
           const char *fsPath, int numAttrsPerVertex) {
    shader = new Shader(vsPath, fsPath, gsPath);
    this->verticesSize = vertices.size() * sizeof(float);
    this->vertices = vertices;
    this->numAttrsPerVertex = numAttrsPerVertex;
    
    genBuffers();
    bindVBO(verticesSize, vertices.data());
    

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

  void draw(mat4 model, GLenum primitive, float time) {
    shader->use();
    shader->setFloat("time", time);
    glBindVertexArray(VAO);
    glDrawArrays(primitive, 0, vertices.size() / this->numAttrsPerVertex);
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
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //    glDeleteBuffers(1, &EBO);
    delete shader;
  }
};

#endif // GRAPHICS_GEOMETRY_H
