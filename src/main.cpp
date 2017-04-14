#include <iostream>
#include <SFML/Graphics.hpp>

#include "ddsloader.h"
#include "controller.h"

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
            sprite.setTexture(ddsFile->getTexture());
            Controller controller(window, sprite);

            while (window.isOpen())
            {
                controller.process();
            }
        }
    }

    return EXIT_SUCCESS;
}