#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

// 函数声明
int processImgR(Mat);
int processImgG(Mat);
bool isIntersected(Rect, Rect);
void detect(Mat& frame);

// 全局变量
bool isFirstDetectedR = true;
bool isFirstDetectedG = true;
Rect* lastTrackBoxR;
Rect* lastTrackBoxG;
int lastTrackNumR;
int lastTrackNumG;

/*
1.轮廓检测、计数
2.red、green和light_out三种状态
3.提取颜色空间，红和绿
4.膨胀和腐蚀，去除噪点
5.判断3种状态
*/

int main()
{
    int redCount = 0;
    int greenCount = 0;

    Mat frame;
    Mat img;
    Mat imgYCrCb;
    Mat imgGreen;
    Mat imgRed;

    // 亮度参数
    double a = 0.3;
    double b = (1 - a) * 125;

    VideoCapture capture("../data/dashcam2.mp4");//导入视频的路径/摄像头 0
    if (!capture.isOpened())
    {
        cout << "Start device failed!\n" << endl;//启动设备失败！
        return -1;
    }

    // 帧处理
    while (1)
    {
        capture >> frame;
        //调整亮度
        frame.convertTo(img, img.type(), a, b);

        //转换为YCrCb颜色空间
        cvtColor(img, imgYCrCb, CV_BGR2YCrCb);

        imgRed.create(imgYCrCb.rows, imgYCrCb.cols, CV_8UC1);
        imgGreen.create(imgYCrCb.rows, imgYCrCb.cols, CV_8UC1);

        //分解YCrCb的三个成分
        vector<Mat> planes;
        split(imgYCrCb, planes);
        // 遍历以根据Cr分量拆分红色和绿色
        MatIterator_<uchar> it_Cr = planes[1].begin<uchar>(),
                it_Cr_end = planes[1].end<uchar>();
        MatIterator_<uchar> it_Red = imgRed.begin<uchar>();
        MatIterator_<uchar> it_Green = imgGreen.begin<uchar>();

        for (; it_Cr != it_Cr_end; ++it_Cr, ++it_Red, ++it_Green)
        {
            // RED, 145<Cr<470 红色
            if (*it_Cr > 145 && *it_Cr < 470)
                *it_Red = 255;
            else
                *it_Red = 0;

            // GREEN 95<Cr<110 绿色
            if (*it_Cr > 95 && *it_Cr < 110)
                *it_Green = 255;
            else
                *it_Green = 0;
        }

        //膨胀和腐蚀
        dilate(imgRed, imgRed, Mat(15, 15, CV_8UC1), Point(-1, -1));
        erode(imgRed, imgRed, Mat(1, 1, CV_8UC1), Point(-1, -1));
        dilate(imgGreen, imgGreen, Mat(15, 15, CV_8UC1), Point(-1, -1));
        erode(imgGreen, imgGreen, Mat(1, 1, CV_8UC1), Point(-1, -1));

        redCount = processImgR(imgRed);
        greenCount = processImgG(imgGreen);
        cout << "red:" << redCount << ";  " << "green:" << greenCount << endl;

        //条件判断
        if (redCount == 0 && greenCount == 0)
        {
            cv::putText(frame, "lights out", Point(40, 150), cv::FONT_HERSHEY_SIMPLEX, 2, cv::Scalar(255, 255, 255), 8, 8, 0);
        }
        else if (redCount > greenCount)
        {
            cv::putText(frame, "red light", Point(40, 150), cv::FONT_HERSHEY_SIMPLEX, 2, cv::Scalar(0, 0, 255), 8, 8, 0);
        }
        else {
            cv::putText(frame, "green light", Point(40, 150), cv::FONT_HERSHEY_SIMPLEX, 2, cv::Scalar(0, 255, 0), 8, 8, 0);
        }

        imshow("video", frame);
        //imshow("Red", imgRed);
        //imshow("Green", imgGreen);

        // Handle with the keyboard input
        if (waitKey(30) >= 0)
            break;
    }

    return 0;
}

