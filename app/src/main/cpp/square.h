//
// Created by DELL on 31-03-2021.
//

#ifndef SAMPLEOPENGL_SQUARE_H
#define SAMPLEOPENGL_SQUARE_H

#include "GLES2/gl2.h"
#include "GLES2/gl2ext.h"
#include "programGenerator.h"
#include "matrixOperation.h"
#include "jni.h"

class square {
public:
    int x,y;
    int w,h;
    unsigned char * image;
    GLuint texture;
    GLuint squareProgram;

    float angle;

    void setupGraphics(int w,int h);
    void render();
    square(int x,int y , GLuint program);
    square(GLuint program);

    void move();
    void loadTexture();
    bool loadImage(unsigned char* image,int w,int h);

};


#endif //SAMPLEOPENGL_SQUARE_H
