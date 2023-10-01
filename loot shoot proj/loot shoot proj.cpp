#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>


int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
    sf::CircleShape shape(50.f);
    sf::RectangleShape gunLine(sf::Vector2f(75, 10));
    const float numbahX = window.getSize().x / 2.0, numbahY = window.getSize().y / 2.0;
    shape.setFillColor(sf::Color::Cyan);
    shape.setOrigin(50, 50);
    shape.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    gunLine.setFillColor(sf::Color::Cyan);
    gunLine.setOrigin(0, 5);
    gunLine.setPosition(window.getSize().x / 2, window.getSize().y / 2);

    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        /*
        if (sf::Mouse::getPosition(window).x > 640)
        {
            gunLine.setRotation((atan((sf::Mouse::getPosition(window).y - 360.0) / (sf::Mouse::getPosition(window).x - 640.0))) * 45 / atan(1));
        }
        else if (sf::Mouse::getPosition(window).x < 640)
        {
            gunLine.setRotation((atan((sf::Mouse::getPosition(window).y - 360.0) / (sf::Mouse::getPosition(window).x - 640.0))) * 45 / atan(1) + 180);
        }
        */
        if (sf::Mouse::getPosition(window).x > 640)
        {
            gunLine.setRotation((atan((sf::Mouse::getPosition(window).y - numbahY) 
                / (sf::Mouse::getPosition(window).x - numbahX))) * 45 / atan(1));
        }
        else if (sf::Mouse::getPosition(window).x < 640)
        {
            gunLine.setRotation(atan((sf::Mouse::getPosition(window).y - numbahY)
                / (sf::Mouse::getPosition(window).x - numbahX)) * 45 / atan(1) + 180);
        }
        else if (sf::Mouse::getPosition(window).x == 640 && sf::Mouse::getPosition(window).y > 360)
        {
            gunLine.setRotation(90);
        }
        else if (sf::Mouse::getPosition(window).x == 640 && sf::Mouse::getPosition(window).y < 360)
        {
            gunLine.setRotation(270);
        }

        window.clear();
        window.draw(shape);
        window.draw(gunLine);
        window.display();
    }

    return 0;
}
