#include <ros/ros.h>
#include "ros_service_example_cpp/Trigger.h"

bool triggerCallback(ros_service_example_cpp::Trigger::Request &req, ros_service_example_cpp::Trigger::Response &res)
{
    // 接收到请求后进行处理
    ROS_INFO("Received service request with default value: %d", req.req);

    // 设置响应值为1
    res.res = true;
    res.message = "Received request and replied with 1";

    return true;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "service_server");
    ros::NodeHandle nh;

    // 创建服务并指定回调函数
    ros::ServiceServer service = nh.advertiseService("example_service", triggerCallback);
    ROS_INFO("Service server is ready.");

    // 循环等待服务请求
    ros::spin();

    return 0;
}