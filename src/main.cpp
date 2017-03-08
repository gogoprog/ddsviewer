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

    return EXIT_SUCCESS;
}