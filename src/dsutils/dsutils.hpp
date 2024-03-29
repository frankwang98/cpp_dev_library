// dsutils.hpp

#ifndef DSUTILS_HPP
#define DSUTILS_HPP

#include <string>
#include <array>
#include <vector>
#include <list>

// 模板特化定义
template<typename To, typename From>
struct converter {};

// 转换到int类型
template<typename From>
struct converter<int, From>
{
    static int convert(const std::string& from) { return std::atoi(from.c_str()); }
    static int convert(const char* from) { return std::atoi(from); }
};

// 转换到long类型
template<typename From>
struct converter<long, From>
{
    static long convert(const std::string& from) { return std::atol(from.c_str()); }
    static long convert(const char* from) { return std::atol(from); }
};

// 转换到long long类型
template<typename From>
struct converter<long long, From>
{
    static long long convert(const std::string& from) { return std::atoll(from.c_str()); }
    static long long convert(const char* from) { return std::atoll(from); }
};

// 转换到double类型
template<typename From>
struct converter<double, From>
{
    static double convert(const std::string& from) { return std::atof(from.c_str()); }
    static double convert(const char* from) { return std::atof(from); }
};

// 转换到float类型
template<typename From>
struct converter<float, From>
{
    static float convert(const std::string& from) { return static_cast<float>(std::atof(from.c_str())); }
    static float convert(const char* from) { return static_cast<float>(std::atof(from)); }
};

// 转换到bool类型
template<typename From>
struct converter<bool, From>
{
    static bool convert(int from) { return from > 0 ? true : false; }
    static bool convert(const std::string from) { return std::atoi(from.c_str()) > 0 ? true : false; }
};

// 转换到string类型
template<typename From>
struct converter<std::string, From>
{
    static std::string convert(int from) { return std::to_string(from); }
    static std::string convert(double from) { return std::to_string(from); }
    static std::string convert(float from) { return std::to_string(from); }
    static std::string convert(const std::string& from) { return from; }
    static std::string convert(const char* from) { return from; }
    static std::string convert(char from) { return std::string(&from); }
};

// 简化调用
template<typename To, typename From>
To lexical_cast(const From& from)
{
    return converter<To, From>::convert(from);
}

/* 部分示例 */
void array_ex();

void vector_ex();

void list_ex();

void string_ex();

#endif