#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include "Player.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Gun Game Test");
    sf::Clock clock;
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

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clock.getElapsedTime().asMilliseconds() >= 50)
        {
            player.shoot();
            clock.restart();
        }

        player.spin(window);
        player.bulletUpdate();

        window.clear();
        window.draw(player);
        player.draw(window);
        window.display();
    }

    return 0;
}
