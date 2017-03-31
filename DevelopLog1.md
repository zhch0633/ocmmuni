# Android NDK 交叉编译记录
## 1 NDK 的CMake 编译
之前一段时间Android NDK 官方使用 Android.mk 进行编译，我推测这一编译方式主要是来源于 Android 系统C++库的编译流程。Make 确实是比较便利的编译方式之一但是对于跨平台交叉编译提供的支持毕竟少。最近的升级中 NDK 推出了CMake 编译方式，CMake 可以自动根据编译平台和目标平台进行 Tool Chain 的配置，并通过这些简单的配置进行交叉编译。这是开发跨平台 C++ 程序的良好基础。首先我们看 Gradle 是如何启动 CMake 并编译 Native 源码。

```
android{
  externalNativeBuild {
        cmake {
            path "CMakeLists.txt"
        }
    }
}
```

此时就可以写 CMakeLists.txt 了。其中最关键是下列的语句。用来生成一个 native-lib.so 动态链接库，需要注意到 gradle 会使用ndk 的内置工具链来编译这C++代码，所以会针对不同的 ABI编译不同版本。

```
add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             # Associated headers in the same location as their source
             # file are automatically included.
             src/main/cpp/native-lib.cpp )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because system libraries are included in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in the
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       native-lib

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )
```

## 2 独立进行 NDK 交叉编译
我们要开发一个跨平台C++库，所以不能指望使用Gradle 来主动调用我们的 CMake 文件，同时我们也需要针对 Android 的ABI进行交叉编译。所以需要直接使用 NDK 中内置的 toolchain。使用方法是首先指定好 NDK 的位置环境变量。然后使用如下语句一次编译一个ABI。

```
#OCMTCP
# build for android armeabi-v7a
mkdir armeabi-v7a
cd armeabi-v7a
cmake -DCMAKE_TOOLCHAIN_FILE=/Users/ali-classmate/android-sdks/ndk-bundle/build/cmake/android.toolchain.cmake \
      -DANDROID_NDK=/Users/ali-classmate/android-sdks/ndk-bundle                  \
      -DCMAKE_BUILD_TYPE=Release                     \
      -DANDROID_ABI="armeabi-v7a with NEON"          \
      ../../../ocmtcp/
make
make install
cd ..
```

如此编译好所有需要的 ABI，并打包成 .so 文件分别存放用来给NDK链接。

CMake 有一个特定的Install路径，在各个平台上编译时便于库的统一存放，因此我们依据各个平台来运算这个偏移量，方便各个平台找到自己适用的动态链接库。

```
# 指定库的安装路径 for Android
if(ANDROID)
  # Android_ABI 为android.toolchain.cmake 内部变量
  install (TARGETS OCMMUNI_TCP DESTINATION Ocmmuni/${ANDROID_ABI}/bin)
  install (FILES src/OcmmuniTCP.h DESTINATION Ocmmuni/${ANDROID_ABI}/include)
else()
  install (TARGETS OCMMUNI_TCP DESTINATION Ocmmuni/bin)
  install (FILES src/OcmmuniTCP.h DESTINATION Ocmmuni/include)
endif()
```

## 3 NDK 调用预编译动态链接库
准备好 .so 动态链接库后，我们可以回到之前Android 工程中的CMake 文件，同样我们运算库的偏移量来在各个库编译时期找到对应的 ABI链接库，这一步很重要不能找错。同时我们可以找到对应的头文件。

```
if(ANDROID)
    # 头文件位置
    include_directories(${CMAKE_INSTALL_PREFIX}/Ocmmuni/${ANDROID_ABI}/include)
    # 库位置
    link_directories(${CMAKE_INSTALL_PREFIX}/Ocmmuni/${ANDROID_ABI}/bin)
    else()
    # Not Android situation for PC platform
    include_directories(${CMAKE_INSTALL_PREFIX}/Ocmmuni/include)
    link_directories(${CMAKE_INSTALL_PREFIX}/Ocmmuni/bin)
endif()
```
如此我们就找到了之前编译完成的库文件，这里else语句中是我用来给本平台编译的打包流程，这样可以首先在本平台开发完成，同一套源码不变打包到 NDK平台。
至此我们完成了Android编译环境的配置。下一步是配置IOS的编译环境。
