//
// Created by DELL on 21-02-2021.
//

#include <opencl-c-base.h>
#include <cmath>
#include "triangle.h"
#include "GLES2/gl2ext.h"
#include "GLES2/gl2.h"
#include "iostream"
#include "fstream"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "programGenerator.h"

#define CHANNEL_NUM 3


using namespace std;

static const char vertexShader[] =  "attribute vec4 vertexPosition;\n"
                                    "attribute vec3 vertexColour;\n"
                                    /* [Add a vertex normal attribute.] */
                                    "attribute vec3 vertexNormal;\n"
                                    /* [Add a vertex normal attribute.] */
                                    "varying vec3 fragColour;\n"
                                    "uniform mat4 projection;\n"
                                    "uniform mat4 modelView;\n"
                                    "void main()\n"
                                    "{\n"
                                    /* [Setup scene vectors.] */
                                    "    vec3 transformedVertexNormal = normalize((modelView * vec4(vertexNormal, 0.0)).xyz);"
                                    "    vec3 inverseLightDirection = normalize(vec3(0.0, 1.0, 1.0));\n"
                                    "    fragColour = vec3(0.0);\n"
                                    /* [Setup scene vectors.] */
                                    "\n"
                                    /* [Calculate the diffuse component.] */
                                    "    vec3 diffuseLightIntensity = vec3(1.0, 1.0, 1.0);\n"
                                    "    vec3 vertexDiffuseReflectionConstant = vertexColour;\n"
                                    "    float normalDotLight = max(0.0, dot(transformedVertexNormal, inverseLightDirection));\n"
                                    "    fragColour += normalDotLight * vertexDiffuseReflectionConstant * diffuseLightIntensity;\n"
                                    /* [Calculate the diffuse component.] */
                                    "\n"
                                    /* [Calculate the ambient component.] */
                                    "    vec3 ambientLightIntensity = vec3(0.1, 0.1, 0.1);\n"
                                    "    vec3 vertexAmbientReflectionConstant = vertexColour;\n"
                                    "    fragColour += vertexAmbientReflectionConstant * ambientLightIntensity;\n"
                                    /* [Calculate the ambient component.] */
                                    "\n"
                                    /* [Calculate the specular component.] */
                                    "    vec3 inverseEyeDirection = normalize(vec3(0.0, 0.0, 1.0));\n"
                                    "    vec3 specularLightIntensity = vec3(1.0, 1.0, 1.0);\n"
                                    "    vec3 vertexSpecularReflectionConstant = vec3(1.0, 1.0, 1.0);\n"
                                    "    float shininess = 2.0;\n"
                                    "    vec3 lightReflectionDirection = reflect(vec3(0) - inverseLightDirection, transformedVertexNormal);\n"
                                    "    float normalDotReflection = max(0.0, dot(inverseEyeDirection, lightReflectionDirection));\n"
                                    "    fragColour += pow(normalDotReflection, shininess) * vertexSpecularReflectionConstant * specularLightIntensity;\n"
                                    /* [Calculate the specular component.] */
                                    "\n"
                                    "    /* Make sure the fragment colour is between 0 and 1. */"
                                    "    clamp(fragColour, 0.0, 1.0);\n"
                                    "\n"
                                    "    gl_Position = projection * modelView * vertexPosition;\n"
                                    "}\n";


static const char fragmentShader[] =
        "precision mediump float;\n"
        "varying vec3 fragColour;\n"
        "void main()\n"
        "{\n"
        "    gl_FragColor = vec4(fragColour,1.0);\n"
        "}\n";

const GLfloat coordinates[] {

        -1.0f, -1.0f,
        1.0f, -1.0f
};

GLuint vertexNormalLocation;

//co-ordinates for cube
const GLfloat cubeCoordinates[]={
        1.0f,  1.0f, -1.0f, /* Back. */
        -1.0f,  1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        0.0f,  0.0f, -2.0f,
        -1.0f,  1.0f,  1.0f, /* Front. */
        1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f,  1.0f,
        0.0f,  0.0f,  2.0f,
        -1.0f,  1.0f, -1.0f, /* Left. */
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        -2.0f,  0.0f,  0.0f,
        1.0f,  1.0f,  1.0f, /* Right. */
        1.0f,  1.0f, -1.0f,
        1.0f, -1.0f,  1.0f,
        1.0f, -1.0f, -1.0f,
        2.0f,  0.0f,  0.0f,
        -1.0f, -1.0f,  1.0f, /* Bottom. */
        1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        0.0f, -2.0f,  0.0f,
        -1.0f,  1.0f, -1.0f, /* Top. */
        1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        0.0f,  2.0f,  0.0f
};

//color for the cube
GLfloat color[]={
        1.0f, 0.0f, 0.0f, /* Back. */
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, /* Front. */
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, /* Left. */
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, /* Right. */
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f, /* Bottom. */
        0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, /* Top. */
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f
};

