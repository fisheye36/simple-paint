#pragma once

#include "Shape.h"
#include "Mode.h"

#include <vector>
#include <memory>

#include <SFML/Graphics.hpp>

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
