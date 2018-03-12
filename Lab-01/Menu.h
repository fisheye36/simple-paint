#pragma once

#include "Config.h"
#include <SFML/Graphics.hpp>

class Menu : public sf::Drawable
{
public:
    Menu();
    virtual ~Menu() { delete[] m_colorsPixels; }
    void saveToFile(const sf::Window& window) const;

private:
    void drawToColorPixels(unsigned x, unsigned y, sf::Uint8 r, sf::Uint8 g, sf::Uint8 b)
    {
        m_colorsPixels[4u * (y * Layout::ColorsWidth + x) + 0u] = r;
        m_colorsPixels[4u * (y * Layout::ColorsWidth + x) + 1u] = g;
        m_colorsPixels[4u * (y * Layout::ColorsWidth + x) + 2u] = b;
        m_colorsPixels[4u * (y * Layout::ColorsWidth + x) + 3u] = sf::Uint8(255);
    }
    void drawText(sf::RenderTarget& target, float x, float y, const sf::String& str) const
    {
        m_text.setPosition(x, y);
        m_text.setString(str);
        target.draw(m_text);
    }
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::Font m_font;
    mutable sf::Text m_text;
    mutable sf::RectangleShape m_pickFg { sf::Vector2f(Layout::PickWidth,
                                                       Layout::PickHeight) };
    mutable sf::RectangleShape m_pickBg { sf::Vector2f(Layout::PickWidth,
                                                       Layout::PickHeight) };
    sf::RectangleShape m_workspace { sf::Vector2f(Layout::WorkspaceWidth,
                                                  Layout::WorkspaceHeight) };
    sf::Uint8 *m_colorsPixels;
    sf::Texture m_colorsTexture;
    sf::Sprite m_colorsSprite;
};
