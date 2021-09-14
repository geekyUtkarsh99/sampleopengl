//
// Created by DELL on 10-06-2021.
//




#include "vboExample.h"


//first object
GLuint static vboBuffer[2];
GLuint static vboBuffer1[2];


const static char vboVertexShader[]  =  "attribute vec4 vertexPosition;\n"
                                        "attribute vec3 vertexColour;\n"
                                        "varying vec3 fragColour;\n"
                                        "uniform mat4 projection;\n"
                                        "uniform mat4 modelView;\n"
                                        "void main()\n"
                                        "{\n"
                                        "    gl_Position = projection * modelView * vertexPosition;\n"
                                        "    fragColour = vertexColour;\n"
                                        "}\n";

const static char vboFragementShader[] =  "precision mediump float;\n"
                                          "varying vec3 fragColour;\n"
                                          "void main()\n"
                                          "{\n"
                                          "    gl_FragColor = vec4(fragColour, 1.0);\n"
                                          "}\n";


GLfloat vbocubeVertices []{


        -1.0f,  1.0f, -1.0f,        /* Back Face First Vertex Position */
        1.0f, 0.0f, 0.0f,           /* Back Face First Vertex Colour */
        1.0f,  1.0f, -1.0f,         /* Back Face Second Vertex Position */
        1.0f, 0.0f, 0.0f,           /* Back Face Second Vertex Colour */
        -1.0f, -1.0f, -1.0f,        /* Back Face Third Vertex Position */
        1.0f, 0.0f, 0.0f,           /* Back Face Third Vertex Colour */
        1.0f, -1.0f, -1.0f,         /* Back Face Fourth Vertex Position */
        1.0f, 0.0f, 0.0f,           /* Back Face Fourth Vertex Colour */
        -1.0f,  1.0f,  1.0f,        /* Front. */
        0.0f, 1.0f, 0.0f,
        1.0f,  1.0f,  1.0f,
        0.0f, 1.0f, 0.0f,
        -1.0f, -1.0f,  1.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, -1.0f,  1.0f,
        0.0f, 1.0f, 0.0f,
        -1.0f,  1.0f, -1.0f,        /* Left. */
        0.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,
        0.0f, 0.0f, 1.0f,
        -1.0f, -1.0f,  1.0f,
        0.0f, 0.0f, 1.0f,
        -1.0f,  1.0f,  1.0f,
        0.0f, 0.0f, 1.0f,
        1.0f,  1.0f, -1.0f,         /* Right. */
        1.0f, 1.0f, 0.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, -1.0f,  1.0f,
        1.0f, 1.0f, 0.0f,
        1.0f,  1.0f,  1.0f,
        1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, -1.0f,         /* Top. */
        0.0f, 1.0f, 1.0f,
        -1.0f, -1.0f,  1.0f,
        0.0f, 1.0f, 1.0f,
        1.0f, -1.0f,  1.0f,
        0.0f, 1.0f, 1.0f,
        1.0f, -1.0f, -1.0f,
        0.0f, 1.0f, 1.0f,
        -1.0f,  1.0f, -1.0f,         /* Bottom. */
        1.0f, 0.0f, 1.0f,
        -1.0f,  1.0f,  1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f, 0.0f, 1.0f,


};


GLfloat squareItemCord[] = {

        -1.0f,1.0f,0.0f, //pos
        1.0f,0.0f,0.0f,  //col
        1.0f,1.0f,0.0f,
        0.0f,1.0f,0.0f,
        1.0f,-1.0f,0.0f,
        0.0f,0.0f,1.0f,
        -1.0f,-1.0f,0.0f,
        1.0f,1.0f,0.0f


};

GLushort squareItemindices[] = {

        0,1,2,
        0,3,2

};

GLshort  vboindices[]{

        0, 2, 3, 0, 1, 3, 4, 6, 7, 4, 5, 7, 8, 9, 10,
        11, 8, 10, 12, 13, 14, 15, 12, 14, 16, 17, 18,
        16, 19, 18, 20, 21, 22, 20, 23, 22

};



void vboExample::setupGraphics(int w, int h) {

    auto * gens = new programGenerator;
    auto * mats = new matrixOperation;

    vboProgram = gens->createProgram(vboVertexShader,vboFragementShader);

    //shared
    vertexLocation = glGetAttribLocation(vboProgram,"vertexPosition");
    colorLocation = glGetAttribLocation(vboProgram,"vertexColour");

    projectionPoint = glGetUniformLocation(vboProgram,"projection");
    modelPoint = glGetUniformLocation(vboProgram,"modelView");

    mats->perspective(projectionMatrix,100,(float)w/(float)h,0.1f,100);
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, w, h);



}

void vboExample::vborender() {

    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    //load buffers to system
    glGenBuffers(2,vboBuffer);
    glBindBuffer(GL_ARRAY_BUFFER,vboBuffer[0]); // for vertices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vboBuffer[1]); //for indices

    //allocate data to buffers to display
    glBufferData(GL_ARRAY_BUFFER,vertexBufferSize,vbocubeVertices,GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,elementBufferSize,vboindices,GL_STATIC_DRAW);

    //1
    auto * mats = new matrixOperation;

    mats->createVolume(matrixModel);

    mats->rotateX(matrixModel,angle);

    mats->translation(2.0f,0.0f,-10.0f,matrixModel);

//    glUseProgram(vboProgram);

    glVertexAttribPointer(vertexLocation,3,GL_FLOAT,GL_FALSE,strideLength,0);
    glEnableVertexAttribArray(vertexLocation);

    glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, strideLength,
                          reinterpret_cast<const void *>(vertexColourOffset));
    glEnableVertexAttribArray(colorLocation);

    glUniformMatrix4fv(projectionPoint,1,GL_FALSE,projectionMatrix);
    glUniformMatrix4fv(modelPoint,1,GL_FALSE,matrixModel);

    glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_SHORT,0);


    //2

    //second object
    glGenBuffers(2,vboBuffer1);
    glBindBuffer(GL_ARRAY_BUFFER,vboBuffer1[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vboBuffer1[1]);

    //allocate
    glBufferData(GL_ARRAY_BUFFER,sizeof(squareItemCord),squareItemCord,GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(squareItemindices),squareItemindices,GL_STATIC_DRAW);

    mats->createVolume(matrixModel);

//    mats->rotateX(matrixModel,angle);

    mats->translation(-1.0f,0.0f,-10.0f,matrixModel);

//    glUseProgram(vboProgram);

    glVertexAttribPointer(vertexLocation,3,GL_FLOAT,GL_FALSE,strideLength1,0);
    glEnableVertexAttribArray(vertexLocation);

    glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, strideLength1,
                          reinterpret_cast<const void *>(vertexColourOffset1));
    glEnableVertexAttribArray(colorLocation);

    glUniformMatrix4fv(projectionPoint,1,GL_FALSE,projectionMatrix);
    glUniformMatrix4fv(modelPoint,1,GL_FALSE,matrixModel);

    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_SHORT,0);
    glUseProgram(vboProgram);

}

vboExample::vboExample() {

}


