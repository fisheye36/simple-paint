#pragma once

#include "Shape.h"
#include "Mode.h"
#include "Logger.h"

#include <iostream>
#include <SFML/Graphics.hpp>

class Rectangle : public Shape
{
public:
    explicit Rectangle(const sf::Vector2f& startPosition) : Shape(startPosition)
    {
        rectangle.setOutlineColor(Mode::colorForeground);
        rectangle.setFillColor(Mode::current == State::Rectangle ? sf::Color::Transparent
                                                                 : Mode::colorBackground);
        rectangle.setOutlineThickness(1.0f);
        rectangle.setPosition(m_startPosition);

        Logger::logPosition(std::cout, "rectangle", m_startPosition.x, m_startPosition.y);
    }
    virtual ~Rectangle() = default;
    virtual void update()
    {
        Shape::update();
        rectangle.setSize(m_endPosition - m_startPosition);
    }

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    { target.draw(rectangle, states); }

private:
    sf::RectangleShape rectangle;
};
