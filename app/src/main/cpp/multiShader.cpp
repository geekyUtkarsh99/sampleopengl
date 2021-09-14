//
// Created by DELL on 20-06-2021.
//

#include "multiShader.h"

//shaders for the model
const char vertexShadersquare1[] ="attribute vec4 vertexPosition;\n"
                                 "attribute vec2 vertexTextureCord;\n"
                                 "varying vec2 textureCord;\n"
                                 "uniform mat4 projection;\n"
                                 "uniform mat4 modelView;\n"
                                 "void main()\n"
                                 "{\n"
                                 "gl_Position = projection*modelView*vertexPosition;\n"
                                 "textureCord = vertexTextureCord;\n"
                                 "}\n";

const char fragmentShadersquare1[] = "precision mediump float;\n"
                                    "uniform sampler2D texture;\n"
                                    "varying vec2 textureCord;\n"
                                    "void main()\n"
                                    "{\n"
                                    "gl_FragColor = texture2D(texture,textureCord);\n"
                                    "}\n";


static const char pyrVertex1[] = "attribute vec4 vertexPosition;\n"
                                "attribute vec3 vertexColour;\n"
                                "varying vec3 fragColour;\n"
                                "uniform mat4 projection;\n"
                                "uniform mat4 modelView;\n"
                                "attribute vec3 vertexNormal;\n "
                                "void main()\n"
                                "{\n"
                                "    vec3 transformedVertexNormal = normalize((modelView * vec4(vertexNormal, 0.0)).xyz);"
                                "    vec3 inverseLightDirection = normalize(vec3(0.0, 1.0, 1.0));\n"
                                "    fragColour = vec3(0.0);\n"
                                "    vec3 diffuseLightIntensity = vec3(1.0, 1.0, 1.0);\n"
                                "    vec3 vertexDiffuseReflectionConstant = vertexColour;\n"
                                "    float normalDotLight = max(0.0, dot(transformedVertexNormal, inverseLightDirection));\n"
                                "    fragColour += normalDotLight * vertexDiffuseReflectionConstant * diffuseLightIntensity;\n"
                                "    clamp(fragColour, 0.0, 1.0);\n"
                                "\n"
                                "    gl_Position = projection * modelView * vertexPosition;\n"
                                "}\n";

static const char pyrFragment1[] = "precision mediump float;\n"
                                  "varying vec3 fragColour;\n"
                                  "void main()\n"
                                  "{\n"
                                  "gl_FragColor = vec4(fragColour,1.0);\n"
                                  "}\n";

GLuint pyrVertexPosition1,pyrColor1,pyrModelView1,pyrProjection1,pyrVertexNormal1;

float pyrProjectionMatrix1[16],pyrModelMatrix1[16];

GLfloat pyrCord1[] = {
        0.0f,2.0f,0.0f, //back
        1.0f,-1.0f,-1.0f,
        -1.00f,-1.0f,-1.0f,
        0.0f,2.0f,0.0f, //right
        1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,1.0f,
        0.0f,2.0f,0.0f, //front
        1.0f,-1.0f,1.0f,
        -1.0f,-1.0f,1.0f,
        0.0f,2.0f,0.0f, //left
        -1.0f,-1.0f,1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f, // bottom
        1.0f,-1.0f,1.0f,
        -1.0f,-1.0f,1.0f,
        -1.0f,-1.0f,-1.0f
};

GLfloat pyrColorCord1[] = {

        1.0f,0.0f,0.0f, //1
        1.0f,0.0f,0.0f,
        1.0f,0.0f,0.0f,
        0.0f,1.0f,0.0f, //2
        0.0f,1.0f,0.0f,
        0.0f,1.0f,0.0f,
        0.0f,0.0f,1.0f, //3
        0.0f,0.0f,1.0f,
        0.0f,0.0f,1.0f,
        0.0f,1.0f,1.0f, //4
        0.0f,1.0f,1.0f,
        0.0f,1.0f,1.0f,
        1.0f,1.0f,0.0f, //5
        1.0f,1.0f,0.0f,
        1.0f,1.0f,0.0f,
        1.0f,1.0f,0.0f,
};

GLushort pyrIndices1[] = {
        0,1,2,
        3,4,5,
        6,7,8,
        9,10,11,
        12,13,14,
        12,14,15
};

GLfloat pyrNormals1[]= {
        0.0f,2.0f,0.0f, //back
        1.0f,-1.0f,-1.0f,
        -1.00f,-1.0f,-1.0f,
        0.0f,2.0f,0.0f, //right
        1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,1.0f,
        0.0f,2.0f,0.0f, //front
        1.0f,-1.0f,1.0f,
        -1.0f,-1.0f,1.0f,
        0.0f,2.0f,0.0f, //left
        -1.0f,-1.0f,1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f, // bottom
        1.0f,-1.0f,1.0f,
        -1.0f,-1.0f,1.0f,
        -1.0f,-1.0f,-1.0f
};


