#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/visualization/cloud_viewer.h>

pcl::visualization::CloudViewer viewer("PointCloud Viewer");

void cloudCallback(const sensor_msgs::PointCloud2ConstPtr& msg)
{
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::fromROSMsg(*msg, *cloud);

    // 获取点云数据的大小（字节数）
    size_t pointCloudSize = msg->data.size();

    ROS_INFO("Received point cloud size: %zu bytes", pointCloudSize);

    if (!viewer.wasStopped())
        viewer.showCloud(cloud);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "pcl_viewer");
    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe<sensor_msgs::PointCloud2>("pointcloud", 1, cloudCallback);

    ros::spin();

    return 0;
}