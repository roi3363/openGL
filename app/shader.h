#ifndef GRAPHICS_SHADER_H
#define GRAPHICS_SHADER_H

class Shader {
public:
  GLuint ID;

  Shader(const char *vertexPath,
         const char *fragmentPath,
         const char *geometryPath = nullptr) {

    const std::string &vShaderCode = getShaderCode(vertexPath);
    const std::string &fShaderCode = getShaderCode(fragmentPath);

    GLuint vertex = compileShader(GL_VERTEX_SHADER, vShaderCode.c_str());
    GLuint fragment = compileShader(GL_FRAGMENT_SHADER, fShaderCode.c_str());

    if (geometryPath) {
      const std::string &gShaderCode = getShaderCode(geometryPath);
      GLuint geometry = compileShader(GL_GEOMETRY_SHADER, gShaderCode.c_str());
      glAttachShader(ID, geometry);
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "program");
    glDeleteShader(vertex);
    //glDeleteShader(geometry);
    glDeleteShader(fragment);
  }

  /*
   *
   */
  void setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int) value);
  }

  /*
   *
   */
  void setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
  }

  /*
   *
   */
  void setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
  }

  /*
   *
   */
  void setMat4(const std::string &name, const glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
  }

  /*
   *
   */
  void setVec3(const std::string &name, const glm::vec3 &vec) const {
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &vec[0]);
  }

  /*
   *
   */
  void use() const {
    glUseProgram(ID);
  }

private:
  /*
   *
   */
  static GLuint compileShader(const GLenum type, const char *shaderCode) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderCode, nullptr);
    glCompileShader(shader);
    checkCompileErrors(shader, "shader");
    return shader;
  }

  /*
   *
   */
  static std::string getShaderCode(const char *path) {
    std::ifstream file;
    std::stringstream shaderStream;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
      file.open(path);
      shaderStream << file.rdbuf();
      file.close();
    }
    catch (std::ifstream::failure &e) {
      std::cout << "File '" << path << "' could not be read." << std::endl;
    }
    return shaderStream.str();
  }

  /*
   *
   */
  static void checkCompileErrors(unsigned int shader, const std::string &type) {
    int success;
    char infoLog[1024];
    if (type != "program") {
      glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
      if (!success) {
        glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
        std::cout << "Shader compilation error of type: " << type << "\n" << infoLog << std::endl;
      }
    } else {
      glGetProgramiv(shader, GL_LINK_STATUS, &success);
      if (!success) {
        glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
        std::cout << "Program linking error of type: " << type << "\n" << infoLog << std::endl;
      }
    }
  }
};

#endif //GRAPHICS_SHADER_H
