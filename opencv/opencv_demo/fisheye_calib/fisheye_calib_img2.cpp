#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    // 读入鱼眼图像
    Mat img = imread("fisheye_image.jpg");
    
    // 设置鱼眼相机参数
    Mat K = Mat::eye(3,3,CV_64F);
    Mat D = Mat::zeros(4,1,CV_64F);
    int fisheye_width = img.cols;
    int fisheye_height = img.rows;
    
    // 执行鱼眼标定
    vector<vector<Point2f>> imagePoints;
    vector<Point3f> objectPoints;
    Size boardSize(8,6); // 棋盘格尺寸
    float squareSize = 20; // 棋盘格方块大小
    vector<int> point_counts;
    int count=0;
    for(int i=0;i<boardSize.height;i++)
    {
        for(int j=0;j<boardSize.width;j++)
        {
            objectPoints.push_back(Point3f(i*squareSize,j*squareSize,0));
        }
    }
    while(count <= 10) // 拍摄10张图片进行标定
    {
        // 获取当前帧
        Mat frame;
        //TODO: 使用摄像头获取实时图像
        
        // 检测棋盘格角点
        vector<Point2f> corners;
        bool found = findChessboardCorners(frame, boardSize, corners,
                        CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE | CALIB_CB_FAST_CHECK);
        if(found)
        {
            imagePoints.push_back(corners);
            point_counts.push_back(boardSize.width*boardSize.height);
            drawChessboardCorners(frame, boardSize, Mat(corners), found);
            count++;
        }
        
        // 显示当前帧
        imshow("Fisheye Calibration", frame);
        waitKey(1);
    }
    
    // 进行标定
    vector<Mat> rvecs, tvecs;
    int flags = fisheye::CALIB_RECOMPUTE_EXTRINSIC + fisheye::CALIB_CHECK_COND +
                fisheye::CALIB_FIX_SKEW + fisheye::CALIB_FIX_K4 + fisheye::CALIB_FIX_K5;
    double rms = fisheye::calibrate(imagePoints, objectPoints, Size(fisheye_width,fisheye_height),
                                    K, D, rvecs, tvecs, flags);
    
    cout << "RMS error: " << rms << endl;
    cout << "K matrix: \n" << K << endl;
    cout << "D matrix: \n" << D << endl;
    
    return 0;
}
