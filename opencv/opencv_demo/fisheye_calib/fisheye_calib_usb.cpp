#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

int main(int argc, char* argv[])
{
    // 打开相机并准备标定板的大小
    cv::VideoCapture cap(0);
    cv::Size boardSize(7, 5);

    // 创建向量来保存检测到的棋盘格角点坐标
    std::vector<std::vector<cv::Point2f>> imagePoints;
    std::vector<cv::Point3f> objectPoints;

    // 创建标定板点的坐标
    for (int i = 0; i < boardSize.height; ++i) {
        for (int j = 0; j < boardSize.width; ++j) {
            objectPoints.push_back(cv::Point3f(j, i, 0));
        }
    }

    // 检测标定板角点并保存检测到的角点坐标
    cv::Mat frame, gray;
    while (imagePoints.size() < 10) {
        cap >> frame;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        std::vector<cv::Point2f> corners;
        bool found = cv::findChessboardCorners(gray, boardSize, corners);

        if (found) {
            imagePoints.push_back(corners);
            cv::drawChessboardCorners(frame, boardSize, corners, found);
        }

        cv::imshow("Camera Calibration", frame);
        cv::waitKey(1);
    }

    // 进行相机标定
    cv::Mat cameraMatrix, distCoeffs;
    std::vector<cv::Mat> rvecs, tvecs;
    double rms = cv::calibrateCamera(
        { objectPoints } , imagePoints, frame.size(), cameraMatrix, distCoeffs, rvecs, tvecs
    );

    std::cout << "RMS error: " << rms << std::endl;
    std::cout << "Camera matrix: " << cameraMatrix << std::endl;
    std::cout << "Distortion coefficients: " << distCoeffs << std::endl;

    return 0;
}
