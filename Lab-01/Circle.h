#pragma once

#include "Shape.h"
#include "Mode.h"

#include <iostream>
#include <cmath>

#include <SFML/Graphics.hpp>

class Circle : public Shape
{
public:
    explicit Circle(const sf::Vector2f& startPosition) : Shape(startPosition)
    {
        circle.setOutlineColor(Mode::colorForeground);
        circle.setFillColor(sf::Color::Transparent);
        circle.setOutlineThickness(1.0f);
        circle.setPosition(m_startPosition);

        std::cout << "Circle x = " << m_startPosition.x
            << ", Circle y = " << m_startPosition.y << std::endl;
    }
    virtual ~Circle() = default;
    virtual void update()
    {
        Shape::update();
        float radius { calculateRadius() };
        circle.setOrigin(radius, radius);
        circle.setRadius(radius);
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(circle, states);
    }

private:
    float calculateRadius()
    {
        sf::Vector2f diff { m_endPosition - m_startPosition };
        return std::sqrt(diff.x * diff.x + diff.y * diff.y);
    }

private:
    sf::CircleShape circle;
};
