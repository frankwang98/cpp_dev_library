#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
// %YAML:1.0
// ---
// fps: 5
// Result: !!opencv-matrix
//    rows: 2
//    cols: 3
//    dt: f
//    data: [ 8., 3., 3., 3., 8., 3. ]

int main(int argc, char** argv) {
    // 创建文件写入
    FileStorage fs("test.yml", FileStorage::WRITE);
    // 保存int fps
    int fps = 5;
    fs << "fps" << fps;
    // 创建一些mat
    Mat m1 = Mat::eye(2, 3, CV_32F);
    Mat m2 = Mat::ones(3, 2, CV_32F);
    Mat result = (m1 + 1).mul(m1 + 3);
    // 写入结果
    fs << "Result" << result;
    // 发布文件
    fs.release();

    FileStorage fs2("test.yml", FileStorage::READ);

    Mat r;
    fs2["Result"] >> r;
    std::cout << r << std::endl;

    fs2.release();

    return 0;
}
