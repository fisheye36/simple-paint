#include "Line.h"
#include "Logger.h"
#include "Mode.h"
#include "Shape.h"

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

Line::Line(const sf::Vector2f & startPosition) : Shape(startPosition)
{
    line[0].color = Mode::colorForeground;
    line[0].position = m_startPosition;
    line[1].color = Mode::colorBackground;
    line[1].position = m_endPosition;

    Logger::logPosition(std::cout, "line", m_startPosition.x, m_startPosition.y);
}
