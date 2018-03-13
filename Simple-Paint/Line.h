#pragma once

#include "Shape.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Line : public Shape
{
public:
    explicit Line(const sf::Vector2f& startPosition);
    virtual ~Line() = default;

    virtual void update()
    { Shape::update(); line[1].position = m_endPosition; }

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    { target.draw(line, states); }

private:
    sf::VertexArray line { sf::LinesStrip, 2u };
};
