#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class Controller
{
public:
    Controller(sf::RenderWindow & _window, sf::Sprite & _sprite);
    ~Controller();

    void process();

private:
    sf::Sprite & sprite;
    sf::RenderWindow & window;

    struct Pimpl;
    std::unique_ptr<Pimpl> _pimpl;
};