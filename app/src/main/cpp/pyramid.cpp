//
// Created by DELL on 10-04-2021.
//

#include "pyramid.h"


static const char * pyrVertex = "attribute vec4 vertexPosition;\n"
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

static const char * pyrFragment = "precision mediump float;\n"
                                "varying vec3 fragColour;\n"
                                "void main()\n"
                                "{\n"
                                "gl_FragColor = vec4(fragColour,1.0);\n"
                                "}\n";

GLuint pyrVertexPosition,pyrColor,pyrModelView,pyrProjection,pyrVertexNormal;

float pyrProjectionMatrix[16],pyrModelMatrix[16];

GLfloat pyrCord[] = {
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

GLfloat pyrColorCord[] = {

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

GLushort pyrIndices[] = {
        0,1,2,
        3,4,5,
        6,7,8,
        9,10,11,
        12,13,14,
        12,14,15
};

GLfloat pyrNormals[]= {
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


void pyramid::setupGraphics(int w, int h) {
if (startRender) {
    pyrProgram = generator->createProgram(pyrVertex, pyrFragment);

    pyrVertexPosition = glGetAttribLocation(pyrProgram, "vertexPosition");
    pyrColor = glGetAttribLocation(pyrProgram, "vertexColour");
    pyrVertexNormal = glGetAttribLocation(pyrProgram, "vertexNormal");

    pyrProjection = glGetUniformLocation(pyrProgram, "projection");
    pyrModelView = glGetUniformLocation(pyrProgram, "modelView");

    operation->perspective(pyrProjectionMatrix, 45, (float) w / (float) h, 0.1f, 100);

    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, w, h);
}
}

void pyramid::render() {
    if (startRender) {

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        operation->createVolume(pyrModelMatrix);
//    operation->rotateX(pyrModelMatrix,angle);
        operation->rotateY(pyrModelMatrix, angle);
//    operation->rotateZ(pyrModelMatrix,angle);
        operation->translation(2.0f, 0.0f, -10.0f, pyrModelMatrix);

        glUseProgram(pyrProgram);

        glVertexAttribPointer(pyrVertexPosition, 3, GL_FLOAT, GL_FALSE, 0, pyrCord);
        glEnableVertexAttribArray(pyrVertexPosition);

        glVertexAttribPointer(pyrColor, 3, GL_FLOAT, GL_FALSE, 0, pyrColorCord);
        glEnableVertexAttribArray(pyrColor);

        glVertexAttribPointer(pyrVertexNormal, 3, GL_FLOAT, GL_FALSE, 0, pyrNormals);
        glEnableVertexAttribArray(pyrVertexNormal);

        glUniformMatrix4fv(pyrProjection, 1, GL_FALSE, pyrProjectionMatrix);
        glUniformMatrix4fv(pyrModelView, 1, GL_FALSE, pyrModelMatrix);

        glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_SHORT, pyrIndices);

        glDeleteProgram(pyrProgram);
    }
}

pyramid::pyramid() {

    generator = new programGenerator;
    operation = new matrixOperation;

}

void pyramid::rotate() {

    angle+=0.1f;
    if(angle >= 360){
        angle =0;
    }

}
