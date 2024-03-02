#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "image_pub");
    ros::NodeHandle nh;
    image_transport::ImageTransport it(nh);
    image_transport::Publisher image_pub = it.advertise("camera/image", 1);

    // 打开视频文件
    cv::VideoCapture cap("../test.mp4");
    if (!cap.isOpened())
    {
        ROS_ERROR("Failed to open video file");
        return -1;
    }

    // 定义图像消息
    sensor_msgs::ImagePtr msg;

    ros::Rate loop_rate(30); // 发布频率为30Hz
    while (ros::ok())
    {
        cv::Mat frame;
        cap >> frame; // 读取视频帧

        if (frame.empty())
        {
            ROS_INFO("Video ended");
            break;
        }

        // 转换图像格式为ROS消息
        msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame).toImageMsg();

        // 发布图像消息
        image_pub.publish(msg);
        std::cout << "Published image" << std::endl;

        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}