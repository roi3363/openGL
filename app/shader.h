#ifndef GRAPHICS_SHADER_H
#define GRAPHICS_SHADER_H

class Shader {
public:
  GLuint ID;
  string vsPath;
  string fsPath;
  string gsPath;
  GLuint vs;
  GLuint gs;
  GLuint fs;
  const char *lastVsCode = "";
  const char *lastGsCode = "";
  const char *lastFsCode = "";

  Shader(const string vsPath,
         const string fsPath,
         const string gsPath = nullptr)
      : vsPath{vsPath}, fsPath{fsPath} {
    if (!gsPath.empty()) {
      this->gsPath = gsPath;
    }
    loadShaders();
  }

  void reload() {
    glDeleteProgram(ID);
    loadShaders();
  }

  void loadShaders() {
    compileShader(GL_VERTEX_SHADER, vsPath);
    if (!gsPath.empty()) {
      compileShader(GL_GEOMETRY_SHADER, gsPath);
    }
    compileShader(GL_FRAGMENT_SHADER, fsPath);

    ID = glCreateProgram();
    glAttachShader(ID, vs);
    if (!gsPath.empty()) {
      glAttachShader(ID, gs);
    }
    glAttachShader(ID, fs);
    glLinkProgram(ID);
    checkCompilationErrors(ID, "program");
    glDeleteShader(vs);
    if (gs) {
      glDeleteShader(gs);
    }
    glDeleteShader(fs);
  }

  /*
   *
   */
  void setBool(const string &name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int) value);
  }

  /*
   *
   */
  void setInt(const string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
  }

  /*
   *
   */
  void setFloat(const string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
  }

  /*
   *
   */
  void setMat4(const string &name, const glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
  }

  /*
   *
   */
  void setVec3(const string &name, const glm::vec3 &vec) const {
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
  void compileShader(const GLenum type, string shaderPath) {
    const char *shaderCode = getShaderCode(shaderPath);
    if (type == GL_VERTEX_SHADER) {
      vs = createShader(type, "Vertex Shader", shaderCode);
    } else if (type == GL_GEOMETRY_SHADER) {
      gs = createShader(type, "Geometry Shader", shaderCode);
    } else if (type == GL_FRAGMENT_SHADER) {
      fs = createShader(type, "Fragment Shader", shaderCode);
    }
  }

  GLuint createShader(const GLenum type, const char *typeStr, const char *shaderCode) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderCode, nullptr);
    glCompileShader(shader);
    checkCompilationErrors(shader, typeStr);
    return shader;
  }

  /*
   *
   */
  static const char *getShaderCode(const string path) {
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
    return strdup(shaderStream.str().c_str());
  }

  /*
   *
   */
  static void checkCompilationErrors(unsigned int shader, const string &type) {
    int success;
    char infoLog[1024];
    if (type != "program") {
      glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
      if (!success) {
        glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
        std::cout << "Compilation error of " << type << "\n" << infoLog << std::endl;
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
