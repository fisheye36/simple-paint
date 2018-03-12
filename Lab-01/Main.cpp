#include "Config.h"
#include "Menu.h"
#include "ShapeCollection.h"
#include "Mode.h"
#include "Logger.h"

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

int getValidCoordinates(int coordinates, int min, int max);

int main()
{
    sf::RenderWindow window(sf::VideoMode(WinWidth, WinHeight), WinTitle,
                            sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60u);

    sf::Event event;
    Menu menu;
    ShapeCollection shapeCollection;

    while (window.isOpen())
    {
        window.clear(sf::Color::Black);

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
                    case sf::Keyboard::Escape:
                        window.close();
                        break;
                    case sf::Keyboard::F:
                        Mode::updateState(Mode::ColorForeground);
                        break;
                    case sf::Keyboard::B:
                        Mode::updateState(Mode::ColorBackground);
                        break;
                    case sf::Keyboard::L:
                        Mode::updateState(Mode::Line);
                        break;
                    case sf::Keyboard::R:
                        Mode::updateState(Mode::Rectangle);
                        break;
                    case sf::Keyboard::A:
                        Mode::updateState(Mode::FilledRectangle);
                        break;
                    case sf::Keyboard::C:
                        Mode::updateState(Mode::Circle);
                        break;
                    case sf::Keyboard::W:
                        Mode::updateState(Mode::WriteFile);
                        break;
                    case sf::Keyboard::O:
                        Mode::updateState(Mode::OpenFile);
                        break;
                }
            }
            else if (event.type == sf::Event::MouseMoved)
            {
                int mouseX = getValidCoordinates(event.mouseMove.x, 0, WinWidth);
                int mouseY = getValidCoordinates(event.mouseMove.y, 0, WinHeight);
                Mode::updateMousePosition(sf::Vector2f(mouseX, mouseY));
                Logger::logPosition(std::cout, "mouse", mouseX, mouseY);
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

        window.draw(shapeCollection);
        window.draw(menu);
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
