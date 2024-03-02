// logutils.hpp

#ifndef LOG_UTILS_HPP
#define LOG_UTILS_HPP

#include <iostream>
#include <fstream>
#include <ctime>

// 定义颜色转义序列（刷色）
// Usage: std::cout << COLOR_RED << "红色文本" << COLOR_RESET << std::endl;
#define COLOR_RED     "\033[31m" // 红 错误警告
#define COLOR_GREEN   "\033[32m" // 绿 
#define COLOR_YELLOW  "\033[33m" // 黄 后台消息
#define COLOR_BLUE    "\033[34m" // 蓝 车端消息
#define COLOR_MAGENTA "\033[35m" // 洋红
#define COLOR_CYAN    "\033[36m" // 青
#define COLOR_RESET   "\033[0m"
#define COLOR_BOLD    "\033[1m"  //加粗/高亮
#define COLOR_UDLINE  "\033[4m"  // 下划线
#define COLOR_REVERSE "\033[7m"  // 反转前景色(30-37)和背景色(40-47)

/* 日志级别 */ 
enum class LogLevel {
    INFO,
    WARNING,
    ERROR
};

class LogUtils {
public:
    /* 拷贝构造函数 */
    LogUtils(const std::string& filename) : logFile(filename) {
        if (!logFile.is_open()) {
            throw std::runtime_error("Failed to open log file");
        }
    }

    /**
     * @brief 日志输出
    */
    void Log(LogLevel level, const std::string& message) {
        std::time_t currentTime = std::time(nullptr);
        std::string logLevelStr;

        switch (level) {
            case LogLevel::INFO:
                logLevelStr = "INFO";
                break;
            case LogLevel::WARNING:
                logLevelStr = "WARNING";
                break;
            case LogLevel::ERROR:
                logLevelStr = "ERROR";
                break;
        }

        std::string logMessage = "[" + logLevelStr + "] " + GetFormattedTime(currentTime) + " - " + message + "\n";
        logFile << logMessage;
        logFile.flush();
    }

private:
    std::ofstream logFile;

    /**
     * @brief 格式化文本
    */
    std::string GetFormattedTime(std::time_t time) {
        char buffer[20];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&time));
        return std::string(buffer);
    }
};

#endif