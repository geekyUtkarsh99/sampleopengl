//
// Created by DELL on 21-02-2021.
//

#ifndef SAMPLEOPENGL_TRIANGLE_H
#define SAMPLEOPENGL_TRIANGLE_H
#include "GLES2/gl2.h"
#include "GLES2/gl2ext.h"
#include "JNI.h"
#include "stb_image.h"


class triangle {

public :
    float x = 0.0f,y = 0.0f;
    unsigned char *pixel;


    triangle(int x,int y);
    void setX(int x);
    static void createMatrixVolume(float * matrix); //create a matrix room

    void setTranslationsToMatrix(float * matrix,float x,float y,float z); //set a predefined position to a matrix object (indirect method)

    void multiplyMatrix(float * dest,float * op1,float * op2); //calculate and process changes made to a matrix body

    void matrixPerspective(float* matrix, float fieldOfView, float aspectRatio, float zNear, float zFar);

    void matrixFrustum(float* matrix, float left, float right, float bottom, float top, float zNear, float zFar);

    void matrixRotateX(float* matrix, float angle);
    void matrixRotateY(float * matrix ,float angle);

    void updateAngle ();

    void move();

    //adding textures
    GLuint addTexture();

    GLubyte* getPixels ();

    void setPixel(GLubyte * pixel);

    //render function
    void render();
    void setupVoid(int w,int h);
    GLuint loadShader(GLenum shaderType,const char * source);
    GLuint loadProgram(const char * vertexshader,const char * fragmentshader);




};


#endif //SAMPLEOPENGL_TRIANGLE_H
