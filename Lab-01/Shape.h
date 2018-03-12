#pragma once

#include "Mode.h"
#include "Logger.h"
#include <iostream>
#include <SFML/Graphics.hpp>

class Shape : public sf::Drawable
{
public:
    explicit Shape(const sf::Vector2f& startPosition) : m_startPosition(startPosition),
                                                        m_endPosition(startPosition)
    { Logger::logPosition(std::cout, "shape", m_startPosition.x, m_startPosition.y); }
    virtual ~Shape() = default;
    virtual void update() { m_endPosition = Mode::mousePosition; }

protected:
    sf::Vector2f m_startPosition;
    sf::Vector2f m_endPosition;
};
