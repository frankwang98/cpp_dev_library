cmake_minimum_required(VERSION 3.0)
project(tiny_clib)

# 编译配置
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++11 ") #-lpthread -lprotobuf -lboost_system

# 查找包
find_package(Protobuf REQUIRED) 
# find_package(Threads REQUIRED)
# find_package(Boost REQUIRED COMPONENTS system thread filesystem)
# find_package(OpenCV REQUIRED) 

# 添加头文件
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
# include_directories(${Protobuf_INCLUDE_DIRS})
# include_directories(${Boost_INCLUDE_DIRS})
# INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})

# 编译
add_executable(test_mathutils test/test_mathutils.cc src/mathutils/mathutils.cc
)

add_executable(test_timeutils test/test_timeutils.cc src/timeutils/timeutils.cc
)

add_executable(test_stringutils test/test_stringutils.cc src/stringutils/stringutils.cc
)

add_executable(test_logutils test/test_logutils.cc src/logutils/logutils.cc
)

add_executable(test_ioutils test/test_ioutils.cc src/ioutils/ioutils.cc
)

add_executable(test_cryptoutils test/test_cryptoutils.cc src/cryptoutils/cryptoutils.cc
)

add_executable(test_dsutils test/test_dsutils.cc src/dsutils/dsutils.cc
)

add_executable(test_algoutils test/test_algoutils.cc src/algoutils/algoutils.cc
)

add_executable(test_networklib test/test_networklib.cc src/networklib/networklib.cc
)

add_executable(test_networklib2 test/test_networklib2.cc src/networklib/networklib.cc
)

add_executable(test_threadlib test/test_threadlib.cc src/threadlib/threadlib.cc
)


# 链接库
target_link_libraries(test_mathutils ${CMAKE_THREAD_LIBS_INIT} ) # ${PROTOBUF_LIBRARIES} ${Boost_LIBRARIES} ${OpenCV_LIBS} -luuid -lcurl

target_link_libraries(test_ioutils ${CMAKE_THREAD_LIBS_INIT} )

target_link_libraries(test_cryptoutils ${CMAKE_THREAD_LIBS_INIT} -lssl -lcrypto -lboost_system )

target_link_libraries(test_networklib ${CMAKE_THREAD_LIBS_INIT} )

target_link_libraries(test_threadlib ${CMAKE_THREAD_LIBS_INIT} -lpthread )

target_link_libraries(test_timeutils ${CMAKE_THREAD_LIBS_INIT} -luuid)
