#include <jni.h>
#include <string>
#include "../../../ndkgen/ocmtcp/lib/OcmmuniTCP.h"

extern "C"
jstring
Java_com_alipay_iap_ocmmuni_ocmmuni_Entry_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    HelloFunc();

    return env->NewStringUTF(hello.c_str());
}
