cmake_minimum_required(VERSION 3.9)
project(graphics)

set(CMAKE_CXX_STANDARD 17)

# Add header file
if (APPLE)
    set(GLFW_H /usr/local/Cellar/glfw/3.3.5/include/GLFW)
elseif(LINUX)
    set(GLFW_H /usr/include/GLFW/)
endif()
include_directories(include ${GLFW_H} ${ASSIMP_H})

# Add target link
if (APPLE)
    set(GLFW_LINK /usr/local/Cellar/glfw/3.3.5/lib/libglfw.3.dylib)
elseif(LINUX)
    set(GLFW_LINK /usr/lib/x86_64-linux-gnu/libglfw.so)
endif()

link_libraries(${GLFW_LINK} ${ASSIMP_LINK})

# Execute compilation command
if (APPLE)
    set(CMAKE_CXX_FLAGS "-framework Cocoa -framework IOKit")
endif()

file(COPY assets/shaders DESTINATION .)

add_executable(
        graphics
        include/stb_image.h
        include/glad.c
        include/stb.cpp
        app/shader.h
        app/camera.h
        app/app.h
        main.cpp
)