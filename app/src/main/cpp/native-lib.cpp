#include <jni.h>
#include <string>

#include "cv.h"

#include "cv.h"

extern "C" JNIEXPORT jstring JNICALL
Java_opencv_library_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    cvCreateImage(CvSize(1.0f, 1.0f), 1, 1);
    return env->NewStringUTF(hello.c_str());
}
