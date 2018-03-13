#include "Config.h"
#include "Logger.h"
#include "Mode.h"

#include <chrono>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

State Mode::current { State::None };
std::wstring Mode::m_currentStateLetter { L"" };
sf::Vector2f Mode::mousePosition;

sf::Color Mode::colorForeground { sf::Color::White };
sf::Color Mode::colorBackground { sf::Color::Black };

sf::Image Mode::m_image;
State Mode::m_previous { State::None };
bool Mode::m_save { false };
bool Mode::m_load { false };

void Mode::initializeTexture(sf::Uint8 * colorsPixels)
{
    sf::Texture texture;
    texture.create(Layout::ColorsWidth, Layout::ColorsHeight);
    texture.update(colorsPixels);
    m_image = texture.copyToImage();
}

void Mode::updateState(State newState)
{
    m_previous = current;
    current = newState;
    Logger::log(std::cout, "previous state", static_cast<int>(m_previous));
    Logger::log(std::cout, "current state", static_cast<int>(current));
    std::thread thr;

    switch (current)
    {
        case State::None:
            m_currentStateLetter = L"";
            break;
        case State::ColorForeground:
            m_currentStateLetter = L"F";
            break;
        case State::ColorBackground:
            m_currentStateLetter = L"B";
            break;
        case State::Line:
            m_currentStateLetter = L"L";
            break;
        case State::Rectangle:
            m_currentStateLetter = L"R";
            break;
        case State::FilledRectangle:
            m_currentStateLetter = L"A";
            break;
        case State::Circle:
            m_currentStateLetter = L"C";
            break;
        case State::WriteFile:
            m_currentStateLetter = L"W";
            m_save = true;
            thr = std::thread(Mode::revertState, Mode::current);
            thr.detach();
            break;
        case State::OpenFile:
            m_currentStateLetter = L"O";
            m_load = true;
            thr = std::thread(Mode::revertState, Mode::current);
            thr.detach();
            break;
    }
}

void Mode::updateColor()
{
    const unsigned mouseX { static_cast<unsigned>(mousePosition.x) };
    const unsigned mouseY { static_cast<unsigned>(mousePosition.y) };

    if (mouseX >= minX && mouseX <= maxX && mouseY >= minY && mouseY <= maxY)
    {
        const sf::Color newColor { m_image.getPixel(mouseX - Layout::ColorsMargin,
                                                    mouseY - Layout::ColorsMargin) };
        if (current == State::ColorForeground)
            colorForeground = newColor;
        else
            colorBackground = newColor;
    }
}

bool Mode::saveRequested()
{
    if (m_save)
    {
        m_save = false;
        return true;
    }

    return false;
}

bool Mode::loadRequested()
{
    if (m_load)
    {
        m_load = false;
        return true;
    }

    return false;
}
void Mode::revertState(State beforeRevert)
{
    std::ostringstream ostr;
    ostr << std::this_thread::get_id();
    std::string threadID { ostr.str() };

    Logger::log(std::cout, "thread execution started with ID", threadID);

    std::this_thread::sleep_for(std::chrono::milliseconds(Settings::StateRevertDelayMs));
    if (current == beforeRevert)
    {
        if (m_previous != State::WriteFile && m_previous != State::OpenFile)
            updateState(m_previous);
        else
            updateState(State::None);
    }

    Logger::log(std::cout, "thread finished with ID", threadID);
}
