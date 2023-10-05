#include "Player.h"
#include <math.h>
#include <iostream>

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

float Player::getPosX()
{
    return pos.x;
}

float Player::getPosY()
{
    return pos.y;
}

void Player::shoot()
{
    Bullet newBullet(getPosition().x + pos.x, getPosition().y + pos.y);

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
    sf::Vector2f num;
    num.x = window.getSize().x / 2.0, 
    num.y = window.getSize().y / 2.0;

    if (sf::Mouse::getPosition(window).x > 640)
    {
        gunLine.setRotation((atan((sf::Mouse::getPosition(window).y - num.y)
            / (sf::Mouse::getPosition(window).x - num.x))) * 45 / atan(1));
    }
    else if (sf::Mouse::getPosition(window).x < 640)
    {
        gunLine.setRotation(atan((sf::Mouse::getPosition(window).y - num.y)
            / (sf::Mouse::getPosition(window).x - num.x)) * 45 / atan(1) + 180);
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
        bullets.at(i).setPosition(bullets.at(i).getPosition().x 
            - pos.x, bullets.at(i).getPosition().y - pos.y);
    }
}

void Player::move()
{
    const float speed = 0.25;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && accel.y > speed * -20)
    {
        accel.y -= speed;
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && accel.y < 0)
    {
        accel.y += speed / 2;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && accel.x > speed * -20)
    {
        accel.x -= speed;
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && accel.x < 0)
    {
        accel.x += speed / 2;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && accel.y < speed * 20)
    {
        accel.y += speed;
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S) && accel.y > 0)
    {
        accel.y -= speed / 2;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && accel.x < speed * 20)
    {
        accel.x += speed;
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D) && accel.x > 0)
    {
        accel.x -= speed / 2;
    }

    if(abs(hypot(accel.x, accel.y)) > speed * 20 && accel.x != 0 && accel.y != 0)
    {
        std::cout << speed * 20 << ' ' << accel.x << ' ' << accel.y << ' '
            << accel.x / speed * 20
            << std::endl;
        if (abs(accel.y) < abs(accel.x))
        {
            accel.x = speed * 20 * cos(asin(accel.y / (speed * 20)));
        }
        else if (abs(accel.x) < abs(accel.y))
        {
            accel.y = speed * 20 * cos(asin(accel.x / (speed * 20)));
        }
    }

    std::cout << speed * 20 << ' ' << accel.x << ' ' << accel.y << ' '
        << accel.x / speed * 20
        << std::endl;
    //std::cout << accel.x << ' ' << accel.y << std::endl;
    pos += accel;
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