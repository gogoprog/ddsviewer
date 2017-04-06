#include <iostream>
#include <SFML/Graphics.hpp>

#include "ddsloader.h"

int main(int argc, char *argv[])
{
    std::cout << "ddsviewer" << std::endl;

    if(argc > 1)
    {
        DdsLoader loader;

        auto ddsFile = loader.load(argv[1]);

        sf::RenderWindow window(sf::VideoMode(800, 600), "ddsviewer");
        sf::Event event;

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
                }
            }
        }
    }

    return EXIT_SUCCESS;
}