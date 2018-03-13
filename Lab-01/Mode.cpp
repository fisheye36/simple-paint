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

sf::Color Mode::colorForeground { sf::Color::Red };
sf::Color Mode::colorBackground { sf::Color::Yellow };

State Mode::previous { State::None };
bool Mode::save { false };
bool Mode::load { false };

void Mode::updateState(State newState)
{
    previous = current;
    current = newState;
    Logger::log(std::cout, "previous state", static_cast<int>(previous));
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
            save = true;
            thr = std::thread(Mode::revertState, Mode::current);
            thr.detach();
            break;
        case State::OpenFile:
            m_currentStateLetter = L"O";
            load = true;
            thr = std::thread(Mode::revertState, Mode::current);
            thr.detach();
            break;
    }
}

bool Mode::saveRequested()
{
    if (save)
    {
        save = false;
        return true;
    }

    return false;
}

bool Mode::loadRequested()
{
    if (load)
    {
        load = false;
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
        if (previous != State::WriteFile && previous != State::OpenFile)
            updateState(previous);
        else
            updateState(State::None);
    }

    Logger::log(std::cout, "thread finished with ID", threadID);
}
