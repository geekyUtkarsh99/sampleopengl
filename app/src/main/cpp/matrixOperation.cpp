//
// Created by DELL on 01-04-2021.
//

#include <cmath>
#include "matrixOperation.h"

void matrixOperation::createVolume(float *matrix) {

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

void matrixOperation::matrixMultiplication(float *dest, float *op1, float *op2) {

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

void matrixOperation::translation(float x, float y, float z, float *matrix) {
    float  tempMatrix[16];
    //load temporary matrix with a matrix room
    createVolume(tempMatrix);
    tempMatrix[12] = x;
    tempMatrix[13] = y;
    tempMatrix[14] = z;
    matrixMultiplication(matrix,tempMatrix,matrix);
}

void matrixOperation::perspective(float *matrix, float fov, float aspectRatio, float zNear, float zFar) {
    float ymax, xmax;
    ymax = zNear * tanf(fov * M_PI / 360.0);
    xmax = ymax * aspectRatio;
    frustum(matrix, -xmax, xmax, -ymax, ymax, zNear, zFar);
}

void matrixOperation::frustum(float *matrix, float left, float right, float bottom, float top,
                              float zNear, float zFar) {
    float temp, xDistance, yDistance, zDistance;
    temp = 2.0f *zNear;
    xDistance = right - left;
    yDistance = top - bottom;
    zDistance = zFar - zNear;
    createVolume(matrix);
    matrix[0] = temp / xDistance;
    matrix[5] = temp / yDistance;
    matrix[8] = (right + left) / xDistance;
    matrix[9] = (top + bottom) / yDistance;
    matrix[10] = (-zFar - zNear) / zDistance;
    matrix[11] = -1.0f;
    matrix[14] = (-temp * zFar) / zDistance;
    matrix[15] = 0.0f;
}

void matrixOperation::rotateX(float *matrix, float angle) {
    float tempMatrix[16];
    createVolume(tempMatrix);
    tempMatrix[0] = cos(angle);
    tempMatrix[8] = sin(angle);
    tempMatrix[2] = -sin(angle);
    tempMatrix[10] = cos(angle);
    matrixMultiplication(matrix,tempMatrix,matrix);

}

void matrixOperation::rotateY(float *matrix, float angle) {

    float tempMatrix[16];
    createVolume(tempMatrix);
    tempMatrix[0] = cos(angle);
    tempMatrix[8] = sin(angle);
    tempMatrix[2] = -sin(angle);
    tempMatrix[10] = cos(angle);
    matrixMultiplication(matrix,tempMatrix,matrix);

}

void matrixOperation::rotateZ(float *matrix, float angle) {
    float tempMatrix[16];
    createVolume(tempMatrix);
    tempMatrix[0] = cos((angle));
    tempMatrix[4] = -sin((angle));
    tempMatrix[1] = sin((angle));
    tempMatrix[5] = cos((angle));
    matrixMultiplication(matrix, tempMatrix, matrix);
}