//轮廓处理函数：红
int processImgR(Mat src)
{
    Mat tmp;

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    vector<Point> hull;

    CvPoint2D32f tempNode;
    CvMemStorage* storage = cvCreateMemStorage();
    CvSeq* pointSeq = cvCreateSeq(CV_32FC2, sizeof(CvSeq), sizeof(CvPoint2D32f), storage);

    Rect* trackBox;
    Rect* result;
    int resultNum = 0;

    int area = 0;
    src.copyTo(tmp);

    //提取轮廓
    findContours(tmp, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

    if (contours.size() > 0)
    {
        trackBox = new Rect[contours.size()];
        result = new Rect[contours.size()];

        //确定要跟踪的区域
        for (int i = 0; i < contours.size(); i++)
        {
            cvClearSeq(pointSeq);
            // 获取凸包的点集
            convexHull(Mat(contours[i]), hull, true);
            int hullcount = (int)hull.size();
            // 凸包的保存点
            for (int j = 0; j < hullcount - 1; j++)
            {
                tempNode.x = hull[j].x;
                tempNode.y = hull[j].y;
                cvSeqPush(pointSeq, &tempNode);
            }

            trackBox[i] = cvBoundingRect(pointSeq);
        }

        if (isFirstDetectedR)
        {
            lastTrackBoxR = new Rect[contours.size()];
            for (int i = 0; i < contours.size(); i++)
                lastTrackBoxR[i] = trackBox[i];
            lastTrackNumR = contours.size();
            isFirstDetectedR = false;
        }
        else
        {
            for (int i = 0; i < contours.size(); i++)
            {
                for (int j = 0; j < lastTrackNumR; j++)
                {
                    if (isIntersected(trackBox[i], lastTrackBoxR[j]))
                    {
                        result[resultNum] = trackBox[i];
                        break;
                    }
                }
                resultNum++;
            }
            delete[] lastTrackBoxR;
            lastTrackBoxR = new Rect[contours.size()];
            for (int i = 0; i < contours.size(); i++)
            {
                lastTrackBoxR[i] = trackBox[i];
            }
            lastTrackNumR = contours.size();
        }

        delete[] trackBox;
    }
    else
    {
        isFirstDetectedR = true;
        result = NULL;
    }
    cvReleaseMemStorage(&storage);

    if (result != NULL)
    {
        for (int i = 0; i < resultNum; i++)
        {
            area += result[i].area();
        }
    }
    delete[] result;

    return area;
}

//轮廓处理函数：绿
int processImgG(Mat src)
{
    Mat tmp;

    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    vector< Point > hull;

    CvPoint2D32f tempNode;
    CvMemStorage* storage = cvCreateMemStorage();
    CvSeq* pointSeq = cvCreateSeq(CV_32FC2, sizeof(CvSeq), sizeof(CvPoint2D32f), storage);

    Rect* trackBox;
    Rect* result;
    int resultNum = 0;

    int area = 0;

    src.copyTo(tmp);
    //提取轮廓
    findContours(tmp, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

    if (contours.size() > 0)
    {
        trackBox = new Rect[contours.size()];
        result = new Rect[contours.size()];

        // 确定要跟踪的区域
        for (int i = 0; i < contours.size(); i++)
        {
            cvClearSeq(pointSeq);
            // 获取凸包的点集
            convexHull(Mat(contours[i]), hull, true);
            int hullcount = (int)hull.size();
            // 保存凸包的点
            for (int j = 0; j < hullcount - 1; j++)
            {
                tempNode.x = hull[j].x;
                tempNode.y = hull[j].y;
                cvSeqPush(pointSeq, &tempNode);
            }

            trackBox[i] = cvBoundingRect(pointSeq);
        }

        if (isFirstDetectedG)
        {
            lastTrackBoxG = new Rect[contours.size()];
            for (int i = 0; i < contours.size(); i++)
                lastTrackBoxG[i] = trackBox[i];
            lastTrackNumG = contours.size();
            isFirstDetectedG = false;
        }
        else
        {
            for (int i = 0; i < contours.size(); i++)
            {
                for (int j = 0; j < lastTrackNumG; j++)
                {
                    if (isIntersected(trackBox[i], lastTrackBoxG[j]))
                    {
                        result[resultNum] = trackBox[i];
                        break;
                    }
                }
                resultNum++;
            }
            delete[] lastTrackBoxG;
            lastTrackBoxG = new Rect[contours.size()];
            for (int i = 0; i < contours.size(); i++)
            {
                lastTrackBoxG[i] = trackBox[i];
            }
            lastTrackNumG = contours.size();
        }

        delete[] trackBox;
    }
    else
    {
        isFirstDetectedG = true;
        result = NULL;
    }
    cvReleaseMemStorage(&storage);

    if (result != NULL)
    {
        for (int i = 0; i < resultNum; i++)
        {
            area += result[i].area();
        }
    }
    delete[] result;

    return area;
}

//确定两个矩形区域是否相交
bool isIntersected(Rect r1, Rect r2)
{
    int minX = max(r1.x, r2.x);
    int minY = max(r1.y, r2.y);
    int maxX = min(r1.x + r1.width, r2.x + r2.width);
    int maxY = min(r1.y + r1.height, r2.y + r2.height);

    //判断是否相交
    if (minX < maxX && minY < maxY)
        return true;
    else
        return false;
}