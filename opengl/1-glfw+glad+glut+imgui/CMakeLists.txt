cmake_minimum_required(VERSION 3.19)
project(opengl_demo)

set(CMAKE_CXX_STANDARD 14)

include_directories("./env/include")
link_directories("./env/lib")
include_directories("./env/imgui")
include_directories("./env/imgui/backends")

set(OpenCV_DIR "D:/develop/opencv341_mingw/x64/mingw/lib")
find_package(OpenCV 3 REQUIRED)
MESSAGE("OpenCV version : ${OpenCV_VERSION}")
include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIBRARIES}) # ${OpenCV_LIB_DIR}

file(GLOB IMGUI "./env/imgui/*.cpp") # 1.80

add_executable(opengl_demo main.cpp env/glad.c ${IMGUI})
target_link_libraries(opengl_demo
        glfw3 # 3.3.9
        opengl32
        freeglut # 3.4.0
        glu32
        ${OpenCV_LIBRARIES}
        xinput
)