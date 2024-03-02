#include "../src/logutils/logutils.hpp"
#include <iostream>

int main(int argc, char** argv)
{
    LogUtils logutils("log.txt");

    logutils.Log(LogLevel::INFO, "This is an information message.");
    logutils.Log(LogLevel::WARNING, "This is a warning message.");
    logutils.Log(LogLevel::ERROR, "This is an error message.");

    return 0;
}