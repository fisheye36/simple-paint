#pragma once

#include "Mode.h"
#include "Shape.h"

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class ShapeCollection : public sf::Drawable
{
public:
    ShapeCollection() = default;
    virtual ~ShapeCollection() { clear(); }

    void drawNewShape() const;
    void saveNewShape();
    void clear();

private:
    Shape * instantiateShape() const;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    mutable State m_remembered { State::None };
    mutable std::unique_ptr<Shape> m_newShape;
    mutable sf::Vector2f m_initialShapePosition;
    std::vector<Shape *> m_collection;
};
