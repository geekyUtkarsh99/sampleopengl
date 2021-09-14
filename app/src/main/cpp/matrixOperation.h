//
// Created by DELL on 01-04-2021.
//

#ifndef SAMPLEOPENGL_MATRIXOPERATION_H
#define SAMPLEOPENGL_MATRIXOPERATION_H


class matrixOperation {

public:

    void createVolume(float * matrix);
    void matrixMultiplication(float * dest,float * operand1,float * operand2);
    void translation(float x,float y,float z,float * matrix);

    //radians rotation
    void rotateX(float * matrix,float angle);
    void rotateY(float * matrix,float angle);
    void rotateZ(float * matrix,float angle);

    //setup the projection view
    void perspective(float * matrix,float fov,float aspectRatio,float zNear,float zFar);
    void frustum(float * matrix,float left ,float right ,float bottom,float top,float zNear,float zFar);


};


#endif //SAMPLEOPENGL_MATRIXOPERATION_H
