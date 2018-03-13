#include "Circle.h"
#include "Line.h"
#include "Logger.h"
#include "Mode.h"
#include "Rectangle.h"
#include "Shape.h"
#include "ShapeCollection.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <iostream>
#include <vector>
#include <memory>

void ShapeCollection::drawNewShape() const
{
    m_remembered = Mode::current;
    if (!m_newShape)
        m_initialShapePosition = Mode::mousePosition;
    m_newShape.reset(instantiateShape());
}

void ShapeCollection::saveNewShape()
{
    if (m_newShape)
        m_collection.push_back(m_newShape.release());

    Logger::log(std::cout, "shapes saved", m_collection.size());
}

void ShapeCollection::clear()
{
    for (auto shape : m_collection)
        delete shape;
    m_collection.clear();
    Logger::log(std::cout, "collection cleared...");
}

Shape * ShapeCollection::instantiateShape() const
{
    switch (m_remembered)
    {
        case State::ColorForeground:
        case State::ColorBackground:
            Mode::updateColor();
            return nullptr;
        case State::Line:
            return new Line(m_initialShapePosition);
        case State::Rectangle:
        case State::FilledRectangle:
            return new Rectangle(m_initialShapePosition);
        case State::Circle:
            return new Circle(m_initialShapePosition);
        default:
            return nullptr;
    }
}

void ShapeCollection::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const auto shape : m_collection)
    {
        target.draw(*shape, states);
    }

    if (m_newShape && m_remembered != Mode::current)
        drawNewShape();
    if (m_newShape)
    {
        m_newShape->update();
        target.draw(*m_newShape, states);
    }
}
