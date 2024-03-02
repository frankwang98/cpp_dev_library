cmake_minimum_required(VERSION 3.19)
project(opencv_demo)

set(CMAKE_CXX_STANDARD 11)

set(OpenCV_DIR "D:/develop/opencv341_mingw/x64/mingw/lib")
find_package(OpenCV 3 REQUIRED)
MESSAGE("OpenCV version : ${OpenCV_VERSION}")
include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIBRARIES}) # ${OpenCV_LIB_DIR}
# local directory
#include_directories(./opencv341/include)
#link_directories(./opencv341/lib)

# QT配置
# set(QT_LIBS Qt5::Core Qt5::Gui Qt5::Widgets)
# find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
# add_executable(${PROJECT_NAME} src/main.cpp ${SOURCE_FILES} ${QT_SRC})
# target_link_libraries(${PROJECT_NAME} ${QT_LIBS})

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
    ${OpenCV_LIBRARIES} # ${OpenCV_LIBS}
#    -lopencv_core341 -lopencv_highgui341 -lopencv_imgproc341 -lopencv_imgcodecs341 -lopencv_videoio341
#    -lopencv_video341 -lopencv_objdetect341
)