// timeutils.hpp
#ifndef TIME_UTILS_HPP
#define TIME_UTILS_HPP

#include <chrono>
#include <ctime>
#include <string>
#include <type_traits>
#include <functional>
#include <unistd.h>
#include <cstring>
#include <sys/wait.h>
#include <errno.h>
#include <assert.h>
#include <uuid/uuid.h>

class TimeUtils {
public:
    long getTimeMillis();
    long long getTimeNanos();
    std::string getLocalTime();
    std::string getUtcTime();

    /**
     * @brief 将当前时间转为字符串
    */
    template<typename T>
    static typename std::enable_if<std::is_same<std::string, T>::value, std::string>::type convert(time_t t)
    {
        return time2string(t);
    }

    /**
     * @brief 将字符串转为当前时间
    */
    template<typename T>
    static typename std::enable_if<std::is_same<time_t, T>::value, time_t>::type convert(const std::string& timeStr)
    {
        return string2time(timeStr);
    }

    /**
     * @brief 获取当前时间
    */
    static std::string currentTime()
    {
        return time2string(time(nullptr));
    }

private:
    /**
     * @brief 内部调用
    */
    static std::string time2string(time_t t)
    {
        struct tm* tmNow = localtime(&t);
        char timeStr[sizeof("yyyy-mm-dd hh:mm:ss")] = {'\0'};
        std::strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", tmNow);
        return timeStr;
    }

    /**
     * @brief 内部调用
    */
    static time_t string2time(const std::string& timeStr)
    {
        struct tm stTm;
        sscanf(timeStr.c_str(), "%d-%d-%d %d:%d:%d",
               &(stTm.tm_year),
               &(stTm.tm_mon),
               &(stTm.tm_mday),
               &(stTm.tm_hour),
               &(stTm.tm_min),
               &(stTm.tm_sec));

        stTm.tm_year -= 1900;
        stTm.tm_mon--;
        stTm.tm_isdst = -1;

        return mktime(&stTm);
    }
};

class Timer
{
public:
    Timer() : m_begin(std::chrono::high_resolution_clock::now()) {}

    void reset()
    {
        m_begin = std::chrono::high_resolution_clock::now();
    }

    // 默认输出毫秒.
    template<typename Duration = std::chrono::milliseconds>
    long long elapsed() const
    {
        return std::chrono::duration_cast<Duration>(std::chrono::high_resolution_clock::now() - m_begin).count();
    }

    // 微秒.
    long long elapsedMicroseconds() const
    {
        return elapsed<std::chrono::microseconds>();
    }

    // 纳秒.
    long long elapsedNanoSeconds() const
    {
        return elapsed<std::chrono::nanoseconds>();
    }

    // 秒.
    long long elapsedSeconds() const
    {
        return elapsed<std::chrono::seconds>();
    }

    // 分.
    long long elapsedMinutes() const
    {
        return elapsed<std::chrono::minutes>();
    }

    // 时.
    long long elapsedHours() const
    {
        return elapsed<std::chrono::hours>();
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_begin;
};

std::string getUuidStr();

#endif