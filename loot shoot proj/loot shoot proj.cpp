#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include "Player.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Gun Game Test");
    sf::Clock clock;
    sf::Texture bgTexture;
    sf::Sprite background;
    sf::CircleShape circ;
    Player player(window);

    window.setFramerateLimit(60);

    bgTexture.loadFromFile("background.png");
    background.setTexture(bgTexture);
    background.setOrigin(background.getLocalBounds().width / 2, background.getLocalBounds().height / 2);

    circ.setRadius(100);

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

        player.move();

        player.spin(window);
        player.bulletUpdate();

        background.setPosition(window.getSize().x / 2 - player.getPosX(), 
            window.getSize().y / 2 - player.getPosY());
        circ.setPosition(background.getPosition());

        window.clear();
        window.draw(background);
        window.draw(circ);
        window.draw(player);
        player.draw(window);
        window.display();
    }

    return 0;
}
