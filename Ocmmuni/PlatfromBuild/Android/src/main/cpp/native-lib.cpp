#include <jni.h>
#include <string>
#include <OcmmuniTCP.h>
#include <MathFunctions.h>
#include <android/log.h>

extern "C"
jstring Java_com_alipay_iap_ocmmuni_ocmmuni_Entry_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    double result = power(2,2);

    if(result == 4){
        hello = "hello and true";
    }

    __android_log_print(ANDROID_LOG_DEBUG,"native_ocmmuni", "");
    TestSocket();
    return env->NewStringUTF(hello.c_str());
}


