rm -rf build
mkdir build
cd build
mkdir armeabi-v7a
cd armeabi-v7a
cmake -DCMAKE_TOOLCHAIN_FILE=/Users/ali-classmate/android-sdks/ndk-bundle/build/cmake/android.toolchain.cmake \
      -DANDROID_NDK=/Users/ali-classmate/android-sdks/ndk-bundle                  \
      -DCMAKE_BUILD_TYPE=Release                     \
      -DANDROID_ABI="armeabi-v7a with NEON"          \
      ../../
make
make install
cd ..
mkdir x86
cd x86
cmake -DCMAKE_TOOLCHAIN_FILE=/Users/ali-classmate/android-sdks/ndk-bundle/build/cmake/android.toolchain.cmake \
      -DANDROID_NDK=/Users/ali-classmate/android-sdks/ndk-bundle                  \
      -DCMAKE_BUILD_TYPE=Release                     \
      -DANDROID_ABI="x86"          \
      ../../
make
make install
cd ..
cd ..
