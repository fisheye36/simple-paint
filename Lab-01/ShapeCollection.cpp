#include "ShapeCollection.h"
#include "Shape.h"
#include "Line.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Mode.h"
#include "Logger.h"

#include <iostream>
#include <vector>
#include <memory>

ShapeCollection::~ShapeCollection()
{
    for (auto shape : m_collection)
        delete shape;
    m_collection.clear();
}

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

Shape * ShapeCollection::instantiateShape() const
{
    switch (m_remembered)
    {
        case Mode::Line:
            return new Line(m_initialShapePosition);
        case Mode::Rectangle:
        case Mode::FilledRectangle:
            return new Rectangle(m_initialShapePosition);
        case Mode::Circle:
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
