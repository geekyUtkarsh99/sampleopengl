//
// Created by DELL on 20-06-2021.
//

#ifndef SAMPLEOPENGL_MULTISHADER_H
#define SAMPLEOPENGL_MULTISHADER_H
#include "GLES2/gl2.h"
#include "GLES2/gl2ext.h"
#include "programGenerator.h"
#include "matrixOperation.h"

class multiShader {
private:

    GLuint program;

    //square
    int x,y;
    int w,h;
    unsigned char * image;
    GLuint texture;

    //variables for shader models
    GLuint vertexPosition;
    GLuint vertexColor;
    GLuint vertexTextureCord;
    GLuint squareSamplerLocation;

    //matrix models positions
    GLuint projectionView;
    GLuint modelView;

    //matrices
    float modelMatrix[16];
    float projectionSquareMatrix[16];


    //pyramid

    GLuint vertexPositionpyr;
    GLuint vertexColorpyr;
    programGenerator *generator;
    matrixOperation *operation;
    GLuint pyrProgram;
    float angle = 45.0f;




public :
    void setupGL(int w , int h);
    void render ();
    bool loadImage(unsigned char *image,int w,int h);
    void loadTexture();
    multiShader();


};


#endif //SAMPLEOPENGL_MULTISHADER_H
