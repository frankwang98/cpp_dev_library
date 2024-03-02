// timeutils.cc

#include "timeutils.hpp"

/**
 * @brief 获取系统毫秒级时间
*/
long TimeUtils::getTimeMillis()
{
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto duration = currentTime.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}

/**
 * @brief 获取系统纳秒级时间
*/
long long TimeUtils::getTimeNanos()
{
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto duration = currentTime.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
}

/**
 * @brief 获取本地时间（根据UTC加上时区算出来）
*/
std::string TimeUtils::getLocalTime()
{
    std::time_t localTime = std::time(nullptr);
    std::string localTimeStr = std::asctime(std::localtime(&localTime));
    localTimeStr.erase(localTimeStr.length() - 1);
    return localTimeStr;
}

/**
 * @brief 获取UTC时间（全球标准参考时间）
*/
std::string TimeUtils::getUtcTime()
{
    std::time_t utcTime = std::time(nullptr);
    std::string utcTimeStr = std::asctime(std::gmtime(&utcTime));
    utcTimeStr.erase(utcTimeStr.length() - 1);
    return utcTimeStr;
}

std::string getUuidStr()
{
    uuid_t uuid;
    char uuidStr[37];
    uuid_generate(uuid);
    uuid_unparse_lower(uuid, uuidStr);
    return uuidStr;
}