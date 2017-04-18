#include <jni.h>
#include <string>

extern "C"
jstring
Java_com_alipay_iap_ocmmuni_ocmmuni_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
