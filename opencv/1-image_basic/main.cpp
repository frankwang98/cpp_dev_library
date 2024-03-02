#include <iostream>
#include <opencv2/opencv.hpp>

cv::Mat image;
int thresholdValue = 0;
int maxValue = 255;

// Trackbar回调函数
void onTrackbar(int value, void* userdata)
{
    cv::Mat thresholded;
    cv::threshold(image, thresholded, value, maxValue, cv::THRESH_BINARY);

//    cv::imshow("Thresholded Image", thresholded);
}

int main()
{
    // 读取图像
    image = cv::imread("../data/img.jpg", cv::IMREAD_ANYCOLOR);
    cv::Mat gray = cv::imread("../data/img.jpg", cv::IMREAD_GRAYSCALE);

    if (image.empty())
    {
        std::cout << "Failed to read image." << std::endl;
        return -1;
    }

    // 显示原始图像
    cv::imshow("Original Image", image);

    // 写入图像
    imwrite("../data/img_gray.jpg", gray);

    // 获取像素值
    int myRow = image.rows - 1;
    int myCol = image.cols - 1;
    auto pixel = image.at<cv::Vec3b>(myRow, myCol);
    std::cout << "Pixel value (B,G,R): (" << (int)pixel[0] << "," << (int)pixel[1] << "," << (int)pixel[2] << ")" << std::endl;

    // 阈值处理窗口
//    cv::namedWindow("Thresholded Image");
    cv::createTrackbar("Threshold", "Thresholded Image", &thresholdValue, maxValue, onTrackbar);
    onTrackbar(thresholdValue, nullptr);

    // 二值化阈值分割
    cv::Mat binaryImage;
    cv::threshold(gray, binaryImage, 128, 255, cv::THRESH_BINARY);
//    cv::namedWindow("Binary Image", cv::WINDOW_NORMAL);
//    cv::imshow("Binary Image", binaryImage);

    // 滤波示例
    cv::Mat mean_filter, gauss_filter, median_filter;
    cv::blur(image,  mean_filter, cv::Size(5, 5));
    cv::GaussianBlur(image, gauss_filter, cv::Size(5, 5), 0);
    cv::medianBlur(image, median_filter, 5);
//    cv::imshow("Mean Filter", mean_filter);
//    cv::imshow("Gaussian Filter", gauss_filter);
//    cv::imshow("Median Filter", median_filter);

    // 平移变换
    cv::Mat translatedImage;
    cv::Mat translationMatrix = (cv::Mat_<float>(2, 3) << 1, 0, 50, 0, 1, 50); // 平移50个像素
    cv::warpAffine(image, translatedImage, translationMatrix, image.size());
    // 旋转变换
    cv::Mat rotatedImage;
    cv::Point2f center(image.cols / 2.0, image.rows / 2.0);
    double angle = 45.0;
    cv::Mat rotationMatrix = cv::getRotationMatrix2D(center, angle, 1.0);
    cv::warpAffine(image, rotatedImage, rotationMatrix, image.size());
//    cv::namedWindow("Translated Image", cv::WINDOW_NORMAL);
//    cv::namedWindow("Rotated Image", cv::WINDOW_NORMAL);
//    cv::imshow("Translated Image", translatedImage);
//    cv::imshow("Rotated Image", rotatedImage);

    // 等待按键退出
    cv::waitKey(0);

    // 销毁窗口
    cv::destroyAllWindows();

    return 0;
}