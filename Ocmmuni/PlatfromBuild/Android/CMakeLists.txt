# Sets the minimum version of CMake required to build the native
# library. You should either keep the default value or only pass a
# value of 3.4.0 or lower.

cmake_minimum_required(VERSION 3.4.1)

if(ANDROID)
    # 头文件位置
    include_directories(${CMAKE_INSTALL_PREFIX}/Ocmmuni/${ANDROID_ABI}/include)
    # 库位置
    link_directories(${CMAKE_INSTALL_PREFIX}/Ocmmuni/${ANDROID_ABI}/bin)
endif()


# 是否加入 MathFunctions 库
# if (NOT HAVE_POW)
set (EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
# endif (NOT HAVE_POW)
set (OCMMUNI_TCP_LIB ${OCMMUNI_TCP_LIB} OCMMUNI_TCP)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds it for you.
# Gradle automatically packages shared libraries with your APK.

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

target_link_libraries (native-lib ${EXTRA_LIBS})

target_link_libraries (native-lib ${OCMMUNI_TCP_LIB})