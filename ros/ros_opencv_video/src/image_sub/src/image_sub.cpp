#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>

void imageCallback(const sensor_msgs::ImageConstPtr &msg)
{
    try
    {
        // 将ROS图像消息转换为OpenCV图像
        cv::Mat image = cv_bridge::toCvShare(msg, "bgr8")->image;

        // 显示图像
        cv::imshow("Image", image);
        cv::waitKey(1);
    }
    catch (cv_bridge::Exception &e)
    {
        ROS_ERROR("Failed to convert ROS image to OpenCV image: %s", e.what());
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "image_sub");
    ros::NodeHandle nh;

    // 创建图像传输对象和订阅者
    image_transport::ImageTransport it(nh);
    image_transport::Subscriber sub = it.subscribe("camera/image", 1, imageCallback);

    // 创建opencv窗口本地显示
    cv::namedWindow("Image", cv::WINDOW_AUTOSIZE);
    
    ros::spin();

    cv::destroyAllWindows();

    return 0;
}