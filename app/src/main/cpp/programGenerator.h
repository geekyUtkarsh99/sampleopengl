//
// Created by DELL on 31-03-2021.
//

#ifndef SAMPLEOPENGL_PROGRAMGENERATOR_H
#define SAMPLEOPENGL_PROGRAMGENERATOR_H

#include "GLES2/gl2.h"
#include "GLES2/gl2ext.h"

class programGenerator {
public:
    GLuint createShader(GLenum type ,const char * source);
    GLuint createProgram(const char * vertex,const char * fragment);


};


#endif //SAMPLEOPENGL_PROGRAMGENERATOR_H
