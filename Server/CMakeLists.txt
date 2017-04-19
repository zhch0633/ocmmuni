cmake_minimum_required(VERSION 3.3)
project(Server)

aux_source_directory(./examples/allocation DIR_LIB_SRCS)

# add boost to compilation of server
SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD ON)
find_package(Boost 1.63.0 REQUIRED COMPONENTS system thread regex)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
endif(Boost_FOUND)

# use BOOST system to fit asio compilation
set(USED_LIBS ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_REGEX_LIBRARY})

#add boost to excutors
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(Server ${DIR_LIB_SRCS})
target_link_libraries(Server ${USED_LIBS})
