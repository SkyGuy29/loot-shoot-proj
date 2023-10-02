#include "CollisionCirc.h"


bool CollisionCirc::isTouching(sf::RectangleShape rect)
{
    //if the distance between one of the four corners is less than the radius of the circle
    //OR if one of the corners of the circle is within the boundaries of the rectangle,
    //return true.
    //i am deeply sorry for my awful line indenting, but this is absolutly unreadable otherwise.
    //this makes it at least barely managable.
    if ((sqrt(pow(rect.getGlobalBounds().top - getPosition().y, 2) + pow(rect.getGlobalBounds().left - getPosition().x, 2)) < getRadius() //top left corner of rect
        || sqrt(pow(rect.getGlobalBounds().top - getPosition().y, 2) + pow(rect.getGlobalBounds().left + rect.getGlobalBounds().width - getPosition().x, 2)) < getRadius() //top right corner of rect
        || sqrt(pow(rect.getGlobalBounds().top + rect.getGlobalBounds().height - getPosition().y, 2) + pow(rect.getGlobalBounds().left - getPosition().x, 2)) < getRadius() //bottom left corner of rect
        || sqrt(pow(rect.getGlobalBounds().top + rect.getGlobalBounds().height - getPosition().y, 2) + pow(rect.getGlobalBounds().left + rect.getGlobalBounds().width - getPosition().x, 2)) < getRadius()) //bottom right
        || (getPosition().x - getRadius() > rect.getGlobalBounds().left //west circle corner
            && getPosition().x - getRadius() < rect.getGlobalBounds().left + rect.getGlobalBounds().width
            && getPosition().y > rect.getGlobalBounds().top
            && getPosition().y < rect.getGlobalBounds().top + rect.getGlobalBounds().height)
        || (getPosition().x + getRadius() > rect.getGlobalBounds().left //east circle corner
            && getPosition().x + getRadius() < rect.getGlobalBounds().left + rect.getGlobalBounds().width
            && getPosition().y > rect.getGlobalBounds().top
            && getPosition().y < rect.getGlobalBounds().top + rect.getGlobalBounds().height) 
        || (getPosition().x > rect.getGlobalBounds().left //north circle corner
            && getPosition().x < rect.getGlobalBounds().left + rect.getGlobalBounds().width
            && getPosition().y - getRadius() > rect.getGlobalBounds().top
            && getPosition().y - getRadius() < rect.getGlobalBounds().top + rect.getGlobalBounds().height)
        || (getPosition().x > rect.getGlobalBounds().left //south circle corner
            && getPosition().x < rect.getGlobalBounds().left + rect.getGlobalBounds().width
            && getPosition().y + getRadius() > rect.getGlobalBounds().top
            && getPosition().y + getRadius() < rect.getGlobalBounds().top + rect.getGlobalBounds().height))
    {
        return true;
    }

    return false;
}
bool CollisionCirc::isTouching(sf::CircleShape circ)
{
    //if the distance between the center of the two circles is less than the
    //sum of both radii of the circles, return true
    if (sqrt(pow(getPosition().y - circ.getPosition().y, 2) + pow(getPosition().x
        - circ.getPosition().x, 2)) < getRadius() + circ.getRadius())
    {
        return true;
    }

    return false;
}