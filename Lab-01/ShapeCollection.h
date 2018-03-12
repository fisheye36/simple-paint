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
    virtual ~ShapeCollection();

    void drawNewShape() const;
    void saveNewShape();

private:
    Shape * instantiateShape() const;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    mutable Mode::State m_remembered { Mode::None };
    mutable std::unique_ptr<Shape> m_newShape;
    mutable sf::Vector2f m_initialShapePosition;
    std::vector<Shape *> m_collection;
};
