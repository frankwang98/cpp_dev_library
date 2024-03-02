#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

vector<Point3f> calcBoardCornerPositions(Size board_size, float square_size);

int main()
{
    // 加载图片
    Mat image = imread("./data/test-fisheye.png");

    // 定义棋盘格参数
    Size pattern_size(9, 6);
    float square_size = 30.0f;

    // 找到角点
    vector<Point2f> corners;
    bool found = findChessboardCorners(image, pattern_size, corners);

    if (found)
    {
        // 提取亚像素角点
        cornerSubPix(image, corners, Size(11, 11), Size(-1, -1),
            TermCriteria(TermCriteria::EPS + TermCriteria::MAX_ITER, 30, 0.1));

        // 绘制角点
        drawChessboardCorners(image, pattern_size, corners, found);

        // 计算相机矩阵和畸变系数
        Mat camera_matrix, dist_coeffs;
        vector<Vec3f> rvecs, tvecs;
        calibrateCamera(vector<vector<Point3f>>(1, calcBoardCornerPositions(pattern_size, square_size)),
            vector<vector<Point2f>>(1, corners), image.size(), camera_matrix, dist_coeffs, rvecs, tvecs);

        // 保存结果
        FileStorage fs("calibration.yaml", FileStorage::WRITE);
        fs << "camera_matrix" << camera_matrix;
        fs << "dist_coeffs" << dist_coeffs;
        fs.release();
    }

    // 显示结果
    imshow("Image", image);
    waitKey();

    return 0;
}

vector<Point3f> calcBoardCornerPositions(Size board_size, float square_size)
{
    vector<Point3f> corners;

    for (int i = 0; i < board_size.height; ++i)
    {
        for (int j = 0; j < board_size.width; ++j)
        {
            corners.push_back(Point3f(j * square_size, i * square_size, 0));
        }
    }

    return corners;
}
