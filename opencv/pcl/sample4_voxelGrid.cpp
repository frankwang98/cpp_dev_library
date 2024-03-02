#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>

int main(int argc, char** argv)
{

	pcl::PCLPointCloud2::Ptr cloud(new pcl::PCLPointCloud2());
	pcl::PCLPointCloud2::Ptr cloud_filtered(new pcl::PCLPointCloud2());

	//点云对象的读取
	pcl::PCDReader reader;

	reader.read("../data_pcd/test.pcd", *cloud);    //读取点云到cloud中

	std::cerr << "PointCloud before filtering: " << cloud->width * cloud->height
		<< " data points (" << pcl::getFieldsList(*cloud) << ").";

	/******************************************************************************
	创建一个voxel体素大小为1cm的pcl::VoxelGrid滤波器，
	**********************************************************************************/
	pcl::VoxelGrid<pcl::PCLPointCloud2> sor;  //创建滤波对象
	sor.setInputCloud(cloud);            //设置需要过滤的点云给滤波对象
	float leftSize = 0.1f;
	sor.setLeafSize(leftSize, leftSize, leftSize);  //设置滤波时创建的体素体积为1cm的立方体
	sor.filter(*cloud_filtered);           //执行滤波处理，存储输出

	std::cerr << "PointCloud after filtering: " << cloud_filtered->width * cloud_filtered->height
		<< " data points (" << pcl::getFieldsList(*cloud_filtered) << ").";

	pcl::PCDWriter writer;
	writer.write("../data_pcd/test_voxelgrid.pcd", *cloud_filtered,
		Eigen::Vector4f::Zero(), Eigen::Quaternionf::Identity(), false);

	return (0);
}

// int main(int argc, char **argv)
// {
// 	pcl::PCLPointCloud2::Ptr cloud(new pcl::PCLPointCloud2());
// 	pcl::PCLPointCloud2::Ptr cloud_filtered(new pcl::PCLPointCloud2());

// 	// 从文件读取点云图
// 	// Fill in the cloud data
// 	pcl::PCDReader reader;
// 	// Replace the path below with the path where you saved your file
// 	reader.read("./data/table_scene_lms400.pcd", *cloud); // Remember to download the file first!

// 	std::cerr << "PointCloud before filtering: " << cloud->width * cloud->height
// 			  << " data points (" << pcl::getFieldsList(*cloud) << ").";

// 	// 创建一个长宽高分别是1cm的体素过滤器，cloud作为输入数据，cloud_filtered作为输出数据
// 	float leftSize = 0.01f;
// 	// Create the filtering object
// 	pcl::VoxelGrid<pcl::PCLPointCloud2> sor;
// 	sor.setInputCloud(cloud);
// 	sor.setLeafSize(leftSize, leftSize, leftSize);
// 	sor.filter(*cloud_filtered);

// 	std::cerr << "PointCloud after filtering: " << cloud_filtered->width * cloud_filtered->height
// 			  << " data points (" << pcl::getFieldsList(*cloud_filtered) << ").";

// 	// 将结果输出到文件
// 	pcl::PCDWriter writer;
// 	writer.write("./data/table_scene_lms400_downsampled.pcd", *cloud_filtered);

// 	return (0);
// }
