#include <iostream>
#include "csv.h"

/*
从多个csv文件读取数据
*/

int main() {
    std::vector<std::string> sheets = {"scene13_vcar1.csv", "scene13_vcar2.csv"};

    for (const std::string& sheet : sheets) {
        std::cout << "Reading sheet: " << sheet << std::endl;

        io::CSVReader<9> in(sheet);  // 创建CSVReader对象，指定CSV文件名和列数

        // 设置CSV列名
        in.read_header(io::ignore_extra_column, "x", "y", "z", "heading_angle", "speed", "curvature", "longitude", "latitude", "altitude");

        std::string x, y, z, heading_angle, speed, curvature, longitude, latitude, altitude, attribute;  // 定义变量来存储CSV列数据

        // 逐行解析CSV文件并访问每一列的数据
        while (in.read_row(x, y, z, heading_angle, speed, curvature, longitude, latitude, altitude)) {
            // 在此处对解析的数据进行处理
            std::cout << "x: " << x << ", y: " << y << ", z: " << z << ", heading_angle: " << heading_angle
                    << ", speed: " << speed << ", curvature: " << curvature << ", longitude: " << longitude
                    << ", latitude: " << latitude << ", altitude: " << altitude
                    << std::endl;
        }

        std::cout << "Sheet " << sheet << " read complete." << std::endl;
    }

    return 0;
}
