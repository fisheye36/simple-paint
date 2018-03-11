#pragma once

#include "Shape.h"
#include "Mode.h"
#include <iostream>
#include <SFML/Graphics.hpp>

class Rectangle : public Shape
{
public:
    explicit Rectangle(const sf::Vector2f& startPosition) : Shape(startPosition)
    {
        rectangle.setOutlineColor(Mode::colorForeground);
        rectangle.setFillColor(Mode::current == Mode::Rectangle ? sf::Color::Transparent
                                                                : Mode::colorBackground);
        rectangle.setOutlineThickness(1.0f);
        rectangle.setPosition(m_startPosition);

        std::cout << "Rectangle x = " << m_startPosition.x
            << ", Rectangle y = " << m_startPosition.y << std::endl;
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
