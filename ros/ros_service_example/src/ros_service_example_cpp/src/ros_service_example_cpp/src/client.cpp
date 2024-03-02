#include <ros/ros.h>
#include "ros_service_example_cpp/Trigger.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "service_client");
    ros::NodeHandle nh;

    // 创建服务客户端
    ros::ServiceClient client = nh.serviceClient<ros_service_example_cpp::Trigger>("example_service");

    // 创建请求
    ros_service_example_cpp::Trigger srv;
    srv.request.req = 1;

    // 发送请求并等待响应
    if (client.call(srv))
    {
        // 成功接收到响应
        ROS_INFO("Received service response: %d", srv.response.res);
        ROS_INFO("Message from service: %s", srv.response.message.c_str());
    }
    else
    {
        // 未能成功发送请求
        ROS_ERROR("Failed to call service");
        return 1;
    }

    return 0;
}