const float textureCoords[] = {
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

GLushort indices[] = {0,  2,  4,  0,  4,  1,  1,  4,  3,  2,  3,  4,  /* Back. */
                      5,  7,  9,  5,  9,  6,  6,  9,  8,  7,  8,  9,  /* Front. */
                      10, 12, 14, 10, 14, 11, 11, 14, 13, 12, 13, 14, /* Left. */
                      15, 17, 19, 15, 19, 16, 16, 19, 18, 17, 18, 19, /* Right. */
                      20, 22, 24, 20, 24, 21, 21, 24, 23, 22, 23, 24, /* Bottom. */
                      25, 27, 29, 25, 29, 26, 26, 29, 28, 27, 28, 29  /* Top. */};


GLfloat normals[] = {
        1.0f,  1.0f, -1.0f, /* Back. */
        -1.0f,  1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        0.0f,  0.0f, -1.0f,
        -1.0f,  1.0f,  1.0f, /* Front. */
        1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f,  1.0f,
        0.0f,  0.0f,  1.0f,
        -1.0f,  1.0f, -1.0f, /* Left. */
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        -1.0f,  0.0f,  0.0f,
        1.0f,  1.0f,  1.0f, /* Right. */
        1.0f,  1.0f, -1.0f,
        1.0f, -1.0f,  1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f,  0.0f,  0.0f,
        -1.0f, -1.0f,  1.0f, /* Bottom. */
        1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        0.0f, -1.0f,  0.0f,
        -1.0f,  1.0f, -1.0f, /* Top. */
        1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        0.0f,  1.0f,  0.0f
};

GLuint program;
GLuint position;

GLint vertexLocation;

GLint vertexColourLocation;

GLint projectionLocation;

GLint modelViewLocation;

float angle = 60;

float  projectionMatrix[16];
float modelViewMatrix[16];

GLint textureCordLocation;

GLint samplerLocation;

GLuint textureId;

triangle::triangle(int x, int y) {
this->x = x;
this->y = y;
}

void triangle::setX(int x) {
    this->x = x;
}

void triangle::render() {

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    createMatrixVolume(modelViewMatrix);
    matrixRotateX(modelViewMatrix, angle);
    matrixRotateY(modelViewMatrix, angle);
    setTranslationsToMatrix(modelViewMatrix, x, y, -10.0f);

    glUseProgram(program);
    //for drawing vertices
    glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, cubeCoordinates);
    glEnableVertexAttribArray(vertexLocation);
    //for drawing color
    glVertexAttribPointer(vertexColourLocation, 3, GL_FLOAT, GL_FALSE, 0, color);
    glEnableVertexAttribArray(vertexColourLocation);
    //for drawing lighting normals
    glVertexAttribPointer(vertexNormalLocation, 3, GL_FLOAT, GL_FALSE, 0, normals);
    glEnableVertexAttribArray(vertexNormalLocation);
    //for loading textures
//    glVertexAttribPointer(textureCordLocation, 2, GL_FLOAT, GL_FALSE, 0, textureCoords);
//    glEnableVertexAttribArray(textureCordLocation);

    /* Set the sampler texture unit to 0. */
//    glUniform1i(samplerLocation, 0);

    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, projectionMatrix);
    glUniformMatrix4fv(modelViewLocation, 1, GL_FALSE, modelViewMatrix);
    glDrawElements(GL_TRIANGLES, 72, GL_UNSIGNED_SHORT, indices);



    if (angle > 360)
        angle -= 360;


}


void triangle::setupVoid(int w, int h) {

    auto gen= new programGenerator;

  program = gen->createProgram(vertexShader,fragmentShader);

    vertexLocation = glGetAttribLocation(program, "vertexPosition");
    vertexColourLocation = glGetAttribLocation(program, "vertexColour");
   // textureCordLocation = glGetAttribLocation(program, "vertexTextureCord");
    projectionLocation = glGetUniformLocation(program, "projection");
    modelViewLocation = glGetUniformLocation(program, "modelView");
   // samplerLocation = glGetUniformLocation(program, "texture");
    vertexNormalLocation = glGetAttribLocation(program, "vertexNormal");
    /* Setup the perspective */
    matrixPerspective(projectionMatrix, 45, (float)w / (float)h, 0.1f, 100);
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, w, h);

    /* Load the Texture. */
   // textureId = addTexture();



}

GLuint triangle::loadShader(GLenum shaderType,const char *source) {

    GLuint shader  = glCreateShader(shaderType);

    if(shader){
        glShaderSource(shader,1,&source, nullptr);
        glCompileShader(shader);

    }

    return shader;
}


GLuint triangle::loadProgram(const char *vertexshader, const char *fragmentshader) {

    GLuint program = glCreateProgram();
    GLuint vshader = loadShader(GL_VERTEX_SHADER,vertexshader);
    GLuint fshader = loadShader(GL_FRAGMENT_SHADER,fragmentshader);

    if(program) {
        glAttachShader(program, vshader);
        glAttachShader(program, fshader);
        glLinkProgram(program);
    }

    return program;
}

