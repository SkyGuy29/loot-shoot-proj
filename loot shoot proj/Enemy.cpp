#include "Enemy.h"
#include "Player.h"
#include <math.h>
#include <iostream>

Enemy::Enemy(sf::RenderWindow& window)
{
    setRadius(25.f);
    setFillColor(sf::Color::Red);
    setOrigin(getRadius(), getRadius());
    gunLine.setSize(sf::Vector2f(36, 16));
    gunLine.setFillColor(sf::Color::Red);
    gunLine.setOrigin(0, 8);
}

Enemy::~Enemy()
{

}

int Enemy::getHealth()
{
    return health;
}

bool Enemy::isAlive()
{
    return alive;
}

void Enemy::bulletUpdate(Player player)
{
    for (int i = 0; i < bullets.size(); i++)
    {
        bullets.at(i).move();
        bullets.at(i).setPosition(bullets.at(i).getPosition().x
            - player.getPosX(), bullets.at(i).getPosition().y - player.getPosY());
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

void Enemy::posUpdate(float x, float y)
{
    setPosition(x, y);
    gunLine.setPosition(getPosition());
}

void Enemy::dmg(int d)
{
    health -= d;
    if (health <= 0)
    {
        alive = false;
    }
}

void Enemy::draw(sf::RenderWindow& window)
{
    window.draw(gunLine);
    for (int i = 0; i < bullets.size(); i++)
    {
        window.draw(bullets.at(i));
    }
}

void Enemy::move()
{
    float neg = 0;
    const int SLOW = 4;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && accel.y > speed * -20)
    {
        accel.y -= speed;
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && accel.y < 0)
    {
        accel.y += speed / SLOW;
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
        accel.x += speed / SLOW;
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
        accel.y -= speed / SLOW;
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
        accel.x -= speed / SLOW;
        if (accel.x < 0)
        {
            accel.x = 0;
        }
    }

    if (abs(hypot(accel.x, accel.y)) > speed * 20 && accel.x != 0 && accel.y != 0)
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
    setPosition(getPosition() + accel);
}

void Enemy::shoot(Player player)
{
    Bullet newBullet(120, getPosition().x + player.getPosX(), getPosition().y + player.getPosY());
    newBullet.setFillColor(sf::Color::Red);

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

void Enemy::spin(Player player)
{
    sf::Vector2i flip;
    if (player.getPosition().x < getPosition().x)
    {
        flip.x = 180;
    }

    if (player.getPosition().y < getPosition().y)
    {
        flip.y = 180;
    }

    if (player.getPosition().x != getPosition().x)
    {
        gunLine.setRotation(atan((player.getPosition().y - getPosition().y)
            / (player.getPosition().x - getPosition().x)) * 45 / atan(1) + flip.x);
    }
    //preventing division by 0
    else
    {
        gunLine.setRotation(90 + flip.y);
    }
}

bool Enemy::bulletCollision(sf::RectangleShape rect)
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
bool Enemy::bulletCollision(sf::CircleShape circ)
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

void Enemy::deathAnim()
{
    if (deathAccel < 60)
    {
        gunLine.rotate(deathAccel++);
    }
}

bool Enemy::isDead()
{
    if (deathAccel >= 60)
    {
        return true;
    }
    return false;
}