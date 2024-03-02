#include <iostream>
#include <pcl/io/pcd_io.h>	//pcd输入输出头
#include <pcl/point_types.h>	//pcd点云类型头

using namespace std;

int main()
{
	pcl::PointCloud<pcl::PointXYZ> cloud;	//实例化模板类PointCloud，类型为PointXYZ

	//写入点云数据，用随机数填充
	cloud.width = 5;
	cloud.height = 1;
	cloud.is_dense = false;	//是否是稠密型
	cloud.resize(cloud.width * cloud.height);

	for (auto& point : cloud)
	{
		point.x = 1024 * rand() / (RAND_MAX + 1.0f);
		point.y = 1024 * rand() / (RAND_MAX + 1.0f);
		point.z = 1024 * rand() / (RAND_MAX + 1.0f);
	}

	pcl::io::savePCDFileASCII("test_pcd.pcd", cloud);
	cerr << "Saved " << cloud.size() << " data points to test_pcd.pcd." << endl;
	//cerr：输出到标准错误的ostream对象，常用于程序错误信息；

	for(const auto& point: cloud)
		cerr << "    " << point.x << " " << point.y << " " << point.z << endl;

	return 0;
}
