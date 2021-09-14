//
// Created by DELL on 10-04-2021.
//

#ifndef SAMPLEOPENGL_PYRAMID_H
#define SAMPLEOPENGL_PYRAMID_H

#include "GLES2/gl2.h"
#include "GLES2/gl2ext.h"
#include "programGenerator.h"
#include "matrixOperation.h"
#include "math.h"


class pyramid {

private :
    programGenerator *generator;
    matrixOperation *operation;
    GLuint pyrProgram;
    float angle = 45.0f;


public:
    bool startRender = false;
    void setupGraphics(int w,int h);
    void render();
    pyramid();
    void rotate();

};


#endif //SAMPLEOPENGL_PYRAMID_H
