//
// Created by DELL on 17-08-2021.
//

#include "testdepth.h"
#include "android/log.h"


void testdepth::render() {

pyr->render();


}

testdepth::testdepth() {

//    pyr = new pyramid();

pyr = new pyramid();

}

void testdepth::swtupDL(int w, int h) {

   pyr->setupGraphics(w ,h);
}

void testdepth::loadAssets() {
    if (!pyr->startRender)
    pyr->startRender = true;
}
