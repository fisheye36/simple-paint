#pragma once

#include "Shape.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Rectangle : public Shape
{
public:
    explicit Rectangle(const sf::Vector2f& startPosition);
    virtual ~Rectangle() = default;

    virtual void update()
    { Shape::update(); rectangle.setSize(m_endPosition - m_startPosition); }

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    { target.draw(rectangle, states); }

private:
    sf::RectangleShape rectangle;
};
