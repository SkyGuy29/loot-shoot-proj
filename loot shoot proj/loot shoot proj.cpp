#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include "Player.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
    Player player(window);

    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        player.spin(window);
        
        window.clear();
        window.draw(player);
        player.draw(window);
        window.display();
    }

    return 0;
}
