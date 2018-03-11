#pragma once

#include <SFML/Graphics.hpp>

class Menu : public sf::Drawable
{
public:
    Menu();
    virtual ~Menu() { delete[] m_colorsPixels; }
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    void drawToColorPixels(unsigned x, unsigned y, sf::Uint8 r, sf::Uint8 g, sf::Uint8 b)
    {
        m_colorsPixels[4u * (y * m_ColorsSizeX + x) + 0u] = r;
        m_colorsPixels[4u * (y * m_ColorsSizeX + x) + 1u] = g;
        m_colorsPixels[4u * (y * m_ColorsSizeX + x) + 2u] = b;
        m_colorsPixels[4u * (y * m_ColorsSizeX + x) + 3u] = sf::Uint8(255);
    }
    void drawText(sf::RenderTarget& target, float x, float y,
                  const sf::String& str) const
    {
        m_text->setPosition(x, y);
        m_text->setString(str);
        target.draw(*m_text);
    }

private:
    const unsigned m_ColorsSizeX = 765u;
    const unsigned m_ColorsSizeY = 60u;

    sf::Font m_font;
    sf::Text *m_text{ new sf::Text };
    sf::RectangleShape m_rectangle{ sf::Vector2f(796.0f, 536.0f) };
    sf::Uint8 *m_colorsPixels;
    sf::Texture m_colorsTexture;
    sf::Sprite m_colorsSprite;
};
