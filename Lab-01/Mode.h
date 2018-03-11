#pragma once

#include "Menu.h"
#include <string>
#include <SFML/Graphics.hpp>

class Mode
{
    friend void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const;

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
    static sf::Vector2f mousePosition;
    static sf::Color colorForeground;
    static sf::Color colorBackground;

private:
    static std::wstring m_currentStateLetter;
};
