cmake_minimum_required(VERSION 3.9)
project(graphics)

set(CMAKE_CXX_STANDARD 14)

# Add header file
set(GLFW_H /usr/local/Cellar/glfw/3.3.5/include/GLFW)
include_directories(include ${GLEW_H} ${GLFW_H} ${GLAD_H} ${KHAR_H})

# Add target link
set(GLFW_LINK /usr/local/Cellar/glfw/3.3.5/lib/libglfw.3.dylib)
link_libraries(${GLEW_LINK} ${GLFW_LINK})

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
