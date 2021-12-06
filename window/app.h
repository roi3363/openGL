#ifndef GRAPHICS_APP_H
#define GRAPHICS_APP_H

#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"

float vertices[] = {
        // positions          // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left
};
unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
};

class App {
    const int SCR_WIDTH = 800;
    const int SCR_HEIGHT = 600;
    Shader *shader;
    Texture *texture;
public:
    GLFWwindow *window{};
    GLuint VAO{};
    GLuint VBO{};
    GLuint EBO{};

    App() {
        initialiseWindow();
        shader = new Shader("../shaders/vertex.frag", "../shaders/fragment.frag");
        texture = new Texture();
    }

    void run() const {
        glUseProgram(shader->ID);
//        GLuint texture1 = Texture::loadTexture("../images/kathleen.jpeg", GL_RGB);
        GLuint texture1 = Texture::loadTexture("../images/container.jpg", GL_RGB);
        GLuint texture2 = Texture::loadTexture("../images/awesomeface.png", GL_RGBA);
        shader->setInt("texture1", 0);
        shader->setInt("texture2", 1);

        while (!glfwWindowShouldClose(window)) {
            processInput();

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            Texture::activateTexture(texture1, GL_TEXTURE0);
            Texture::activateTexture(texture2, GL_TEXTURE1);

            shader->use();

            // create transformations
//            float x = 0;
            float x = glm::sin((float(glfwGetTime())));
//            float y = 0.0f;
            float y = glm::sin((float(glfwGetTime())));
//            float z = 0.0f;
            float z = glm::sin((float(glfwGetTime())));
            glm::vec3 translationMat = glm::vec3(x, y, z);
            glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            transform = glm::translate(transform, translationMat);
            transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 0.0f));

            GLint transformLoc = glGetUniformLocation(shader->ID, "transform");
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

            // render container
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    void load() {
        initBuffers();

        bindVBO(vertices, sizeof(vertices));
        bindEBO(indices, sizeof(indices));

        // position attribute
        setVertexAttrs(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
        // texture coord attribute
        setVertexAttrs(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    }

    void initBuffers() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glBindVertexArray(VAO);
    }

    static void setVertexAttrs(GLuint index,
                               GLint size,
                               GLenum type,
                               GLboolean normalized,
                               GLsizei stride,
                               const void *pointer) {
        glVertexAttribPointer(index, size, type, normalized, stride, pointer);
        glEnableVertexAttribArray(index);
    }

    void bindVBO(GLfloat data[], int dataSize) const {
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
    }

    void bindEBO(GLuint data[], int dataSize) const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
    }

    void initialiseWindow() {
        // glfw: initialize and configure
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        // glfw window creation
        window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
        if (window == nullptr) {
            std::cout << "Failed to create GLFW createWindow" << std::endl;
            glfwTerminate();
            exit(1);
        }
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        // glad: load all OpenGL function pointers
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            std::cout << "Failed to initialize GLAD" << std::endl;
            exit(1);
        }

        glEnable(GL_DEPTH_TEST);
    }

    void processInput() const {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }

    static void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
        glViewport(0, 0, width, height);
    }

    void close() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        delete shader;
        delete texture;
        glfwTerminate();
    }
};


#endif //GRAPHICS_APP_H
