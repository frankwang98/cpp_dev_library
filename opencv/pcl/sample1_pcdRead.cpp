#include <iostream>
#include <pcl/io/pcd_io.h>		//pcd输入输出头
#include <pcl/point_types.h>	//pcd点云类型头

using namespace std;

int main()
{
	// 创建一个PointCloud<pcl::PointXYZ>  boost共享指针并进行实例化
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);

	// 判断点云文件是否存在
	if (pcl::io::loadPCDFile<pcl::PointXYZ>("test_pcd.pcd", *cloud) == -1)
	{
		PCL_ERROR("Couldn't read file test_pcd.pcd \n");
		return (-1);
	}
	// 转为PCD点云类型并输出
	cout << "Loaded "
		 << cloud->width * cloud->height // 宽*高
		 << " data points from test_pcd.pcd with the following fields: "
		 << endl;
	for (size_t i = 0; i < cloud->points.size(); ++i)
		cout << "    " << cloud->points[i].x
			 << " " << cloud->points[i].y
			 << " " << cloud->points[i].z << endl;

	return (0);
}

// #include <iostream>
// #include <pcl/io/io.h>
// #include <pcl/io/pcd_io.h>
// #include <pcl/visualization/cloud_viewer.h>

// int main(int argc, char **argv) {

//     // 创建PointCloud的智能指针
//     pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGBA>);
//     // 加载pcd文件到cloud
//     pcl::io::loadPCDFile("./data/pcl_logo.pcd", *cloud);
//     pcl::visualization::CloudViewer viewer("Cloud Viewer");
//     //这里会一直阻塞直到点云被渲染
//     viewer.showCloud(cloud);

//     // 循环判断是否退出
//     while (!viewer.wasStopped()) {
//         // 你可以在这里对点云做很多处理
//     }
//     return 0;
// }
