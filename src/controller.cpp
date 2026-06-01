#include "controller.h"

#include <iostream>
#include <SFML/System/Vector2.hpp>

struct Controller::Pimpl
{
    sf::Vector2f mouseStart;
    sf::Vector2f spriteStart;
    bool movingSprite = false;
};

Controller::~Controller() = default;

Controller::Controller(sf::RenderWindow & _window, sf::Sprite & _sprite)
    :
    window(_window),
    sprite(_sprite),
    _pimpl(new Pimpl())
{
    sprite.setOrigin(sf::Vector2f(sprite.getTexture().getSize()) * 0.5f);
}

void Controller::process()
{
    auto & pimpl = *_pimpl;

    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
            {
                window.close();
            }
        }
        else if (const auto* mouseWheelScrolled = event->getIf<sf::Event::MouseWheelScrolled>())
        {
            if (mouseWheelScrolled->delta > 0)
            {
                sprite.setScale(sprite.getScale() * 1.1f);
            }
            else
            {
                sprite.setScale(sprite.getScale() / 1.1f);
            }
        }
        else if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
        {
            pimpl.mouseStart = sf::Vector2f(mouseButtonPressed->position.x, mouseButtonPressed->position.y);
            pimpl.spriteStart = sprite.getPosition();
            pimpl.movingSprite = true;
        }
        else if (const auto* mouseButtonReleased = event->getIf<sf::Event::MouseButtonReleased>())
        {
            pimpl.movingSprite = false;
        }
        else if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>())
        {
            if(pimpl.movingSprite)
            {
                auto delta = sf::Vector2f(mouseMoved->position.x, mouseMoved->position.y) - pimpl.mouseStart;
                sprite.setPosition(pimpl.spriteStart + delta);
            }
        }
        else if (const auto* resized = event->getIf<sf::Event::Resized>())
        {
            window.setView(sf::View(sf::Vector2f(0, 0), sf::Vector2f(resized->size.x, resized->size.y)));
        }
    }

    window.clear();
    window.draw(sprite);
    window.display();
}