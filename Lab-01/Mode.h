#pragma once

#include "Menu.h"
#include <string>
#include <SFML/Graphics.hpp>

enum class State
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

class Mode
{
public:
    Mode() = delete;
    ~Mode() = delete;

    static void updateState(State newState);
    static void updateMousePosition(const sf::Vector2f& newMousePosition)
    { mousePosition = newMousePosition; }
    static void updateColor() {}

    static bool saveRequested();
    static bool loadRequested();

private:
    static void revertState(State beforeRevert);

public:
    static State current;
    static std::wstring m_currentStateLetter;
    static sf::Vector2f mousePosition;
    static sf::Color colorForeground;
    static sf::Color colorBackground;

private:
    static State previous;
    static bool save;
    static bool load;
};
