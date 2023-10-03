#include "Player.h"
#include <math.h>

Player::Player(sf::RenderWindow& window)
{
	setRadius(25.f);
    setFillColor(sf::Color::Cyan);
    setOrigin(getRadius(), getRadius());
    setPosition(window.getSize().x / 2, window.getSize().y / 2);
	gunLine.setSize(sf::Vector2f(36, 16));
    gunLine.setFillColor(sf::Color::Cyan);
    gunLine.setOrigin(0, 8);
    gunLine.setPosition(window.getSize().x / 2, window.getSize().y / 2);
}

Player::~Player()
{

}

void Player::shoot()
{
    Bullet newBullet;

    newBullet.setRise(5 * sin(gunLine.getRotation() * atan(1) / 45));
    newBullet.setRun(5 * cos(gunLine.getRotation() * atan(1) / 45));

    //offsets the bullet to the front of the gun instead of firing from the
    //center of the player, purely for visual effect
    for (int i = 0; i < 6; i++)
    {
        newBullet.move();
    }

    bullets.push_back(newBullet);
}

void Player::spin(sf::RenderWindow& window)
{
    const float numX = window.getSize().x / 2.0, 
        numY = window.getSize().y / 2.0;

    if (sf::Mouse::getPosition(window).x > 640)
    {
        gunLine.setRotation((atan((sf::Mouse::getPosition(window).y - numY)
            / (sf::Mouse::getPosition(window).x - numX))) * 45 / atan(1));
    }
    else if (sf::Mouse::getPosition(window).x < 640)
    {
        gunLine.setRotation(atan((sf::Mouse::getPosition(window).y - numY)
            / (sf::Mouse::getPosition(window).x - numX)) * 45 / atan(1) + 180);
    }
    //preventing division by 0
    else if (sf::Mouse::getPosition(window).x == 640 
        && sf::Mouse::getPosition(window).y > 360)
    {
        gunLine.setRotation(90);
    }
    else if (sf::Mouse::getPosition(window).x == 640 
        && sf::Mouse::getPosition(window).y < 360)
    {
        gunLine.setRotation(270);
    }
}

void Player::bulletUpdate()
{
    for (int i = 0; i < bullets.size(); i++)
    {
        bullets.at(i).move();
    }
}

void Player::move()
{
    //if(hypot())
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(gunLine);
    for (int i = 0; i < bullets.size(); i++)
    {
        window.draw(bullets.at(i));
    }
}

bool Player::bulletCollision(sf::RectangleShape rect)
{
    for (int i = 0; i < bullets.size(); i++)
    {
        if (bullets.at(i).isTouching(rect))
        {
            return true;
        }
    }
    return false;
}
bool Player::bulletCollision(sf::CircleShape circ)
{
    for (int i = 0; i < bullets.size(); i++)
    {
        if (bullets.at(i).isTouching(circ))
        {
            return true;
        }
    }
    return false;
}