void triangle::createMatrixVolume( float *matrix) {


        matrix[0] = 1.0f;
        matrix[1] = 0.0f;
        matrix[2] = 0.0f;
        matrix[3] = 0.0f;
        matrix[4] = 0.0f;
        matrix[5] = 1.0f;
        matrix[6] = 0.0f;
        matrix[7] = 0.0f;
        matrix[8] = 0.0f;
        matrix[9] = 0.0f;
        matrix[10] = 1.0f;
        matrix[11] = 0.0f;
        matrix[12] = 0.0f;
        matrix[13] = 0.0f;
        matrix[14] = 0.0f;
        matrix[15] = 1.0f;


}



void triangle::setTranslationsToMatrix(float *matrix, float x, float y, float z) {

    float  tempMatrix[16];
    //load temporary matrix with a matrix room
    createMatrixVolume(tempMatrix);
    tempMatrix[12] = x;
    tempMatrix[13] = y;
    tempMatrix[14] = z;
    multiplyMatrix(matrix,tempMatrix,matrix);

}


void triangle::multiplyMatrix(float *dest, float *op1, float *op2) {
    float theResult[16];
    int row, column = 0;
    int i,j = 0;
    for(i = 0; i < 4; i++)
    {
        for(j = 0; j < 4; j++)
        {
            theResult[4 * i + j] = op1[j] * op2[4 * i] + op1[4 + j] * op2[4 * i + 1] +
                                   op1[8 + j] * op1[4 * i + 2] + op1[12 + j] * op2[4 * i + 3];
        }
    }
    for(int i = 0; i < 16; i++)
    {
        dest[i] = theResult[i];
    }
}

void triangle::matrixPerspective(float *matrix, float fieldOfView, float aspectRatio, float zNear,
                                 float zFar) {
    float ymax, xmax;
    ymax = zNear * tanf(fieldOfView * M_PI / 360.0);
    xmax = ymax * aspectRatio;
    matrixFrustum(matrix, -xmax, xmax, -ymax, ymax, zNear, zFar);

}

void triangle::matrixFrustum(float *matrix, float left, float right, float bottom, float top,
                             float zNear, float zFar) {
    float temp, xDistance, yDistance, zDistance;
    temp = 2.0f *zNear;
    xDistance = right - left;
    yDistance = top - bottom;
    zDistance = zFar - zNear;
    createMatrixVolume(matrix);
    matrix[0] = temp / xDistance;
    matrix[5] = temp / yDistance;
    matrix[8] = (right + left) / xDistance;
    matrix[9] = (top + bottom) / yDistance;
    matrix[10] = (-zFar - zNear) / zDistance;
    matrix[11] = -1.0f;
    matrix[14] = (-temp * zFar) / zDistance;
    matrix[15] = 0.0f;


}

void triangle::matrixRotateX(float *matrix, float angle) {
    float tempMatrix[16];
    createMatrixVolume(tempMatrix);
    tempMatrix[5] = cos(angle);
    tempMatrix[9] = -sin(angle);
    tempMatrix[6] = sin(angle);
    tempMatrix[10] = cos(angle);
    multiplyMatrix(matrix, tempMatrix, matrix);

}

void triangle::matrixRotateY(float *matrix, float angle) {

    float tempMatrix[16];
    createMatrixVolume(tempMatrix);
    tempMatrix[0] = cos(angle);
    tempMatrix[8] = sin(angle);
    tempMatrix[2] = -sin(angle);
    tempMatrix[10] = cos(angle);
    multiplyMatrix(matrix,tempMatrix,matrix);

}

void triangle::updateAngle() {
    angle+=0.01f;

}

void triangle::move() {
    x++;
    if (x > 5){
        x=0;
    }
}

GLuint triangle::addTexture() {

    /* Texture Object Handle. */
    GLuint textureId;
    /* 3 x 3 Image,  R G B A Channels RAW Format. */
    GLubyte pixels[9 * 4] =
            {
                    18,  140, 171, 255, /* Some Colour Bottom Left. */
                    143, 143, 143, 255, /* Some Colour Bottom Middle. */
                    255, 255, 255, 255, /* Some Colour Bottom Right. */
                    255, 255, 0,   255, /* Yellow Middle Left. */
                    0,   255, 255, 255, /* Some Colour Middle. */
                    255, 0,   255, 255, /* Some Colour Middle Right. */
                    255, 0,   0,   255, /* Red Top Left. */
                    0,   255, 0,   255, /* Green Top Middle. */
                    0,   0,   255, 255, /* Blue Top Right. */
            };
    int width, height, nrChannels;

    //pack texture tightly
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);

    //create a texture
    glGenTextures(1,&textureId);

    //activate texture
    glActiveTexture(GL_TEXTURE0);

    //bind texture
    glBindTexture(GL_TEXTURE_2D,textureId);

    /* Load the texture. */
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 3, 3, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

    /* Set the filtering mode. */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    return textureId;

}

GLubyte* triangle::getPixels() {
    return 0;
}

void triangle::setPixel(GLubyte *pixel) {

}






