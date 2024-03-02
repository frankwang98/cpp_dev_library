#include <iostream>
#include "CoorConv.h"

// UTM 与 WGS84 坐标转换，不太准

int main() {
    double x = 464101.487;
    double y = 4378816.449;

    WGS84Corr t;
    // 长沙的zone为49  长沙的中央子午线经度为111，推出zone为49
    UTMXYToLatLon(x, y, 49, false, t);
    // double lat = RadToDeg(t.lat); // 注意弧度转角度！！！
    // double log = RadToDeg(t.log);

    std::cout << "UTM2WGS84\nlat: " << RadToDeg(t.lat) << " log: " << RadToDeg(t.log) << std::endl;


    double lat = 35.21265;
    double log = 117.02101;

    UTMCoor test;
    LatLonToUTMXY(DegToRad(lat), DegToRad(log), 50, test);
    std::cout << "WGS842UTM\nx: " << test.x << " y: " << test.y << std::endl;

    return 0;
}
