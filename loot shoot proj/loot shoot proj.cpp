#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include "Player.h"
#include "Enemy.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Gun Game Test");
    sf::Clock pClock, eClock;
    sf::Texture bgTexture;
    sf::Sprite background;
    sf::CircleShape circ;
    Player player(window);
    Enemy enemy(window);

    window.setFramerateLimit(60);

    bgTexture.loadFromFile("background.png");
    background.setTexture(bgTexture);
    background.setOrigin(background.getLocalBounds().width / 2, background.getLocalBounds().height / 2);

    circ.setRadius(100);

    //game loop begins, runs every frame for the window
    while (window.isOpen())
    {
        //allows window closing
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //player shoots
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && pClock.getElapsedTime().asMilliseconds() >= 80)
        {
            player.shoot();
            pClock.restart();
        }

        //enemy shoots
        if (enemy.isAlive() && eClock.getElapsedTime().asSeconds() >= 1)
        {
            enemy.shoot(player);
            eClock.restart();
        }


        player.move(circ.getGlobalBounds());


        player.spin(window);
        if (enemy.isAlive())
        {
            enemy.spin(player);
        }
        else
        {
            enemy.deathAnim();
        }
        player.bulletUpdate();
        enemy.bulletUpdate(player);

        enemy.posUpdate(0 - player.getPosX(), 0 - player.getPosY());
        background.setPosition(800 - player.getPosX(), 
            400 - player.getPosY());
        circ.setPosition(background.getPosition());

        if (!enemy.isDead() && player.bulletCollision(enemy))
        {
            enemy.dmg(player.hitEnemy(enemy));
        }

        window.clear();
        window.draw(background);
        window.draw(circ);
        if (!enemy.isDead())
        {
            window.draw(enemy);
            enemy.draw(window);
        }
        window.draw(player);
        player.draw(window);
        window.display();
    }

    return 0;
}





/*
WALL COLLISION HAPPENS

if()
accel.x *= -1; 
if()
accel.y *= -1;

*/