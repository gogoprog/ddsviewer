#include "controller.h"

void Controller::process()
{
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

            default:
            break;
        }
    }

    window.clear();
    window.draw(sprite);
    window.display();
}