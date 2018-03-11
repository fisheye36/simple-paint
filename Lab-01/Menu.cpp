#include "Menu.h"
#include "Mode.h"
#include "font.h"
#include <SFML/Graphics.hpp>

Menu::Menu()
{
    m_font.loadFromMemory((void *) FontData, FontDataSize);
    m_text->setFont(m_font);
    m_text->setFillColor(sf::Color::White);
    m_text->setCharacterSize(12u);

    m_rectangle.setFillColor(sf::Color::Transparent);
    m_rectangle.setOutlineColor(sf::Color::White);
    m_rectangle.setOutlineThickness(1.0f);
    m_rectangle.setPosition(2.0f, 62.0f);

    unsigned x, y;
    m_colorsPixels = new sf::Uint8[m_ColorsSizeX * m_ColorsSizeY * 4u];
    for (x = 0u; x < 255u; ++x)
    {
        for (y = 0u; y < 30u; ++y)
        {
            drawToColorPixels(x, y, x, 255, 0);
            drawToColorPixels(x + 255u, y, 255, 255 - x, 0);
            drawToColorPixels(x + 510u, y, 255, 0, x);
            drawToColorPixels(254u - x, y + 30u, 0, 255, 255 - x);
            drawToColorPixels(509u - x, y + 30u, 0, x, 255);
            drawToColorPixels(764u - x, y + 30u, 255 - x, 0, 255);
        }
    }

    m_colorsTexture.create(m_ColorsSizeX, m_ColorsSizeY);
    m_colorsTexture.update(m_colorsPixels);

    m_colorsSprite.setTexture(m_colorsTexture);
    m_colorsSprite.setPosition(1, 1);
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    drawText(target, 5, 600, L"f - wybór koloru rysowania");
    drawText(target, 5, 615, L"b - wybór koloru wype³niania");
    drawText(target, 5, 630, L"l - rysowanie linii");

    drawText(target, 200, 600, L"r - rysowanie prostok¹ta");
    drawText(target, 200, 615, L"a - rysowanie wype³nionego prostok¹ta");
    drawText(target, 200, 630, L"c - rysowanie okrêgu");

    drawText(target, 470, 600, L"w - zapis do pliku");
    drawText(target, 470, 615, L"o - odczyt z pliku");
    drawText(target, 470, 630, L"esc - wyjœcie");

    std::wstring current = L"Aktualne: " + Mode::m_currentStateLetter;
    drawText(target, 650, 615, current);

    target.draw(m_rectangle, states);
    target.draw(m_colorsSprite, states);
}
