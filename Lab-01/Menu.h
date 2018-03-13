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
    void initializeColors();
    void initializePicks();
    void initializeWorkspace();
    void initializeToolbar();

    void drawToColorPixels(unsigned x, unsigned y, sf::Uint8 r, sf::Uint8 g, sf::Uint8 b);
    void drawText(sf::RenderTarget& target, float x, float y,
                  const sf::String& str) const;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::RectangleShape m_colorsMask { sf::Vector2f(Layout::ColorsMaskWidth,
                                                   Layout::ColorsMaskHeight) };
    sf::Uint8 *m_colorsPixels;
    sf::Texture m_colorsTexture;
    sf::Sprite m_colorsSprite;

    mutable sf::RectangleShape m_pickFg { sf::Vector2f(Layout::PickWidth,
                                                       Layout::PickHeight) };
    mutable sf::RectangleShape m_pickBg { sf::Vector2f(Layout::PickWidth,
                                                       Layout::PickHeight) };
    sf::RectangleShape m_workspace { sf::Vector2f(Layout::WorkspaceWidth,
                                                  Layout::WorkspaceHeight) };

    sf::RectangleShape m_toolbarMask { sf::Vector2f(Layout::ToolbarMaskWidth,
                                                    Layout::ToolbarMaskHeight) };
    sf::Font m_font;
    mutable sf::Text m_text;
};
