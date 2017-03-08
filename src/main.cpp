#include <SFML/Graphics.hpp>
#include <iostream>

int main(int args, char *argv[])
{
    std::cout << "ddsviewer" << std::endl;

    sf::RenderWindow window(sf::VideoMode(800, 600), "ddsviewer");
    sf::Event event;

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    return EXIT_SUCCESS;
}