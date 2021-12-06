cmake_minimum_required(VERSION 3.9)
project(graphics)

set(CMAKE_CXX_STANDARD 14)

# Add header file
set(GLEW_H /usr/local/Cellar/glew/2.2.0_1/include/GL)
set(GLFW_H /usr/local/Cellar/glfw/3.3.4/include/GLFW)
set(GLAD_H glad.h)
set(KHAR_H KHAR.h)
include_directories(${GLEW_H} ${GLFW_H} ${GLAD_H} ${KHAR_H})

# Add target link
set(GLEW_LINK /usr/local/Cellar/glew/2.2.0_1/lib/libGLEW.2.2.dylib)
set(GLFW_LINK /usr/local/Cellar/glfw/3.3.4/lib/libglfw.3.dylib)
link_libraries(${GLEW_LINK} ${GLFW_LINK})

# Execute compilation command
set(CMAKE_CXX_FLAGS "-framework Cocoa -framework IOKit")
add_executable(graphics
        include/stb_image.h
        include/glad.c
        include/stb.cpp
        shaders/shader.h
        main.cpp
        textures/texture.h window/app.h)
