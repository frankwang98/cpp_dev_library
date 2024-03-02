cmake_minimum_required(VERSION 3.0)

PROJECT(pcl-app)

set (CMAKE_CXX_STANDARD 14)

# pcl版本
FIND_PACKAGE(PCL 1.8 REQUIRED)
# 包含头文件目录
include_directories(${PCL_INCLUDE_DIRS})
# 设置依赖库链接目录
link_directories(${PCL_LIBRARY_DIRS})
# 添加预处理器和编译器标记
add_definitions(${PCL_DEFINITIONS})

add_executable(planar_segmentation segmentation/planar_segmentation.cpp)
target_link_libraries(planar_segmentation ${PCL_LIBRARIES})

add_executable(cluster_extraction segmentation/cluster_extraction.cpp)
target_link_libraries(cluster_extraction ${PCL_LIBRARIES})

# add_executable(sample3_concatenateClouds sample3_concatenateClouds.cpp)
# target_link_libraries(sample3_concatenateClouds ${PCL_LIBRARIES})

# add_executable(sample4_voxelGrid sample4_voxelGrid.cpp)
# target_link_libraries(sample4_voxelGrid ${PCL_LIBRARIES})

# add_executable(sample5_clusterSeg sample5_clusterSeg.cpp)
# target_link_libraries(sample5_clusterSeg ${PCL_LIBRARIES})

# add_executable(sample6_cloudViewer sample6_cloudViewer.cpp)
# target_link_libraries(sample6_cloudViewer ${PCL_LIBRARIES})

# add_executable(sample7_pclVisualizer sample7_pclVisualizer.cpp)
# target_link_libraries(sample7_pclVisualizer ${PCL_LIBRARIES})

# add_executable(sample8_transform sample8_transform.cpp)
# target_link_libraries(sample8_transform ${PCL_LIBRARIES})

# add_executable(sample9_kdTree sample9_kdTree.cpp)
# target_link_libraries(sample9_kdTree ${PCL_LIBRARIES})

# add_executable(sample10_octree sample10_octree.cpp)
# target_link_libraries(sample10_octree ${PCL_LIBRARIES})

# add_executable(sample11_pathThrough sample11_pathThrough.cpp)
# target_link_libraries(sample11_pathThrough ${PCL_LIBRARIES})

# add_executable(sample12_statisticalRemoval sample12_statisticalRemoval.cpp)
# target_link_libraries(sample12_statisticalRemoval ${PCL_LIBRARIES})

# add_executable(sample13_keypoints sample13_keypoints.cpp)
# target_link_libraries(sample13_keypoints ${PCL_LIBRARIES})

# add_executable(sample14_ransac sample14_ransac.cpp)
# target_link_libraries(sample14_ransac ${PCL_LIBRARIES}) # -f -sf c++14

# add_executable(sample15_normalEstimation sample15_normalEstimation.cpp)
# target_link_libraries(sample15_normalEstimation ${PCL_LIBRARIES})

# add_executable(sample16_iterative_closest_point sample16_iterative_closest_point.cpp)
# target_link_libraries(sample16_iterative_closest_point ${PCL_LIBRARIES})

# add_executable(sample17_ndt sample17_ndt.cpp)
# target_link_libraries(sample17_ndt ${PCL_LIBRARIES})

# add_executable(sample18_icp sample18_icp.cpp)
# target_link_libraries(sample18_icp ${PCL_LIBRARIES})    # 空格迭代 ./interactive_icp monkey.ply 1

# add_executable(sample10_octree sample10_octree.cpp)
# target_link_libraries(sample10_octree ${PCL_LIBRARIES})

# add_executable(sample11_pathThrough sample11_pathThrough.cpp)
# target_link_libraries(sample11_pathThrough ${PCL_LIBRARIES})

# add_executable(sample12_statisticalRemoval sample12_statisticalRemoval.cpp)
# target_link_libraries(sample12_statisticalRemoval ${PCL_LIBRARIES})

# add_executable(sample13_keypoints sample13_keypoints.cpp)
# target_link_libraries(sample13_keypoints ${PCL_LIBRARIES})