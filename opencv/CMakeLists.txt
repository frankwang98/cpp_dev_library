cmake_minimum_required (VERSION 3.0)

PROJECT(opencv-basic)

set (CMAKE_CXX_STANDARD 11)

# Requires OpenCV
# OpenCV版本
# set(OpenCV_DIR D:/develop/opencv454/build/x64/vc15/lib)
FIND_PACKAGE( OpenCV 4 REQUIRED )
MESSAGE("OpenCV version : ${OpenCV_VERSION}")

# QT配置
# set(QT_LIBS Qt5::Core Qt5::Gui Qt5::Widgets)
# find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
# add_executable(${PROJECT_NAME} src/main.cpp ${SOURCE_FILES} ${QT_SRC})
# target_link_libraries(${PROJECT_NAME} ${QT_LIBS})

include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIB_DIR})

ADD_EXECUTABLE( sample1_imread sample1_imread.cpp )
TARGET_LINK_LIBRARIES( sample1_imread ${OpenCV_LIBS} )

ADD_EXECUTABLE( sample2_cap sample2_cap.cpp )
TARGET_LINK_LIBRARIES( sample2_cap ${OpenCV_LIBS} )

ADD_EXECUTABLE( sample3_filestorage sample3_filestorage.cpp )
TARGET_LINK_LIBRARIES( sample3_filestorage ${OpenCV_LIBS} )

ADD_EXECUTABLE( sample4_destroy sample4_destroy.cpp )
TARGET_LINK_LIBRARIES( sample4_destroy ${OpenCV_LIBS} ) # need qt support

ADD_EXECUTABLE( sample5_displayOverlay sample5_displayOverlay.cpp )
TARGET_LINK_LIBRARIES( sample5_displayOverlay ${OpenCV_LIBS} )

ADD_EXECUTABLE( sample6_createTrackbar sample6_createTrackbar.cpp )
TARGET_LINK_LIBRARIES( sample6_createTrackbar ${OpenCV_LIBS} )

ADD_EXECUTABLE( sample7_createButton sample7_createButton.cpp )
TARGET_LINK_LIBRARIES( sample7_createButton ${OpenCV_LIBS} )

ADD_EXECUTABLE( sample8_opengl sample8_opengl.cpp )
TARGET_LINK_LIBRARIES( sample8_opengl ${OpenCV_LIBS} -lglut -lGL -lGLU)

ADD_EXECUTABLE( sample9_viz3d sample9_viz3d.cpp )
TARGET_LINK_LIBRARIES( sample9_viz3d ${OpenCV_LIBS} )

ADD_EXECUTABLE( sample10_photoTool sample10_photoTool.cpp )
TARGET_LINK_LIBRARIES( sample10_photoTool ${OpenCV_LIBS} )

ADD_EXECUTABLE( sample11_multiImageWindow sample11_multiImageWindow.cpp utils/MultipleImageWindow.cpp)
TARGET_LINK_LIBRARIES( sample11_multiImageWindow ${OpenCV_LIBS} )

ADD_EXECUTABLE( sample12_colorHsv sample12_colorHsv.cpp)
TARGET_LINK_LIBRARIES( sample12_colorHsv ${OpenCV_LIBS} )

ADD_EXECUTABLE( sample13_combineImgs sample13_combineImgs.cpp )
TARGET_LINK_LIBRARIES( sample13_combineImgs ${OpenCV_LIBS})

# ADD_EXECUTABLE( sample9_viz3d sample9_viz3d.cpp )
# TARGET_LINK_LIBRARIES( sample9_viz3d ${OpenCV_LIBS} )

# ADD_EXECUTABLE( sample10_photoTool sample10_photoTool.cpp )
# TARGET_LINK_LIBRARIES( sample10_photoTool ${OpenCV_LIBS} )

# ADD_EXECUTABLE( sample11_multiImageWindow sample11_multiImageWindow.cpp utils/MultipleImageWindow.cpp)
# TARGET_LINK_LIBRARIES( sample11_multiImageWindow ${OpenCV_LIBS} )

# ADD_EXECUTABLE( sample11_multiImageWindow sample11_multiImageWindow.cpp utils/MultipleImageWindow.cpp)
# TARGET_LINK_LIBRARIES( sample11_multiImageWindow ${OpenCV_LIBS} )

