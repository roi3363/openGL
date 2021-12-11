cmake_minimum_required(VERSION 3.9)
project(graphics)

set(CMAKE_CXX_STANDARD 17)

# Add header file
set(GLFW_H /usr/local/Cellar/glfw/3.3.5/include/GLFW)
set(ASSIMP_H /usr/local/Cellar/assimp/5.1.2/include)
include_directories(include ${GLFW_H} ${ASSIMP_H})

# Add target link
set(GLFW_LINK /usr/local/Cellar/glfw/3.3.5/lib/libglfw.3.dylib)
set(ASSIMP_LINK /usr/local/Cellar/assimp/5.1.2/lib/libassimp.5.1.0.dylib)
link_libraries(${GLFW_LINK} ${ASSIMP_LINK})

# Execute compilation command
set(CMAKE_CXX_FLAGS "-framework Cocoa -framework IOKit")
add_executable(
        graphics
        include/stb_image.h
        include/glad.c
        include/stb.cpp
        app/shaders/shader.h
        app/textures/texture.h
        app/camera/camera.h
        app/app.h
        main.cpp
)
