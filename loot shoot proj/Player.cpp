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
    Bullet newBullet(12, getPosition() + pos);

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
    sf::Vector2i flip;
    if (sf::Mouse::getPosition(window).x < getPosition().x)
    {
        flip.x = 180;
    }

    if (sf::Mouse::getPosition(window).y < getPosition().y)
    {
        flip.y = 180;
    }

    if (sf::Mouse::getPosition(window).x != getPosition().x)
    {
        gunLine.setRotation(atan((sf::Mouse::getPosition(window).y - getPosition().y)
            / (sf::Mouse::getPosition(window).x - getPosition().x)) * 45 / atan(1) + flip.x);
    }
    //preventing division by 0
    else
    {
        gunLine.setRotation(90 + flip.y);
    }
}

void Player::bulletUpdate()
{
    for (int i = 0; i < bullets.size(); i++)
    {
        bullets.at(i).move();
        bullets.at(i).setPosition(bullets.at(i).getPosition().x 
            - pos.x, bullets.at(i).getPosition().y - pos.y);
        if (!bullets.at(i).isActive() || bullets.at(i).clock.getElapsedTime().asMilliseconds() >= 2000)
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

//checks if a point is within the boundaries of a rectangle
bool isWithin(sf::FloatRect rect, sf::Vector2f point)
{
    if (point.x > rect.left && point.x < rect.left + rect.width
        && point.y > rect.top && point.y < rect.top + rect.height)
    {
        return true;
    }
    return false;
}

//bounces the player off of a wall if they hit it
void Player::wallBounce(sf::FloatRect rect)
{
    //okay I'm redoing this
    sf::Vector2f topLeft, topRight, botLeft, botRight;

    topLeft.x = botLeft.x = getGlobalBounds().left;
    topRight.x = botRight.x = getGlobalBounds().left + getGlobalBounds().width;
    topLeft.y = topRight.y = getGlobalBounds().left;
    botLeft.y = botRight.y = getGlobalBounds().top + getGlobalBounds().height;

    //edge case: if two corners of player are in the bounds of the wall:
    //move them out to the edge of the wall, set acceleration in target direction to 0

    //top edge of player in wall
    if (isWithin(rect, topLeft) && isWithin(rect, topRight)
        || isWithin(rect, botLeft) && isWithin(rect, botRight))
    {
        vel.y = -vel.y;
    }

    //left edge of player in wall
    if (isWithin(rect, topLeft) && isWithin(rect, topLeft)
        || isWithin(rect, topRight) && isWithin(rect, botRight))
    {
        vel.x = -vel.x;
    }
}

void Player::move(sf::FloatRect rect)
{
    float neg = 0;

    //moves player up
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && vel.y > SPEED * -20)
    {
        vel.y -= SPEED;
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && vel.y < 0)
    {
        vel.y += SPEED / 2;
        if (vel.y > 0)
        {
            vel.y = 0;
        }
    }
    
    //moves player left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && vel.x > SPEED * -20)
    {
        vel.x -= SPEED;
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && vel.x < 0)
    {
        vel.x += SPEED / 2;
        if (vel.x > 0)
        {
            vel.x = 0;
        }
    }

    //moves player down
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && vel.y < SPEED * 20)
    {
        vel.y += SPEED;
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S) && vel.y > 0)
    {
        vel.y -= SPEED / 2;
        if (vel.y < 0)
        {
            vel.y = 0;
        }
    }

    //moves player right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && vel.x < SPEED * 20)
    {
        vel.x += SPEED;
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D) && vel.x > 0)
    {
        vel.x -= SPEED / 2;
        if (vel.x < 0)
        {         
            vel.x = 0;
        }
    }

    //truncates velocity values in diagonal directions, max speed will always be 5
    if(abs(hypot(vel.x, vel.y)) > SPEED * 20 && vel.x != 0 && vel.y != 0)
    {
        if (abs(vel.y) < abs(vel.x))
        {
            neg = vel.x / abs(vel.x); //this will be either 1 or -1, which will apply back in the next line 
            vel.x = neg * SPEED * 20 * cos(asin(vel.y / (SPEED * 20)));
        }
        else if (abs(vel.x) < abs(vel.y))
        {
            neg = vel.y / abs(vel.y);
            vel.y = neg * SPEED * 20 * sin(acos(vel.x / (SPEED * 20))); 
        }
    }

    wallBounce(rect);

    pos += vel;
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(gunLine);
    for (int i = 0; i < bullets.size(); i++)
    {
        if(bullets.at(i).isActive())
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
        if (bullets.at(i).isActive() && bullets.at(i).getGlobalBounds().intersects(circ.getGlobalBounds()))
        {
            return true;
        }
    }
    return false;
}

int Player::hitEnemy(sf::CircleShape enemy)
{
    for (int i = 0; i < bullets.size(); i++)
    {
        if (bullets.at(i).getGlobalBounds().intersects(enemy.getGlobalBounds()))
        {
            bullets.at(i).deactivate();
            return bullets.at(i).getDamage();
        }
    }
    return 0;
}