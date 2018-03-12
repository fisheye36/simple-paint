#pragma once

#include "Menu.h"
#include <string>
#include <SFML/Graphics.hpp>

class Mode
{
public:
    enum State
    {
        None,
        ColorForeground,
        ColorBackground,
        Line,
        Rectangle,
        FilledRectangle,
        Circle,
        WriteFile,
        OpenFile
    };

    Mode() = delete;
    ~Mode() = delete;

    static void updateState(Mode::State newState);
    static void updateMousePosition(const sf::Vector2f& newMousePosition)
    { mousePosition = newMousePosition; }
    static void updateColor() {}

public:
    static State current;
    static std::wstring m_currentStateLetter;
    static sf::Vector2f mousePosition;
    static sf::Color colorForeground;
    static sf::Color colorBackground;
};
