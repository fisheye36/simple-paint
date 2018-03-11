#include "ShapeCollection.h"
#include "Shape.h"
#include "Line.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Mode.h"
#include <iostream>

ShapeCollection::~ShapeCollection()
{
    for (auto shape : m_collection)
        delete shape;
    m_collection.clear();
}

void ShapeCollection::drawNewShape()
{
    if (!m_currentlyDrawing)
    {
        m_initialShapePosition = Mode::mousePosition;
        m_currentlyDrawing = true;
    }
    else
    {
        delete m_newShape;
    }

    switch (Mode::current)
    {
        case Mode::Line:
            m_newShape = new Line(m_initialShapePosition);
            break;
        case Mode::Rectangle:
        case Mode::FilledRectangle:
            m_newShape = new Rectangle(m_initialShapePosition);
            break;
        case Mode::Circle:
            m_newShape = new Circle(m_initialShapePosition);
            break;
    }
}

void ShapeCollection::saveNewShape()
{
    if (m_newShape)
    {
        m_collection.push_back(m_newShape);
        m_newShape = nullptr;
        m_currentlyDrawing = false;
    }
    std::cout << "Shapes saved: " << m_collection.size() << std::endl;
}

void ShapeCollection::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto shape : m_collection)
    {
        target.draw(*shape, states);
    }

    if (m_newShape)
    {
        m_newShape->update();
        target.draw(*m_newShape, states);
    }
}