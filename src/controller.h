#pragma once

#include <SFML/Graphics.hpp>

class Controller
{
public:
    Controller(sf::RenderWindow & _window, sf::Sprite & _sprite)
        :
        window(_window),
        sprite(_sprite)
    {
    }

    void process();

private:
    sf::Sprite & sprite;
    sf::RenderWindow & window;
};