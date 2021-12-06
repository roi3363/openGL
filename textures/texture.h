#ifndef GRAPHICS_TEXTURE_H
#define GRAPHICS_TEXTURE_H

#include "../include/stb_image.h"

class Texture {
public:

    static GLuint loadTexture(const char *path, GLint format) {
        GLuint texture;
        int width, height, nrChannels;
        unsigned char *image = stbi_load(path, &width, &height, &nrChannels, 0);

        if (!image) {
            printf("Image/s could not be loaded\n");
            exit(1);
        }

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_set_flip_vertically_on_load(true);
        stbi_image_free(image);
        return texture;
    }

    static void activateTexture(GLuint texture, GLenum target) {
        glActiveTexture(target);
        glBindTexture(GL_TEXTURE_2D, texture);
    }
};


#endif //GRAPHICS_TEXTURE_H
