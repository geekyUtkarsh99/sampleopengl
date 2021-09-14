//
// Created by DELL on 31-03-2021.
//

#include "programGenerator.h"

GLuint programGenerator::createShader(GLenum type, const char *source) {

    GLuint shader = glCreateShader(type);

    if(shader){
        glShaderSource(shader,1,&source, nullptr);
        glCompileShader(shader);
    }

    return shader;
}

GLuint programGenerator::createProgram(const char *vertex, const char *fragment) {

    GLuint program = glCreateProgram();

    GLuint vertexShader = createShader(GL_VERTEX_SHADER,vertex);
    GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER,fragment);

    if(program){
        glAttachShader(program,vertexShader);
        glAttachShader(program,fragmentShader);
        glLinkProgram(program);
    }

    return program;
}
