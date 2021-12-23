#ifndef GRAPHICS_GEOMETRY_H
#define GRAPHICS_GEOMETRY_H

using std::filesystem::current_path;

class Geometry {
 public:
  GLuint VAO{};
  GLuint VBO{};
  GLuint EBO{};

  Shader *shader;

  Geometry(float vertices[], int verticesSize, unsigned int indices[], int indicesSize){
    shader = new Shader("assets/shaders/vertex.frag", "assets/shaders/fragment.frag");

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
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
