#include <stdio.h>
#include "minio_client.hpp"
#include "ilogger.hpp"

int main() {
    // 对于自己搭建的服务器，http访问配置
    const char* server     = "http://10.10.8.8:9000";
    const char* access_key = "root";
    const char* secret_key = "123456wicri";
    // 对于官方给的测试案例地址，https访问
    // const char* server     = "https://play.min.io:9000";
    // const char* access_key = "Q3AM3UQ867SPQQA43P2F";
    // const char* secret_key = "zuf+tfteSlswRu7BJ86wekitnifILbZam1KYY3TG";
    MinioClient minio(server, access_key, secret_key);

    /////////////////////////////////////////////////////////////////
    INFO("===========================test get buckets=========================");
    auto buckets = minio.get_bucket_list();
    INFO("total is %d", buckets.size());

    for(int i = 0; i < buckets.size(); ++i)
        INFO("bucket[%d] = %s", i, buckets[i].c_str());

    /////////////////////////////////////////////////////////////////
    INFO("===========================test upload=========================");
    const char* local_file       = "echo.txt";
    const char* bucket_name      = buckets[1].c_str();
    if(minio.upload_file(iLogger::format("/%s/echo.txt", bucket_name), local_file)){
        INFO("upload %s success, size: %d bytes", local_file, iLogger::file_size(local_file));
    }

    INFO("===========================test upload data=========================");
    auto filedata = iLogger::load_text_file("test.png");
    if(minio.upload_filedata(iLogger::format("/%s/test.png", bucket_name), filedata)){
        INFO("upload filedata success, filedata.size = %d", filedata.size());
    }

    /////////////////////////////////////////////////////////////////
    // INFO("===========================test download=========================");
    // auto data = minio.get_file(iLogger::format("/%s/echo.txt", bucket_name));
    // INFO("download echo.txt, content is[%d bytes]: %s", data.size(), data.c_str());

    /////////////////////////////////////////////////////////////////
    // INFO("===========================test download=========================");
    // auto data2 = minio.get_file(iLogger::format("/%s/echo-filedata.txt", bucket_name));
    // INFO("download echo-filedata.txt, content is[%d bytes]: %s", data2.size(), data2.c_str());
    return 0;
}