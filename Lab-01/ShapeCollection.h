#pragma once

#include "Shape.h"
#include <vector>
#include <SFML/Graphics.hpp>

class ShapeCollection : public sf::Drawable
{
public:
    ShapeCollection() = default;
    virtual ~ShapeCollection();

    void drawNewShape();
    void saveNewShape();

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    bool m_currentlyDrawing { false };
    Shape * m_newShape { nullptr };
    sf::Vector2f m_initialShapePosition;
    std::vector<Shape *> m_collection;
};

