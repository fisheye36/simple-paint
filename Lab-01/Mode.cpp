#include "Mode.h"
#include <string>
#include <SFML/Graphics.hpp>

Mode::State Mode::current = Mode::None;
sf::Vector2f Mode::mousePosition;
sf::Color Mode::colorForeground = sf::Color::Red;
sf::Color Mode::colorBackground = sf::Color::Yellow;
std::wstring Mode::m_currentStateLetter = L"";

void Mode::updateState(Mode::State newState)
{
    current = newState;
    switch (current)
    {
        case Mode::None:
            m_currentStateLetter = L"";
            break;
        case Mode::ColorForeground:
            m_currentStateLetter = L"F";
            break;
        case Mode::ColorBackground:
            m_currentStateLetter = L"B";
            break;
        case Mode::Line:
            m_currentStateLetter = L"L";
            break;
        case Mode::Rectangle:
            m_currentStateLetter = L"R";
            break;
        case Mode::FilledRectangle:
            m_currentStateLetter = L"A";
            break;
        case Mode::Circle:
            m_currentStateLetter = L"C";
            break;
        case Mode::WriteFile:
            m_currentStateLetter = L"W";
            break;
        case Mode::OpenFile:
            m_currentStateLetter = L"O";
            break;
    }
}
