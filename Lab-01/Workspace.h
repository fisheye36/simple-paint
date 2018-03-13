#pragma once

#include "Config.h"
#include <SFML/Graphics.hpp>

class Workspace : public sf::Drawable
{
public:
    Workspace();
    virtual ~Workspace() = default;

    void saveToFile(const sf::Window& window) const;
    void loadFromFile();

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    { target.draw(m_workspace, states); }

private:
    sf::Texture m_workspaceTexture;
    sf::RectangleShape m_workspace { sf::Vector2f(Layout::WorkspaceWidth,
                                                  Layout::WorkspaceHeight) };
};
