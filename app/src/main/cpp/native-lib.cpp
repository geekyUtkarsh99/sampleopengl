#include <jni.h>
#include <string>
#include "android//log.h"
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include "triangle.h"
#include "thread"
#include "fstream"
#include "square.h"
#include "pyramid.h"
#include "mappingClass.h"
#define LOG_TAG "libNative"
#include <cstdlib>
#include "android/bitmap.h"
#include "vboExample.h"
#include "multiShader.h"
#include "testdepth.h"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)


bool checkLoad = false;

// TRIANGLE EXAMPLE --- //
static const char glVertexShader[] =
        "attribute vec4 vPosition;\n"
        "void main()\n"
        "{\n"
        "  gl_Position = vPosition;\n"
        "}\n";

static const char glFragmentShader[] =
        "void main()\n"
        "{\n"
        "  gl_FragColor = vec4(0.0, 1.0, 1.0, 1.0);\n"
        "}\n";

float x = 0.0f;

GLuint loadShader(GLenum shaderType, const char* shaderSource)
{
    GLuint shader = glCreateShader(shaderType);
    if (shader)
    {
        glShaderSource(shader, 1, &shaderSource, NULL);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled)
        {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen)
            {
                char * buf = (char*) malloc(infoLen);
                if (buf)
                {
                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
                    LOGE("Could not Compile Shader %d:\n%s\n", shaderType, buf);
                    free(buf);
                }
                glDeleteShader(shader);
                shader = 0;
            }
        }
    }
    return shader;
}

GLuint createProgram(const char* vertexSource, const char * fragmentSource)
{
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vertexSource);
    if (!vertexShader)
    {
        return 0;
    }
    GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentSource);
    if (!fragmentShader)
    {
        return 0;
    }
    GLuint program = glCreateProgram();
    if (program)
    {
        glAttachShader(program , vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program , GL_LINK_STATUS, &linkStatus);
        if( linkStatus != GL_TRUE)
        {
            GLint bufLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength)
            {
                char* buf = (char*) malloc(bufLength);
                if (buf)
                {
                    glGetProgramInfoLog(program, bufLength, NULL, buf);
                    LOGE("Could not link program:\n%s\n", buf);
                    free(buf);
                }
            }
            glDeleteProgram(program);
            program = 0;
        }
    }
    return program;
}

GLuint simpleTriangleProgram;
GLuint vPosition;
bool setupGraphics(int w, int h)
{
    simpleTriangleProgram = createProgram(glVertexShader, glFragmentShader);
    if (!simpleTriangleProgram)
    {
        LOGE ("Could not create program");
        return false;
    }
    vPosition = glGetAttribLocation(simpleTriangleProgram, "vPosition");
    glViewport(250, 100, 100, 100);
    return true;
}

//co-ordinates
 GLfloat triangleVertices[] = {
        0.0f, 1.0f,
        -1.0f, -1.0f,
        1.0f, -1.0f
};
void renderFrame()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear (GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glUseProgram(simpleTriangleProgram);
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0 ,triangleVertices);
    glEnableVertexAttribArray(vPosition);
    glDrawArrays(GL_TRIANGLES, 0, 3);

}

// --- //



static triangle tr(0,0); //working
GLuint programp;
static square sq(1,0 , programp); //working

static pyramid pyr;//working

//mapping example
static mappingClass map(0,0); //working

//vbo
auto * vbo = new vboExample(); //working

auto * multi = new multiShader();
auto * test = new testdepth();

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_sampleopengl_libHolder_stringFromJNI(JNIEnv *env, jclass clazz) {
    // TODO: implement stringFromJNI()
    std::string hello = "Hello from C++";

    LOGI("log worked..... !");


    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_sampleopengl_libHolder_changeSurface(JNIEnv *env, jclass clazz, jint w, jint h) {
    // TODO: implement changeSurface()


//    tr.setupVoid(w,h);


//map.setupGraphics(w,h); //worked

//
//   if (checkLoad)
//   sq.setupGraphics(w,h);

//   pyr.setupGraphics(w,h);

//vbo->setupGraphics(w,h);


//if (checkLoad)
//    multi->setupGL(w,h);

test->swtupDL(w , h);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_sampleopengl_libHolder_createSurface(JNIEnv *env, jclass clazz) {
    // TODO: implement createSurface()


//tr.render();

//map.render(); //worked

// if (checkLoad)
//   sq.render();

//pyr.render();
//    vbo->vborender();

//if (checkLoad)
//    multi->render();
    test->render();
}


extern "C"
JNIEXPORT void JNICALL
Java_com_example_sampleopengl_libHolder_updateVals(JNIEnv *env, jclass clazz) {
    // TODO: implement updateVals()
 // tr.updateAngle();
//    tr.move();
 //   (*tr1).move();
    //tr.move();


    //square traversal
//    if (checkLoad)
//    sq.move();
test->loadAssets();


}


extern "C"
JNIEXPORT void JNICALL
Java_com_example_sampleopengl_libHolder_getImage(JNIEnv *env, jclass clazz, jcharArray a) {
    // TODO: implement getImage()

   // tr.pixel = reinterpret_cast<unsigned char *>(a);


}extern "C"
JNIEXPORT void JNICALL
Java_com_example_sampleopengl_libHolder_deliverImages(JNIEnv *env, jclass clazz, jbyteArray image,int width,int height) {
    // TODO: implement deliverImages()

//    int len = env->GetArrayLength(image);
//      unsigned char* buffer = new  unsigned char[len];
//    env->GetByteArrayRegion(image, 0, len, reinterpret_cast<jbyte *>(buffer));

//    checkLoad =   sq.loadImage(buffer,width,height);


}extern "C"
JNIEXPORT void JNICALL
Java_com_example_sampleopengl_libHolder_send_1pixel(JNIEnv *env, jclass clazz, jobject image,
                                                    jint w, jint h) {
    // TODO: implement send_pixel()

    void * pixels ;
    AndroidBitmapInfo  info;

    AndroidBitmap_getInfo(env,image,&info);
    AndroidBitmap_lockPixels(env,image,&pixels);
    auto * realImage = (unsigned  char * )pixels;
    AndroidBitmap_unlockPixels(env,image);

    checkLoad = sq.loadImage(realImage,w,h);


}