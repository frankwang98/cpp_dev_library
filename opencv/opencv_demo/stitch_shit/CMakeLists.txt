cmake_minimum_required(VERSION 3.1)
project(cv_stitch)

# 编译配置
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++11 ")

# 查找包
find_package(OpenCV 4 REQUIRED) 

# 添加头文件
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# 编译
add_executable(cv_stitch main.cpp 
)

target_link_libraries(cv_stitch ${OpenCV_LIBS})
