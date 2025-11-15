#ifndef __TGA_H__
#define __TGA_H__

#include <stdbool.h>

#include <GL/gl.h>

typedef struct {
    GLuint width;
    GLuint height;
    GLuint format; // GL_RGB, GL_RGBA
    GLubyte *data;
} texture_t;

bool load_tga(const char *path, texture_t *texture);

#endif // __TGA_H__