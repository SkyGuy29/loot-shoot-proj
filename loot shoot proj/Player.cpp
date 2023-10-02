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

bool Player::isTouching(sf::RectangleShape rect)
{
    //if the distance between one of the four corners is less than the radius of the circle
    //OR if one of the corners of the circle is within the boundaries of the rectangle,
    //return true.
    //i am deeply sorry for my awful line indenting, but this is absolutly unreadable otherwise.
    //this makes it at least barely managable.
    if ((sqrt(pow(rect.getGlobalBounds().top - getOrigin().y, 2) + pow(rect.getGlobalBounds().left - getOrigin().x, 2)) < getRadius()
            || sqrt(pow(rect.getGlobalBounds().top - getOrigin().y, 2) + pow(rect.getGlobalBounds().left + rect.getGlobalBounds().width - getOrigin().x, 2)) < getRadius() 
            || sqrt(pow(rect.getGlobalBounds().top + rect.getGlobalBounds().height - getOrigin().y, 2) + pow(rect.getGlobalBounds().left - getOrigin().x, 2)) < getRadius() 
            || sqrt(pow(rect.getGlobalBounds().top + rect.getGlobalBounds().height - getOrigin().y, 2) + pow(rect.getGlobalBounds().left + rect.getGlobalBounds().width - getOrigin().x, 2)) < getRadius())
        || (getOrigin().x - getRadius() > rect.getGlobalBounds().left
            && getOrigin().x - getRadius() < rect.getGlobalBounds().left + rect.getGlobalBounds().width
            && getOrigin().y > rect.getGlobalBounds().top
            && getOrigin().y < rect.getGlobalBounds().top + rect.getGlobalBounds().height)
        || (getOrigin().x + getRadius() > rect.getGlobalBounds().left
            && getOrigin().x + getRadius() < rect.getGlobalBounds().left + rect.getGlobalBounds().width
            && getOrigin().y > rect.getGlobalBounds().top
            && getOrigin().y < rect.getGlobalBounds().top + rect.getGlobalBounds().height)
        || (getOrigin().x > rect.getGlobalBounds().left
            && getOrigin().x < rect.getGlobalBounds().left + rect.getGlobalBounds().width
            && getOrigin().y - getRadius() > rect.getGlobalBounds().top
            && getOrigin().y - getRadius() < rect.getGlobalBounds().top + rect.getGlobalBounds().height)
        || (getOrigin().x > rect.getGlobalBounds().left
            && getOrigin().x < rect.getGlobalBounds().left + rect.getGlobalBounds().width
            && getOrigin().y + getRadius() > rect.getGlobalBounds().top
            && getOrigin().y + getRadius() < rect.getGlobalBounds().top + rect.getGlobalBounds().height))
    {
        return true;
    }

    return false;
}
bool Player::isTouching(sf::CircleShape circ)
{
    //if the distance between the center of the two circles is less than the
    //sum of both radii of the circles, return true
    if (atan(abs(getOrigin().y - circ.getOrigin().y) / abs(getOrigin().x 
        - circ.getOrigin().x)) < getRadius() + circ.getRadius())
    {
        return true;
    }

    return false;
}

void Player::shoot()
{

}

void Player::spin(sf::RenderWindow& window)
{
    //SFML is bugged apperantly so i cant do 
    //sf::Mouse::getPosition(window).x - window.getSize().x / 2.0
    //for some reason
    const float numX = window.getSize().x / 2.0, 
        numY = window.getSize().y / 2.0;

    //ima be honest real quick i do not understand why this works
    //but it does so idc lol
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

void Player::move()
{

}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(gunLine);
    //draw the bullets too once that is coded
}