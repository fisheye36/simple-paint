#pragma once

#include <iostream>
#include <string>

#include <SFML/System.hpp>

class Logger
{
public:
    Logger() = delete;
    ~Logger() = delete;

    template <typename T>
    static void log(std::ostream& os, const std::string& str, const T& data)
    { os << str << ": " << data << std::endl; }
    static void log(std::ostream& os, const std::string& str)
    { os << str << std::endl; }
    static void logPosition(std::ostream& os, const std::string& name,
                            const sf::Vector2f& vec)
    { os << name << " x = " << vec.x << ", " << name << " y = " << vec.y << std::endl; }
};
