cmake_minimum_required (VERSION 2.8)

SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD ON)
find_package(Boost 1.63.0 REQUIRED COMPONENTS system thread regex)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  link_directories(${Boost_LIBRARY_DIRS})
endif(Boost_FOUND)

set(USED_LIBS ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_REGEX_LIBRARY})

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(./src DIR_LIB_SRCS)

# 指定生成链接库
add_library (OCMMUNI_TCP SHARED ${DIR_LIB_SRCS})
target_link_libraries(OCMMUNI_TCP ${USED_LIBS})

message(当前构建 "${DANDROID_ABI}")

# 指定库的安装路径 for Android
if(ANDROID)
  # Android_ABI 为android.toolchain.cmake 内部变量
  install (TARGETS OCMMUNI_TCP DESTINATION Ocmmuni/${ANDROID_ABI}/bin)
  install (FILES src/OcmmuniTCP.h DESTINATION Ocmmuni/${ANDROID_ABI}/include)
else()
  install (TARGETS OCMMUNI_TCP DESTINATION Ocmmuni/bin)
  install (FILES src/OcmmuniTCP.h DESTINATION Ocmmuni/include)
endif()
