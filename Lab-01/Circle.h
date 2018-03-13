#pragma once

#include "Shape.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Circle : public Shape
{
public:
    explicit Circle(const sf::Vector2f& startPosition);
    virtual ~Circle() = default;

    virtual void update();

private:
    float calculateRadius() const;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    { target.draw(circle, states); }

private:
    sf::CircleShape circle;
};
