cmake_minimum_required (VERSION 2.8)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(./src DIR_LIB_SRCS)

# 指定生成链接库
add_library (MathFunctions SHARED ${DIR_LIB_SRCS})

message(当前构建 "${DANDROID_ABI}")

# 指定库的安装路径 for Android
if(ANDROID)
  # Android_ABI 为android.toolchain.cmake 内部变量
  install (TARGETS MathFunctions DESTINATION Ocmmuni/${ANDROID_ABI}/bin)
  install (FILES src/MathFunctions.h DESTINATION Ocmmuni/${ANDROID_ABI}/include)
else()
  install (TARGETS MathFunctions DESTINATION Ocmmuni/bin)
  install (FILES src/MathFunctions.h DESTINATION Ocmmuni/include)
endif()
