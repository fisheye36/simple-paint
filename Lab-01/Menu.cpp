#include "Menu.h"
#include "Mode.h"
#include "Config.h"
#include "Logger.h"
#include "font.h"

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace Layout;

Menu::Menu()
{
    initializeColors();
    initializePicks();
    initializeWorkspace();
    initializeToolbar();
}

void Menu::saveToFile(const sf::Window& window) const
{
    sf::Texture texture;
    texture.create(WinWidth, WinHeight);
    texture.update(window);
    sf::Image image { texture.copyToImage() };
    image.saveToFile("drawing.png");
}

void Menu::initializeColors()
{
    m_colorsMask.setFillColor(BackgroundColor);
    m_colorsMask.setPosition(ColorsMaskPosX, ColorsMaskPosY);

    m_colorsPixels = new sf::Uint8[ColorsWidth * ColorsHeight * 4u];
    const unsigned colorsRowHeight { ColorsHeight / 2u };
    for (unsigned x = 0u; x < RGBScale; ++x)
    {
        for (unsigned y = 0u; y < colorsRowHeight; ++y)
        {
            drawToColorPixels(x, y, x, RGBScale, 0u);
            drawToColorPixels(x + RGBScale, y, RGBScale, RGBScale - x, 0u);
            drawToColorPixels(x + RGBScale * 2u, y, RGBScale, 0u, x);

            drawToColorPixels(RGBScale - 1u - x, y + colorsRowHeight,
                              0u, RGBScale, RGBScale - x);
            drawToColorPixels(RGBScale * 2u - 1u - x, y + colorsRowHeight,
                              0u, x, RGBScale);
            drawToColorPixels(RGBScale * 3u - 1u - x, y + colorsRowHeight,
                              RGBScale - x, 0u, RGBScale);
        }
    }

    m_colorsTexture.create(ColorsWidth, ColorsHeight);
    m_colorsTexture.update(m_colorsPixels);

    m_colorsSprite.setTexture(m_colorsTexture);
    m_colorsSprite.setPosition(ColorsPosX, ColorsPosY);
}

void Menu::initializePicks()
{
    m_pickFg.setOutlineColor(sf::Color::White);
    m_pickFg.setOutlineThickness(1.0f);
    m_pickFg.setPosition(PickFgPosX, PickFgPosY);

    m_pickBg.setOutlineColor(sf::Color::White);
    m_pickBg.setOutlineThickness(1.0f);
    m_pickBg.setPosition(PickBgPosX, PickBgPosY);
}

void Menu::initializeWorkspace()
{
    m_workspace.setFillColor(sf::Color::Transparent);
    m_workspace.setOutlineColor(sf::Color::White);
    m_workspace.setOutlineThickness(1.0f);
    m_workspace.setPosition(WorkspacePosX, WorkspacePosY);
}

void Menu::initializeToolbar()
{
    m_toolbarMask.setFillColor(BackgroundColor);
    m_toolbarMask.setPosition(ToolbarMaskPosX, ToolbarMaskPosY);

    m_font.loadFromMemory((void *) FontData, FontDataSize);
    m_text.setFont(m_font);
    m_text.setFillColor(sf::Color::White);
    m_text.setCharacterSize(12u);
}

void Menu::drawToColorPixels(unsigned x, unsigned y, sf::Uint8 r, sf::Uint8 g, sf::Uint8 b)
{
    m_colorsPixels[4u * (y * Layout::ColorsWidth + x) + 0u] = r;
    m_colorsPixels[4u * (y * Layout::ColorsWidth + x) + 1u] = g;
    m_colorsPixels[4u * (y * Layout::ColorsWidth + x) + 2u] = b;
    m_colorsPixels[4u * (y * Layout::ColorsWidth + x) + 3u] = sf::Uint8(255);
}

void Menu::drawText(sf::RenderTarget & target, float x, float y, const sf::String & str) const
{
    m_text.setPosition(x, y);
    m_text.setString(str);
    target.draw(m_text);
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    m_pickFg.setFillColor(Mode::colorForeground);
    m_pickBg.setFillColor(Mode::colorBackground);

    target.draw(m_colorsMask, states);
    target.draw(m_toolbarMask, states);

    drawText(target, ToolbarCol1PosX, ToolbarRow1PosY, L"f - wybór koloru rysowania");
    drawText(target, ToolbarCol1PosX, ToolbarRow2PosY, L"b - wybór koloru wype³niania");
    drawText(target, ToolbarCol1PosX, ToolbarRow3PosY, L"l - rysowanie linii");

    drawText(target, ToolbarCol2PosX, ToolbarRow1PosY, L"r - rysowanie prostok¹ta");
    drawText(target, ToolbarCol2PosX, ToolbarRow2PosY,
             L"a - rysowanie wype³nionego prostok¹ta");
    drawText(target, ToolbarCol2PosX, ToolbarRow3PosY, L"c - rysowanie okrêgu");

    drawText(target, ToolbarCol3PosX, ToolbarRow1PosY, L"w - zapis do pliku");
    drawText(target, ToolbarCol3PosX, ToolbarRow2PosY, L"o - odczyt z pliku");
    drawText(target, ToolbarCol3PosX, ToolbarRow3PosY, L"esc - wyjœcie");

    const std::wstring current { L"Aktualne: " + Mode::m_currentStateLetter };
    drawText(target, ToolbarCol4PosX, ToolbarRow2PosY, current);

    target.draw(m_colorsSprite, states);
    target.draw(m_pickFg, states);
    target.draw(m_pickBg, states);
    target.draw(m_workspace, states);
}
