#include "include/glad.h"
#include <glfw3.h>
#include "shaders/shader.h"
#include "textures/texture.h"
#include "window/app.h"

int main() {
    App app;
    app.load();
    app.run();
    app.close();
    return 0;
}

