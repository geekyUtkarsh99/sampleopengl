//
// Created by DELL on 10-04-2021.
//

#include <cstdio>
#include <cstdlib>
#include "mappingClass.h"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)


const char mappedVertex[] = "attribute vec4 vertexPosition;\n"
                            "attribute vec3 vertexColour;\n"
                            "attribute vec2 vertexTextureCord;\n"
                            "varying vec3 fragColour;\n"
                            "varying vec2 textureCord;\n"
                            "uniform mat4 projection;\n"
                            "uniform mat4 modelView;\n"
                            "void main()\n"
                            "{\n"
                            "gl_Position = projection*modelView*vertexPosition;\n"
                            "fragColour = vertexColour;\n"
                            "textureCord = vertexTextureCord;\n"
                            "}\n";

const char mappedFragment[] = "precision mediump float;\n"
                              "varying vec3 fragColour;\n"
                              "uniform sampler2D texture;\n"
                              "varying vec2 textureCord;\n"
                              "void main()\n"
                              "{\n"
                              "gl_FragColor = texture2D(texture,textureCord);\n"
                              "}\n";

GLfloat mappingCord[] = {

        -1.0f,  1.0f, -1.0f, /* Back. */
        1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f, /* Front. */
        1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f, /* Left. */
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        1.0f,  1.0f, -1.0f, /* Right. */
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f, /* Top. */
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f,  1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f, /* Bottom. */
        -1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f, -1.0f

};

GLfloat mappingColor[] = {
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f
};

GLfloat mapTexture[] = {
        1.0f, 1.0f, /* Back. */
        0.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f, /* Front. */
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f, /* Left. */
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 1.0f, /* Right. */
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        0.0f, 1.0f, /* Top. */
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 0.0f, /* Bottom. */
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f
};

GLushort mapIndices[] = {
        0, 2, 3, 0, 1, 3, 4, 6, 7, 4, 5, 7, 8, 9, 10, 11, 8, 10, 12, 13, 14, 15, 12, 14, 16, 17, 18, 16, 19, 18, 20, 21, 22, 20, 23, 22
};

//shader resources
GLuint mapVertexPosition,mapColorPosition,mapModelView,mapProjectionView,mapTextureCordLocation,mapSamplerLocation;

//program to run on
GLuint mapProgram;

//matrices
float MapProjectionMatrix[16];
float MapModelMatrix[16];

size_t TEXTURE_WIDTH;

size_t TEXTURE_HEIGHT;

size_t CHANNELS_PER_PIXEL;

GLubyte *theTexture;

void mappingClass::render() {

    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    operation->createVolume(MapModelMatrix);
    operation->translation(0.0f,0.0f,-10.0f,MapModelMatrix);

    glUseProgram(mapProgram);
    glVertexAttribPointer(mapVertexPosition,3,GL_FLOAT,GL_FALSE,0,mappingCord);
    glEnableVertexAttribArray(mapVertexPosition);
    glVertexAttribPointer(mapColorPosition,3,GL_FLOAT,GL_FALSE,0,mappingColor);
    glEnableVertexAttribArray(mapColorPosition);

    glUniformMatrix4fv(mapProjectionView,1,GL_FALSE,MapProjectionMatrix);
    glUniformMatrix4fv(mapModelView,1,GL_FALSE,MapModelMatrix);

    glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_SHORT,mapIndices);


}

void mappingClass::setupGraphics(int w, int h) {

    mapProgram = generator->createProgram(mappedVertex,mappedFragment);

    mapVertexPosition = glGetAttribLocation(mapProgram,"vertexPosition");
    mapColorPosition = glGetAttribLocation(mapProgram,"vertexColour");
    mapProjectionView = glGetUniformLocation(mapProgram,"projection");
    mapModelView = glGetUniformLocation(mapProgram,"modelView");
    mapTextureCordLocation = glGetAttribLocation(mapProgram,"vertexTextureCord");
    mapSamplerLocation = glGetUniformLocation(mapProgram,"texture");


    operation->perspective(MapProjectionMatrix,45,(float )w/(float)h,0.1f,100);
    glEnable(GL_DEPTH_TEST);
    glViewport(0,0,w,h);

    loadTexture();

}

mappingClass::mappingClass(float x, float y) {

    generator = new programGenerator;
    operation = new matrixOperation;

}

GLuint mappingClass::loadTexture() {


    static GLuint textureId;
    theTexture = (GLubyte *)malloc(sizeof(GLubyte) * TEXTURE_WIDTH * TEXTURE_HEIGHT * CHANNELS_PER_PIXEL);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    /* Generate a texture object. */
    glGenTextures(1, &textureId);
    /* Activate a texture. */
    glActiveTexture(GL_TEXTURE0);
    /* Bind the texture object. */
    glBindTexture(GL_TEXTURE_2D, textureId);
    FILE * theFile = fopen("/src/main/res/drawable/img3.jpg", "r");
    if(theFile == NULL)
    {
//        LOGE("Failure to load the texture");
        return 0;
    }
    fread(theTexture, TEXTURE_WIDTH * TEXTURE_HEIGHT * CHANNELS_PER_PIXEL, 1, theFile);
    /* Load the texture. */
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXTURE_WIDTH, TEXTURE_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, theTexture);
    /* Set the filtering mode. */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    free(theTexture);
    return textureId;

}
