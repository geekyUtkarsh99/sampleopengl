//
// Created by DELL on 31-03-2021.
//

#include "square.h"

//shaders for the model
const char *vertexShadersquare ="attribute vec4 vertexPosition;\n"
                           "attribute vec2 vertexTextureCord;\n"
                           "varying vec2 textureCord;\n"
                           "uniform mat4 projection;\n"
                           "uniform mat4 modelView;\n"
                           "void main()\n"
                           "{\n"
                           "gl_Position = projection*modelView*vertexPosition;\n"
                           "textureCord = vertexTextureCord;\n"
                           "}\n";

const char * fragmentShadersquare = "precision mediump float;\n"
                                    "uniform sampler2D texture;\n"
                                    "varying vec2 textureCord;\n"
                              "void main()\n"
                              "{\n"
                              "gl_FragColor = texture2D(texture,textureCord);\n"
                              "}\n";

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

//vertices
GLfloat verticesSquare[] = {
        -1.0f,1.0f,0.0f,
        1.0f,1.0f,0.0f,
        1.0f,-1.0f,0.0f,
        -1.0f,-1.0f,0.0f
};

//GLfloat verticesSquare1[] = {
//        -1.0f,1.0f,0.0f,
//        1.0f,1.0f,0.0f,
//        1.0f,-1.0f,0.0f,
//        -1.0f,-1.0f,0.0f
//};


GLfloat colorSquare[]= {
        1.0f,0.0f,0.0f,
        0.0f,0.0f,1.0f,
        0.0f,1.0f,0.0f,
        1.0f,1.0f,0.0f
};



GLushort squareindices[] = {
       0,1,2,
       0,3,2
};



//swapped co-ordinates
GLfloat squaretextureCord[] = {
        -1.0f,-1.0f,
        1.0f,-1.0f,
        1.0f,1.0f,
        -1.0f,1.0f
};

square::square(int x, int y , GLuint programp) {

this->x = x;
this->y = y;
this->squareProgram = programp;

}

/**
 *
 * @param w - width of screen
 * @param h - height of screen
 */
void square::setupGraphics(int w, int h) {

      auto * generator = new programGenerator;
      auto * matrixSelf = new matrixOperation;

      squareProgram = generator->createProgram(vertexShadersquare,fragmentShadersquare);

      vertexPosition = glGetAttribLocation(squareProgram,"vertexPosition");
//      vertexColor = glGetAttribLocation(squareProgram,"vertexColour");
      vertexTextureCord = glGetAttribLocation(squareProgram,"vertexTextureCord");
      squareSamplerLocation = glGetUniformLocation(squareProgram,"texture");


      modelView = glGetUniformLocation(squareProgram,"modelView");
      projectionView = glGetUniformLocation(squareProgram,"projection");

      //set perspective
      matrixSelf->perspective(projectionSquareMatrix,45,(float )w/(float )h,0.1f,100);
      glEnable(GL_DEPTH_TEST);
      glViewport(0,0,w,h);

      loadTexture();

    delete matrixSelf;
    delete generator;

}

void square::render() {

    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


    auto * matrixSelf = new matrixOperation;
    matrixSelf->createVolume(modelMatrix);
    matrixSelf->translation((float)x,0.0f,-5.0f,modelMatrix);


    glUseProgram(squareProgram);

    glVertexAttribPointer(vertexPosition,3,GL_FLOAT,GL_FALSE,0,verticesSquare);
    glEnableVertexAttribArray(vertexPosition);

//    glVertexAttribPointer(vertexColor,3,GL_FLOAT,GL_FALSE,0,colorSquare);
//    glEnableVertexAttribArray(vertexColor);

    glVertexAttribPointer(vertexTextureCord,2,GL_FLOAT,GL_FALSE,0,squaretextureCord);
    glEnableVertexAttribArray(vertexTextureCord);
    glUniformMatrix4fv(projectionView,1,GL_FALSE,projectionSquareMatrix);
    glUniformMatrix4fv(modelView,1,GL_FALSE,modelMatrix);

    glUniform1i(squareSamplerLocation,0);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_SHORT,squareindices);
//    glDrawArrays(GL_TRIANGLES,0,4);

    glDeleteProgram(squareProgram);
}

void square::move() {

  x++;
  if ( x > 10){
      x = 0;
  }

}

void square::loadTexture() {

glPixelStorei(GL_UNPACK_ALIGNMENT,1);

glGenTextures(1,&texture);

glActiveTexture(GL_TEXTURE0);

glBindTexture(GL_TEXTURE_2D,texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    /* Set the filtering mode. */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}

bool square::loadImage(unsigned char *image,int w,int h) {

    this->w = w;
    this->h = h;

    if (image != nullptr) {
        this->image = image;
        return true;
    }else return false;

}

square::square(GLuint program) {
    this->squareProgram = program;
}




