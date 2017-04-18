cmake_minimum_required (VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(./src DIR_LIB_SRCS)

# 指定生成链接库
add_library (OCMMUNI_TCP SHARED ${DIR_LIB_SRCS})

message(当前构建 "${DANDROID_ABI}")

include_directories(../asio)

# 指定库的安装路径 for Android
if(ANDROID)
  # Android_ABI 为android.toolchain.cmake 内部变量
  install (TARGETS OCMMUNI_TCP DESTINATION Ocmmuni/${ANDROID_ABI}/bin)
  install (FILES src/OcmmuniTCP.h DESTINATION Ocmmuni/${ANDROID_ABI}/include)
else()
  install (TARGETS OCMMUNI_TCP DESTINATION Ocmmuni/bin)
  install (FILES src/OcmmuniTCP.h DESTINATION Ocmmuni/include)
endif()
