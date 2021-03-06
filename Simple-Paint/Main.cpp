#include "Config.h"
#include "Logger.h"
#include "Menu.h"
#include "Mode.h"
#include "ShapeCollection.h"
#include "Workspace.h"

#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int getValidCoordinates(int coordinates, int min, int max);

int main()
{
    sf::RenderWindow window(sf::VideoMode(Layout::WinWidth, Layout::WinHeight),
                            Layout::WinTitle, sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60u);

    sf::Event event;
    Workspace workspace;
    ShapeCollection shapeCollection;
    Menu menu;

    while (window.isOpen())
    {
        window.clear(Layout::BackgroundColor);

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                    case sf::Keyboard::Q:
                    case sf::Keyboard::Escape:
                        window.close();
                        break;
                    case sf::Keyboard::F:
                        Mode::updateState(State::ColorForeground);
                        break;
                    case sf::Keyboard::B:
                        Mode::updateState(State::ColorBackground);
                        break;
                    case sf::Keyboard::L:
                        Mode::updateState(State::Line);
                        break;
                    case sf::Keyboard::R:
                        Mode::updateState(State::Rectangle);
                        break;
                    case sf::Keyboard::A:
                        Mode::updateState(State::FilledRectangle);
                        break;
                    case sf::Keyboard::C:
                        Mode::updateState(State::Circle);
                        break;
                    case sf::Keyboard::W:
                        Mode::updateState(State::WriteFile);
                        break;
                    case sf::Keyboard::O:
                        Mode::updateState(State::OpenFile);
                        break;
                }
            }
            else if (event.type == sf::Event::MouseMoved)
            {
                int mouseX = getValidCoordinates(event.mouseMove.x, 0, Layout::WinWidth);
                int mouseY = getValidCoordinates(event.mouseMove.y, 0, Layout::WinHeight);
                Mode::updateMousePosition(sf::Vector2f(mouseX, mouseY));
                Logger::logPosition(std::cout, "mouse", Mode::mousePosition);
            }
            else if (event.type == sf::Event::MouseButtonPressed
                     && event.mouseButton.button == sf::Mouse::Left)
            {
                shapeCollection.drawNewShape();
            }
            else if (event.type == sf::Event::MouseButtonReleased
                     && event.mouseButton.button == sf::Mouse::Left)
            {
                shapeCollection.saveNewShape();
            }
        }

        if (Mode::loadRequested())
        {
            Logger::log(std::cout, "loading image from file...");
            workspace.loadFromFile();
            shapeCollection.clear();
        }
        window.draw(workspace);
        window.draw(shapeCollection);
        window.draw(menu);
        if (Mode::saveRequested())
        {
            Logger::log(std::cout, "saving image to file...");
            workspace.saveToFile(window);
        }
        window.display();
    }

    return 0;
}

int getValidCoordinates(int coordinates, int min, int max)
{
    if (coordinates < min)
        coordinates = min;
    else if (coordinates > max)
        coordinates = max;

    return coordinates;
}
