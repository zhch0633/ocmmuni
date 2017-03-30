rm -rf build
mkdir build
cd build

mkdir math
cd math

# math
# build for android armeabi-v7a
mkdir armeabi-v7a
cd armeabi-v7a
cmake -DCMAKE_TOOLCHAIN_FILE=/Users/ali-classmate/android-sdks/ndk-bundle/build/cmake/android.toolchain.cmake \
      -DANDROID_NDK=/Users/ali-classmate/android-sdks/ndk-bundle                  \
      -DCMAKE_BUILD_TYPE=Release                     \
      -DANDROID_ABI="armeabi-v7a with NEON"          \
      ../../../math/
make
make install
cd ..

# build for android x86
mkdir x86
cd x86
cmake -DCMAKE_TOOLCHAIN_FILE=/Users/ali-classmate/android-sdks/ndk-bundle/build/cmake/android.toolchain.cmake \
      -DANDROID_NDK=/Users/ali-classmate/android-sdks/ndk-bundle                  \
      -DCMAKE_BUILD_TYPE=Release                     \
      -DANDROID_ABI="x86"          \
      ../../../math/
make
make install
cd ..

# build for dev environment os debug
mkdir dev
cd dev
cmake ../../../math/
make
make install
cd ..
cd ..

mkdir ocmtcp
cd ocmtcp

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

# build for android x86
mkdir x86
cd x86
cmake -DCMAKE_TOOLCHAIN_FILE=/Users/ali-classmate/android-sdks/ndk-bundle/build/cmake/android.toolchain.cmake \
      -DANDROID_NDK=/Users/ali-classmate/android-sdks/ndk-bundle                  \
      -DCMAKE_BUILD_TYPE=Release                     \
      -DANDROID_ABI="x86"          \
      ../../../ocmtcp/
make
make install
cd ..

# build for dev environment os debug
mkdir dev
cd dev
cmake ../../../ocmtcp/
make
make install
cd ..
cd ..


mkdir portal
cd portal

# Portal project
# build for android armeabi-v7a
mkdir armeabi-v7a
cd armeabi-v7a
cmake -DCMAKE_TOOLCHAIN_FILE=/Users/ali-classmate/android-sdks/ndk-bundle/build/cmake/android.toolchain.cmake \
      -DANDROID_NDK=/Users/ali-classmate/android-sdks/ndk-bundle                  \
      -DCMAKE_BUILD_TYPE=Release                     \
      -DANDROID_ABI="armeabi-v7a with NEON"          \
      ../../../
make
make install
cd ..

# build for android x86
mkdir x86
cd x86
cmake -DCMAKE_TOOLCHAIN_FILE=/Users/ali-classmate/android-sdks/ndk-bundle/build/cmake/android.toolchain.cmake \
      -DANDROID_NDK=/Users/ali-classmate/android-sdks/ndk-bundle                  \
      -DCMAKE_BUILD_TYPE=Release                     \
      -DANDROID_ABI="x86"          \
      ../../../
make
make install
cd ..

# build for dev environment os debug
mkdir dev
cd dev
cmake ../../../
make
make install
cd ..
cd ..
