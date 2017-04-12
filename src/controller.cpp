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
}

void Controller::process()
{
    auto & pimpl = *_pimpl;
    sf::Event event;

    while (window.pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::Closed:
            {
                window.close();
            }
            break;

            case sf::Event::KeyPressed:
            {
                switch(event.key.code)
                {
                    case sf::Keyboard::Key::Escape:
                    {
                        window.close();
                    }
                    break;

                    default:
                    break;
                }
            }
            break;

            case sf::Event::MouseWheelScrolled:
            {
                if(event.mouseWheelScroll.delta > 0)
                {
                    sprite.setScale(sprite.getScale() * 1.1f);
                }
                else
                {
                    sprite.setScale(sprite.getScale() / 1.1f);
                }
            }
            break;

            case sf::Event::MouseButtonPressed:
            {
                pimpl.mouseStart = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                pimpl.spriteStart = sprite.getPosition();
                pimpl.movingSprite = true;
            }
            break;

            case sf::Event::MouseButtonReleased:
            {
                pimpl.movingSprite = false;
            }
            break;

            case sf::Event::MouseMoved:
            {
                if(pimpl.movingSprite)
                {
                    auto delta = sf::Vector2f(event.mouseMove.x, event.mouseMove.y) - pimpl.mouseStart;

                    sprite.setPosition(pimpl.spriteStart + delta);
                }
            }
            break;

            default:
            break;
        }
    }

    window.clear();
    window.draw(sprite);
    window.display();
}