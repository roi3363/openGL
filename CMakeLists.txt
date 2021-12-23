cmake_minimum_required(VERSION 3.9)
project(graphics)

set(CMAKE_CXX_STANDARD 17)

# Add header file
<<<<<<< HEAD
set(GLFW_H /usr/include/GLFW/)
#set(ASSIMP_H /usr/local/Cellar/assimp/5.1.2/include)
include_directories(include ${GLFW_H})# ${ASSIMP_H})

# Add target link
set(GLFW_LINK /usr/lib/x86_64-linux-gnu/libglfw.so)
#set(ASSIMP_LINK /usr/local/Cellar/assimp/5.1.2/lib/libassimp.5.1.0.dylib)
link_libraries(${GLFW_LINK} ${CMAKE_DL_LIBS}) # ${ASSIMP_LINK})
=======
if (APPLE)
    set(GLFW_H /usr/local/Cellar/glfw/3.3.5/include/GLFW)
elseif(UNIX)
    set(GLFW_H /usr/include/GLFW/)
endif()
include_directories(include ${GLFW_H})

# Add target link
if (APPLE)
    set(GLFW_LINK /usr/local/Cellar/glfw/3.3.5/lib/libglfw.3.dylib)
    link_libraries(${GLFW_LINK} )
elseif(UNIX)
    set(GLFW_LINK /usr/lib/x86_64-linux-gnu/libglfw.so)
    link_libraries(${GLFW_LINK} ${CMAKE_DL_LIBS} )
endif()
>>>>>>> 1baa6c4ef981474e294a2b27530486c1ec7b7dd1



# Execute compilation command
<<<<<<< HEAD
#set(CMAKE_CXX_FLAGS "-ldl")
=======
if (APPLE)
    set(CMAKE_CXX_FLAGS "-framework Cocoa -framework IOKit")
endif()

file(COPY assets/shaders DESTINATION .)
>>>>>>> 1baa6c4ef981474e294a2b27530486c1ec7b7dd1

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
