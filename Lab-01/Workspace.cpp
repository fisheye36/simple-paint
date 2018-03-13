#include "Workspace.h"
#include "Config.h"
#include <SFML/Graphics.hpp>

using namespace Layout;

Workspace::Workspace()
{
    m_workspaceTexture.create(WorkspaceWidth, WorkspaceHeight);
    m_workspace.setFillColor(sf::Color::Transparent);
    m_workspace.setOutlineColor(sf::Color::White);
    m_workspace.setOutlineThickness(1.0f);
    m_workspace.setPosition(WorkspacePosX, WorkspacePosY);
}

void Workspace::saveToFile(const sf::Window& window) const
{
    sf::Texture texture;
    texture.create(WinWidth, WinHeight);
    texture.update(window);

    sf::Image image { texture.copyToImage() };
    sf::Image screenshot;
    sf::IntRect screenshotRect { sf::Vector2i(WorkspacePosX, WorkspacePosY),
                                 sf::Vector2i(WorkspaceWidth, WorkspaceHeight) };
    screenshot.create(WorkspaceWidth, WorkspaceHeight);
    screenshot.copy(image, 0u, 0u, screenshotRect);
    screenshot.saveToFile(Settings::ScreenshotFileName);
}

void Workspace::loadFromFile()
{
    m_workspaceTexture.loadFromFile(Settings::ScreenshotFileName);
    m_workspace.setTexture(&m_workspaceTexture);
    m_workspace.setFillColor(sf::Color::White);
}
