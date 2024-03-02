#include "../src/stringutils/stringutils.hpp"
#include <iostream>

int main(int argc, char** argv)
{ 
    char str1[] = "Hello";
    char str2[] = "World";
    char str3[] = "";

    std::cout << "strlen: " << strlen(str1) << std::endl
              << "strcat: " << strcat(str1, str2) << std::endl
              << "strcpy: " << strcpy(str3, str1) << std::endl
              << "strcmp: " << strcmp(str1, str2) << std::endl
              << "----- end..." << std::endl;

    std::string str = "Hello world";
    std::cout << StringUtils::trimLeft(str, "Hello") << std::endl;
    std::cout << StringUtils::trimRight(str, "world") << std::endl;
    str = "  nihao ";
    std::cout << StringUtils::trim(str) << std::endl;
    std::cout << StringUtils::toUpper(str) << std::endl;
    std::cout << StringUtils::toLower(StringUtils::toUpper(str)) << std::endl;
    str = "Hello world";
    std::cout << StringUtils::startsWith(str, "Hello") << std::endl;
    std::cout << StringUtils::endsWith(str, "a") << std::endl;
    std::vector<std::string> result = StringUtils::split(str, " ");
    for (auto& iter : result)
    {
        std::cout << iter << std::endl;
    }

    return 0;
}