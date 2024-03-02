#include <iostream>
#include <opencv2/opencv.hpp>

cv::Mat lane_detect(cv::Mat &image)
{
    // 定义感兴趣区域（ROI）
    int roiHeight = image.rows / 2;
    cv::Rect roi(0, roiHeight, image.cols, roiHeight);
    cv::Mat roiImage = image(roi).clone();

    // 灰度化
    cv::Mat gray;
    cv::cvtColor(roiImage, gray, cv::COLOR_BGR2GRAY);

    // 对灰度图像进行高斯模糊去噪
    cv::Mat blurred;
    cv::GaussianBlur(gray, blurred, cv::Size(5, 5), 0);

    // 对去噪后的图像应用Canny边缘检测
    cv::Mat edges;
    cv::Canny(blurred, edges, 50, 150);

    // 霍夫线变换
    std::vector<cv::Vec4i> lines;
    cv::HoughLinesP(edges, lines, 1, CV_PI / 180, 50, 50, 10);

    // 绘制检测到的车道线
    cv::Mat result = roiImage.clone();
    for (size_t i = 0; i < lines.size(); ++i)
    {
        cv::Vec4i line = lines[i];
        line[1] += roiHeight;  // 调整线段的起点和终点的y坐标
        line[3] += roiHeight;
        cv::line(image, cv::Point(line[0], line[1]), cv::Point(line[2], line[3]), cv::Scalar(0, 0, 255), 2);
    }

    // 在原始图像中绘制ROI区域
    cv::rectangle(image, roi, cv::Scalar(0, 255, 0), 2);
    return image;
}

int main()
{
    // 读取输入图像
//    std::string image_path = "../data/road2.png";
//    cv::Mat image = cv::imread(image_path);

    // 读取视频
    cv::VideoCapture cap("../data/dashcam2.mp4");
    if (!cap.isOpened()) {
        std::cout << "video can't open" << std::endl;
        return -1;
    }

    // 获取输入视频的参数
    int frameWidth = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    int frameHeight = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
    double fps = cap.get(cv::CAP_PROP_FPS);

    // 创建视频编写器
    cv::VideoWriter writer("output_video.mp4", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, cv::Size(frameWidth, frameHeight));
    if (!writer.isOpened()) {
        std::cout << "video writer failed" << std::endl;
        return -1;
    }

    while (true)
    {
        cv::Mat image;
        cap.read(image);
        if (image.empty()) {
            break;
        }
        cv::Mat result = lane_detect(image);

        // 将处理后的帧写入视频编写器
        writer.write(result);

        // 显示结果
        cv::namedWindow("Lane Detection", cv::WINDOW_NORMAL);
        cv::resizeWindow("Lane Detection", 1080, 960);
        cv::imshow("Lane Detection", result);
//        cv::waitKey(0);
        if (cv::waitKey(30) >= 0)
            break;
    }
    cap.release();
    cv::destroyAllWindows();

    return 0;
}
