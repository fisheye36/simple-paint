#pragma once

#include "Config.h"

#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

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

    static void initializeTexture(sf::Uint8 *colorsPixels);
    static void updateState(State newState);
    static void updateMousePosition(const sf::Vector2f& newMousePosition)
    { mousePosition = newMousePosition; }
    static void updateColor();

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
    static const unsigned minX { Layout::ColorsPosX };
    static const unsigned maxX { Layout::ColorsPosX + Layout::ColorsWidth };
    static const unsigned minY { Layout::ColorsPosY };
    static const unsigned maxY { Layout::ColorsPosY + Layout::ColorsHeight };

    static sf::Image m_image;
    static State m_previous;
    static bool m_save;
    static bool m_load;
};
