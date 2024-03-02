#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
    // 解析命令行参数没太大用

    // 读取设备实时图像/视频文件
    VideoCapture cap(0);
    if (!cap.isOpened())
    {
        cout << "Cannot open video" << endl;
        return -1;
    }

    namedWindow("video", 1);
    moveWindow("video", 10, 10);
    resizeWindow("video", 512, 512);
    while (1)
    {
        Mat frame;
        cap >> frame;
        if (frame.empty())
            break;
        imshow("video", frame);
//        displayOverlay("video", "Hello, World!", 1000); // with qt
//        displayStatusBar("video", "Status bar 5secs", 5000);
        if (waitKey(30) >= 0)
            break;
    }
    cap.release();
    destroyAllWindows();

    return 0;
}
