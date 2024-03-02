// stringutils.hpp

#ifndef STRING_UTILS_HPP
#define STRING_UTILS_HPP

#include <cstring>
#include <cctype>
#include <string>
#include <vector>
#include <algorithm>

/**
 * @brief 字符串工具类
 * @test 类的静态成员可以在不实例化对象的情况下使用。静态成员属于类本身，而不是类的实例
*/
class StringUtils {
public:
    static std::string trimLeft(const std::string& str, const std::string& token = " ")
    {
        std::string t = str;
        t.erase(0, t.find_first_not_of(token));
        return t;
    }

    static std::string trimRight(const std::string& str, const std::string& token = " ")
    {
        std::string t = str;
        t.erase(t.find_last_not_of(token) + 1);
        return t;
    }

    static std::string trim(const std::string& str, const std::string& token = " ")
    {
        std::string t = str;
        t.erase(0, t.find_first_not_of(token));
        t.erase(t.find_last_not_of(token) + 1);
        return t;
    }

    static std::string toLower(const std::string& str)
    {
        std::string t = str;
        std::transform(t.begin(), t.end(), t.begin(), ::tolower);
        return t;
    }

    static std::string toUpper(const std::string& str)
    {
        std::string t = str;
        std::transform(t.begin(), t.end(), t.begin(), ::toupper);
        return t;
    }

    static bool	startsWith(const std::string& str, const std::string& substr)
    {
        return str.find(substr) == 0;
    }

    static bool endsWith(const std::string& str, const std::string& substr)
    {
        return str.rfind(substr) == (str.length() - substr.length());
    }

    static bool equalsIgnoreCase(const std::string& str1, const std::string& str2) 
    {
        return toLower(str1) == toLower(str2);
    }

    static std::vector<std::string> split(const std::string& str, const std::string& delimiter)
    {
        char* save = nullptr;
#ifdef _WIN32
        char* token = strtok_s(const_cast<char*>(str.c_str()), delimiter.c_str(), &save);
#else
        char* token = strtok_r(const_cast<char*>(str.c_str()), delimiter.c_str(), &save);
#endif
        std::vector<std::string> result;
        while (token != nullptr)
        {
            result.emplace_back(token);
#ifdef _WIN32
            token = strtok_s(nullptr, delimiter.c_str(), &save);
#else
            token = strtok_r(nullptr, delimiter.c_str(), &save);
#endif
        }
        return result;
    }

    static bool contains(const std::string& str, const std::string& token)
    {
        return str.find(token) == std::string::npos ? false : true;
    }

};

#endif