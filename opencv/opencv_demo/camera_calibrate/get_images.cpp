#include "opencv2/opencv.hpp"
#include <string>
#include <iostream>
 
using namespace cv;
using namespace std;
 
int main(){
    Mat frame;
    string imgname;
    int f = 1;
 
    // 打开相机
    VideoCapture inputVideo(0);
    if (!inputVideo.isOpened()){
        cout << "Could not open the input video " << endl;
        return -1;
    }
    else{
        cout << "video is opened!" << endl;
    }

    // 读取并保存图像
    while (1){
        inputVideo >> frame;
        if (frame.empty()) continue;
        imshow("Camera", frame);
        char key = waitKey(1);
        if (key == 27) break;
        if (key == 's' || key == 'S'){
            imgname = to_string(f++) + ".jpg";  // 保存name
            imwrite(imgname, frame);
        }
    }
    cout << "Finished writing" << endl;
    return 0;
}