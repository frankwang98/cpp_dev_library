#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

Mat MoveCheck(Mat &frontFrame, Mat &afterFrame)
{
    Mat frontGray,afterGray;
    Mat resFrame = afterFrame.clone();

    cvtColor(frontFrame, frontGray, COLOR_BGR2GRAY);
    cvtColor(afterFrame, afterGray, COLOR_BGR2GRAY);

    Mat diff;
    absdiff(frontGray, afterGray, diff);
    //imshow("diff",diff);

    threshold(diff, diff, 25, 255, THRESH_BINARY);
    //imshow("threshold",diff);

    Mat element = cv::getStructuringElement(MORPH_RECT, Size(4, 4));
    erode(diff, diff, element);
    //imshow("erode",diff);

    Mat element2=cv::getStructuringElement(MORPH_RECT, Size(30, 30));
    dilate(diff, diff, element2);
    //imshow("dilate",diff);

    vector<vector<Point>>contours;
    findContours(diff, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));

    vector<vector<Point>>contours_poly(contours.size());
    vector<Rect>boundRect(contours.size());

    int x,y,w,h;
    int num=contours.size();
    for(int i = 0;i < num;i++)
    {
        approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
        boundRect[i]=boundingRect(Mat(contours_poly[i]));
        x=boundRect[i].x;
        y=boundRect[i].y;
        w=boundRect[i].width;
        h=boundRect[i].height;

        rectangle(resFrame, Point(x, y), Point(x+w, y+h), Scalar(255, 0, 0), 2);//Scalar颜色
    }
    return resFrame;
}
int main(int argc, char *argv[])
{
    Mat frame;
    Mat temp;
    Mat res;
    int count = 0;
    VideoCapture cap("../data/dashcam1.mp4");

    while(cap.read(frame))
    {
        count++;
        if(count == 1)
        {
            res = MoveCheck(frame, frame);
        }
        else
        {
            res = MoveCheck(temp, frame);
        }
        temp = frame.clone();
        imshow("frame", frame);
        imshow("res", res);
        waitKey(25);
    }

    return 0;
}