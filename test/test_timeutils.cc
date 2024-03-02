#include "../src/timeutils/timeutils.hpp"
#include <iostream>
#include <unistd.h>

int main(int argc, char** argv)
{
    std::string uuidStr = getUuidStr();
    std::cout << "getUuidStr: " << uuidStr << std::endl;

    TimeUtils t;
    std::cout << "getTimeMillis: " << t.getTimeMillis() << std::endl;

    std::cout << "getTimeNanos: " << t.getTimeNanos() << std::endl;

    std::cout << "getLocalTime: " << t.getLocalTime() << std::endl;

    std::cout << "getUtcTime: " << t.getUtcTime() << std::endl;

    std::string timeStr = TimeUtils::convert<std::string>(time(nullptr));
    std::cout << timeStr << std::endl;
    std::cout << TimeUtils::convert<time_t>(timeStr) << std::endl;
    std::cout << TimeUtils::currentTime() << std::endl;

    /* 定时器 */
    Timer timer;

    sleep(2);

    std::cout << "milliseconds: " << timer.elapsed() << std::endl;
    std::cout << "microseconds: " << timer.elapsedMicroseconds() << std::endl;
    std::cout << "nanoseconds: " << timer.elapsedNanoSeconds() << std::endl;
    std::cout << "seconds: " << timer.elapsedSeconds() << std::endl;
    std::cout << "minutes: " << timer.elapsedMinutes() << std::endl;
    std::cout << "hours: " << timer.elapsedHours() << std::endl;


    return 0;
}