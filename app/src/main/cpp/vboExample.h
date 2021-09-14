//
// Created by DELL on 10-06-2021.
//



#ifndef SAMPLEOPENGL_VBOEXAMPLE_H
#define SAMPLEOPENGL_VBOEXAMPLE_H

#include "GLES2/gl2.h"
#include "GLES2/gl2ext.h"
#include "programGenerator.h"
#include "matrixOperation.h"
#include "android/log.h"
#include "programGenerator.h"
#include "matrixOperation.h"
//#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS_


class vboExample {

private :
    //1
     GLushort vertexBufferSize = 48 * 3 * sizeof (GLfloat);
     GLushort elementBufferSize = 12 * 3  * sizeof(GLushort);
     GLushort vertexColourOffset = 3  * sizeof (GLfloat);
     GLushort strideLength = 6 * sizeof(GLfloat);

     //2
     GLushort vertexBufferSize1 = 48 * 3 * sizeof (GLfloat);
     GLushort elementBufferSize1 = 2 * 3  * sizeof(GLushort);
     GLushort vertexColourOffset1 = 3  * sizeof (GLfloat);
     GLushort strideLength1 = 6 * sizeof(GLfloat);

     //shared
     GLuint vertexLocation;
     GLuint colorLocation;
     GLuint projectionPoint,modelPoint;


     //programs
     GLuint vboProgram;
     float matrixModel[16];
     float projectionMatrix[16];
     float angle = 45.0f;



public :

    void setupGraphics(int w , int h);
    void vborender ();
    vboExample();


};


#endif //SAMPLEOPENGL_VBOEXAMPLE_H
