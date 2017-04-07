#include <iostream>
#include <SFML/Graphics.hpp>

#include "ddsloader.h"

int main(int argc, char *argv[])
{
    std::cout << "ddsviewer" << std::endl;

    if(argc > 1)
    {
        sf::RenderWindow window(sf::VideoMode(800, 600), "ddsviewer");

        auto ddsFile = DdsLoader::load(argv[1]);

        if(ddsFile)
        {
            sf::Sprite sprite;
            sf::Event event;

            sprite.setTexture(ddsFile->getTexture());

            while (window.isOpen())
            {
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
                            if(event.key.code == sf::Keyboard::Key::Escape)
                            {
                                window.close();
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
        }
    }

    return EXIT_SUCCESS;
}