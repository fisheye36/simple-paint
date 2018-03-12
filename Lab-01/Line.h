#pragma once

#include "Shape.h"
#include "Mode.h"
#include "Logger.h"

#include <iostream>
#include <SFML/Graphics.hpp>

class Line : public Shape
{
public:
    explicit Line(const sf::Vector2f& startPosition) : Shape(startPosition)
    {
        line[0].color = Mode::colorForeground;
        line[0].position = m_startPosition;
        line[1].color = Mode::colorBackground;
        line[1].position = m_endPosition;

        Logger::logPosition(std::cout, "line", m_startPosition.x, m_startPosition.y);
    }
    virtual ~Line() = default;
    virtual void update()
    {
        Shape::update();
        line[1].position = m_endPosition;
    }

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    { target.draw(line, states); }

private:
    sf::VertexArray line{ sf::LinesStrip, 2u };
};
