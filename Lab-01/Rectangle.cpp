#include "Logger.h"
#include "Mode.h"
#include "Rectangle.h"
#include "Shape.h"

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

Rectangle::Rectangle(const sf::Vector2f & startPosition) : Shape(startPosition)
{
    rectangle.setOutlineColor(Mode::colorForeground);
    rectangle.setFillColor(Mode::current == State::Rectangle ? sf::Color::Transparent
                                                             : Mode::colorBackground);
    rectangle.setOutlineThickness(1.0f);
    rectangle.setPosition(m_startPosition);

    Logger::logPosition(std::cout, "rectangle", m_startPosition);
}
