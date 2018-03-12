#pragma once

#include <iostream>
#include <string>

class Logger
{
public:
    Logger() = delete;
    ~Logger() = delete;

    template <typename T>
    static void log(std::ostream& os, const std::string& str, const T& data)
    { os << str << ": " << data << std::endl; }
    static void logPosition(std::ostream& os, const std::string& name, int x, int y)
    { os << name << " x = " << x << ", " << name << " y = " << y << std::endl; }
};