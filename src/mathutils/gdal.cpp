#include <iostream>
#include <gdal/gdal.h>
#include <gdal/gdal_priv.h>
#include <gdal/cpl_conv.h>

// gdal能处理坐标，但这个不完整

int main()
{
    GDALAllRegister();

    const char* latlon_proj_str = "+proj=longlat +ellps=WGS84 +datum=WGS84 +no_defs";
    const char* utm_proj_str = "+proj=utm +zone=49 +ellps=WGS84 +datum=WGS84 +units=m +no_defs";

    OGRSpatialReference src_proj;
    OGRSpatialReference dst_proj;
    // src_proj.SetFromUserInput(latlon_proj_str);
    // dst_proj.SetFromUserInput(utm_proj_str);

    src_proj.SetFromUserInput(utm_proj_str);
    dst_proj.SetFromUserInput(latlon_proj_str);

    OGRCoordinateTransformation* transform = OGRCreateCoordinateTransformation(&src_proj, &dst_proj);

    /* latlon */
    // double src_lon = 120.12345;
    // double src_lat = 30.98765;

    /* xy */
    double utm_x = 668361.959;
    double utm_y = 4377276.488;

    // double dst_x = src_lon;
    // double dst_y = src_lat;

    double dst_lat = utm_x;
    double dst_lon = utm_y;

    if (transform) {
        // std::cout << "UTM X: " << dst_x << std::endl;
        // std::cout << "UTM Y: " << dst_y << std::endl;
        std::cout << "Latitude: " << dst_lat << std::endl;
        std::cout << "Longitude: " << dst_lon << std::endl;
        OCTDestroyCoordinateTransformation(transform);
    }

    GDALDestroy();

    return 0;
}