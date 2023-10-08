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
    if (sf::Mouse::getPosition(window).x > getPosition().x)
    {
        gunLine.setRotation((atan((sf::Mouse::getPosition(window).y - getPosition().y)
            / (sf::Mouse::getPosition(window).x - getPosition().x))) * 45 / atan(1));
    }
    else if (sf::Mouse::getPosition(window).x < getPosition().x)
    {
        gunLine.setRotation(atan((sf::Mouse::getPosition(window).y - getPosition().y)
            / (sf::Mouse::getPosition(window).x - getPosition().x)) * 45 / atan(1) + 180);
    }
    //preventing division by 0
    else if (sf::Mouse::getPosition(window).x == getPosition().x
        && sf::Mouse::getPosition(window).y > getPosition().y)
    {
        gunLine.setRotation(90);
    }
    else if (sf::Mouse::getPosition(window).x == getPosition().x
        && sf::Mouse::getPosition(window).y < getPosition().y)
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
        if (bullets.at(i).clock.getElapsedTime().asMilliseconds() >= 2000)
        {
            std::vector<Bullet> temp;
            for (int j = 0; j < i; j++)
                temp.push_back(bullets.at(j));
            for (int j = i + 1; j < bullets.size(); j++)
                temp.push_back(bullets.at(j));
            while (!bullets.empty())
                bullets.pop_back();
            for (int j = 0; j < temp.size(); j++)
                bullets.push_back(temp.at(j));
        }
    }
}

void Player::move()
{
    float neg = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && accel.y > speed * -20)
    {
        accel.y -= speed;
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && accel.y < 0)
    {
        accel.y += speed / 2;
        if (accel.y > 0)
        {
            accel.y = 0;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && accel.x > speed * -20)
    {
        accel.x -= speed;
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && accel.x < 0)
    {
        accel.x += speed / 2;
        if (accel.x > 0)
        {
            accel.x = 0;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && accel.y < speed * 20)
    {
        accel.y += speed;
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S) && accel.y > 0)
    {
        accel.y -= speed / 2;
        if (accel.y < 0)
        {
            accel.y = 0;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && accel.x < speed * 20)
    {
        accel.x += speed;
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D) && accel.x > 0)
    {
        accel.x -= speed / 2;
        if (accel.x < 0)
        {         
            accel.x = 0;
        }
    }

    if(abs(hypot(accel.x, accel.y)) > speed * 20 && accel.x != 0 && accel.y != 0)
    {
        if (abs(accel.y) < abs(accel.x))
        {
            neg = accel.x / abs(accel.x); //this will be either 1 or -1, which will apply back in the next line 
            accel.x = neg * speed * 20 * cos(asin(accel.y / (speed * 20)));
        }
        else if (abs(accel.x) < abs(accel.y))
        {
            neg = accel.y / abs(accel.y);
            accel.y = neg * speed * 20 * sin(acos(accel.x / (speed * 20))); 
        }
    }
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
        if (bullets.at(i).getGlobalBounds().intersects(rect.getGlobalBounds()))
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
        if (bullets.at(i).getGlobalBounds().intersects(circ.getGlobalBounds()))
        {
            return true;
        }
    }
    return false;
}

/*
//removes a value from vec at position
void erase(std::vector<double>& vec, int position)
{
    std::vector<double> temp;
    for (int i = 0; i < position; i++)
        temp.push_back(vec.at(i));
    for (int i = position + 1; i < vec.size(); i++)
        temp.push_back(vec.at(i));
    while (!vec.empty())
    vec.pop_back();
    for (int i = 0; i < temp.size(); i++)
        vec.push_back(temp.at(i));
}
//adds a value (newNum) to vec at position
void insert(std::vector<double>& vec, double newNum, int position)
{
    std::vector<double> temp;
    for (int i = 0; i < position; i++)
        temp.push_back(vec.at(i));
    temp.push_back(newNum);
    for (int i = position; i < vec.size(); i++)
        temp.push_back(vec.at(i));
    while (!vec.empty())
    vec.pop_back();
    for (int i = 0; i < temp.size(); i++)
        vec.push_back(temp.at(i));
}
*/