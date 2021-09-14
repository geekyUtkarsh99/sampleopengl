//
// Created by DELL on 10-04-2021.
//

#ifndef SAMPLEOPENGL_MAPPINGCLASS_H
#define SAMPLEOPENGL_MAPPINGCLASS_H

#include "GLES2/gl2.h"
#include "GLES2/gl2ext.h"
#include "programGenerator.h"
#include "matrixOperation.h"
#include "android/log.h"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

class mappingClass {

public:

    programGenerator *generator;
    matrixOperation *operation;

    mappingClass(float x,float y);

    void render();
    void setupGraphics(int w,int h);
    GLuint loadTexture();



};


#endif //SAMPLEOPENGL_MAPPINGCLASS_H
