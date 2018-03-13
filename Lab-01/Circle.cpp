#include "Circle.h"
#include "Logger.h"
#include "Mode.h"
#include "Shape.h"

#include <cmath>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

Circle::Circle(const sf::Vector2f & startPosition) : Shape(startPosition)
{
    circle.setOutlineColor(Mode::colorForeground);
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineThickness(1.0f);
    circle.setPosition(m_startPosition);

    Logger::logPosition(std::cout, "circle", m_startPosition.x, m_startPosition.y);
}

inline void Circle::update()
{
    Shape::update();
    float radius { calculateRadius() };
    circle.setOrigin(radius, radius);
    circle.setRadius(radius);
}

inline float Circle::calculateRadius() const
{
    sf::Vector2f diff { m_endPosition - m_startPosition };
    return std::sqrt(diff.x * diff.x + diff.y * diff.y);
}
