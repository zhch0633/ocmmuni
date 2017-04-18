#交叉编译网络库笔记
## 1 网络库选型
比较相关网上资料认为选用成熟的C++网络库作为基础比较有利于跨平台开发（实际上效率不一定高。。。）总的来说有以下几个：
·libevent 这儿库比较集中在unix平台，对于跨平台支持相对比较不足有待考虑，社区很活跃看了一下代码
·ACE 成熟的商业网络库，比较大不适合无线开发，听说使用十分广泛
·BOOST ASIO 强调跨平台能力的网络库，相对来说还是比较合适的但是也是有坑的

## BOOST ASIO Cmake 跨平台
参考网上已有的 BOOST 文档，boost 库原则上是hpp库，基本与平台无关，然而少数几个关键库还是需要相关平台的支持的。这几个库中就包含对于网络比较重要的

Boost_SYSTEM_LIBRARY
Boost_THREAD_LIBRARY
Boost_REGEX_LIBRARY

从网络API层面来说，不同平台的网络和异步实现是各不相同的，所以ASIO的主要任务就是把这些平台不同的库转换成统一的网络编程接口，所以对于跨平台性要在编译配置中抹平参考官方文档，知道Boost_System需要对boost 进行本地编译

### BOOST 本地编译
如果直接在代码中引入
```
#include <boost/asio.hpp>
```
会发现编译出现错误，提示找不到system相关的symbol，这说明asio会依赖boost.system库来进行操作系统适配，因此需要首先编译boost.system

boost源码（不能使用brew install boost 否则安装不上）中自带的 configure.sh 生成一个.b2 文件相当于make文件，运行后会在本地编译boost源码，并且安装到boost本地库中。这是一个比较标准的方式。而boost本身也没有提供跨平台的编译配置（原先有一个boost.cmake）后来取消了。

继续查找资料发现 cmake内部实际上有一个find_boost模块，专门用来支持boost的编译。于是修改cmake文件为以下格式。

```
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

```
测试在安卓平台编译，没有发现问题。
