//
// Created by DELL on 17-08-2021.
//

#ifndef SAMPLEOPENGL_TESTDEPTH_H
#define SAMPLEOPENGL_TESTDEPTH_H
#include "GLES2//gl2.h"
#include "GLES2/gl2ext.h"
#include "pyramid.h"

class testdepth {
public:
    pyramid * pyr  = nullptr;

    void render();
    testdepth();
    void swtupDL(int w , int h);
    void loadAssets();



};


#endif //SAMPLEOPENGL_TESTDEPTH_H
