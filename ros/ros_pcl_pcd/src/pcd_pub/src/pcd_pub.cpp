#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

int main(int argc, char** argv)
{
    // 初始化ROS节点
    ros::init(argc, argv, "pcd_publisher");
    ros::NodeHandle nh;

    // 创建一个ROS发布者，用于发布点云消息
    ros::Publisher pub = nh.advertise<sensor_msgs::PointCloud2>("pointcloud", 1);

    // 读取PCD文件
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    if (pcl::io::loadPCDFile<pcl::PointXYZ>("../test.pcd", *cloud) == -1)
    {
        PCL_ERROR("Failed to read PCD file\n");
        return -1;
    }

    // 创建一个ROS点云消息
    sensor_msgs::PointCloud2 output;
    pcl::toROSMsg(*cloud, output);
    output.header.frame_id = "base_link";  // 设置点云消息的坐标系

    ros::Rate loop_rate(10);
    while (ros::ok())
    {
        // 发布ROS点云消息
        pub.publish(output);
        std::cout << "Published a point cloud." << std::endl;

        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}