//vertices
GLfloat verticesSquare1[] = {
        -1.0f,1.0f,0.0f,
        1.0f,1.0f,0.0f,
        1.0f,-1.0f,0.0f,
        -1.0f,-1.0f,0.0f
};

GLushort squareindices1[] = {
        0,1,2,
        0,3,2
};

GLfloat squaretextureCord1[] = {
        -1.0f,-1.0f,
        1.0f,-1.0f,
        1.0f,1.0f,
        -1.0f,1.0f
};



void multiShader::setupGL(int w, int h) {

    glEnable(GL_DEPTH_TEST);
    glViewport(0,0,w,h);
    loadTexture();
}

void multiShader::render() {

    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    //set 1
    program = generator->createProgram(pyrVertex1,pyrFragment1);

    pyrVertexPosition1 = glGetAttribLocation(program,"vertexPosition");
    pyrColor1 = glGetAttribLocation(program,"vertexColour");
    pyrVertexNormal1 = glGetAttribLocation(program,"vertexNormal");

    pyrProjection1 = glGetUniformLocation(program,"projection");
    pyrModelView1 = glGetUniformLocation(program,"modelView");

    operation->perspective(pyrProjectionMatrix1,100,(float )w/(float)h,0.1f,100);
    //end


    //pyramid
    operation->createVolume(pyrModelMatrix1);
//    operation->rotateX(pyrModelMatrix,angle);
    operation->rotateY(pyrModelMatrix1,angle);
//    operation->rotateZ(pyrModelMatrix,angle);
    operation->translation(3.0f,0.0f,-10.0f,pyrModelMatrix1);

    glUseProgram(program);

    glVertexAttribPointer(pyrVertexPosition1,3,GL_FLOAT,GL_FALSE,0,pyrCord1);
    glEnableVertexAttribArray(pyrVertexPosition1);

    glVertexAttribPointer(pyrColor1,3,GL_FLOAT,GL_FALSE,0,pyrColorCord1);
    glEnableVertexAttribArray(pyrColor1);

    glVertexAttribPointer(pyrVertexNormal1,3,GL_FLOAT,GL_FALSE,0,pyrNormals1);
    glEnableVertexAttribArray(pyrVertexNormal1);

    glUniformMatrix4fv(pyrProjection1,1,GL_FALSE,pyrProjectionMatrix1);
    glUniformMatrix4fv(pyrModelView1,1,GL_FALSE,pyrModelMatrix1);

    glDrawElements(GL_TRIANGLES,18,GL_UNSIGNED_SHORT,pyrIndices1);

//    glDeleteProgram(program);

 //set 2
    auto * generator = new programGenerator;
    auto * matrixSelf = new matrixOperation;

    program = generator->createProgram(vertexShadersquare1,fragmentShadersquare1);

    vertexPosition = glGetAttribLocation(program,"vertexPosition");
//      vertexColor = glGetAttribLocation(squareProgram,"vertexColour");
    vertexTextureCord = glGetAttribLocation(program,"vertexTextureCord");
    squareSamplerLocation = glGetUniformLocation(program,"texture");


    modelView = glGetUniformLocation(program,"modelView");
    projectionView = glGetUniformLocation(program,"projection");

    //set perspective
    matrixSelf->perspective(projectionSquareMatrix,100,(float )w/(float )h,0.1f,100);
//end

    //square
    auto * matrixSelf1 = new matrixOperation;
    matrixSelf1->createVolume(modelMatrix);
    matrixSelf1->translation((float)x-2,0.0f,-5.0f,modelMatrix);

    glUseProgram(program);

    glVertexAttribPointer(vertexPosition,3,GL_FLOAT,GL_FALSE,0,verticesSquare1);
    glEnableVertexAttribArray(vertexPosition);

//    glVertexAttribPointer(vertexColor,3,GL_FLOAT,GL_FALSE,0,colorSquare);
//    glEnableVertexAttribArray(vertexColor);

    glVertexAttribPointer(vertexTextureCord,2,GL_FLOAT,GL_FALSE,0,squaretextureCord1);
    glEnableVertexAttribArray(vertexTextureCord);
    glUniformMatrix4fv(projectionView,1,GL_FALSE,projectionSquareMatrix);
    glUniformMatrix4fv(modelView,1,GL_FALSE,modelMatrix);

    glUniform1i(squareSamplerLocation,0);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_SHORT,squareindices1);

//    glDeleteProgram(program);


}

bool multiShader::loadImage(unsigned char *image, int w, int h) {

    this->w = w;
    this->h = h;

    if (image != nullptr) {
        this->image = image;
        return true;
    }else return false;

}

void multiShader::loadTexture() {

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

multiShader::multiShader() {

    generator = new programGenerator;
    operation = new matrixOperation;

}
