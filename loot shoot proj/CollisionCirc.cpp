#include "CollisionCirc.h"


bool CollisionCirc::isTouching(sf::RectangleShape rect)
{
    //if the distance between one of the four corners is less than the radius of the circle
    //OR if one of the corners of the circle is within the boundaries of the rectangle,
    //return true.
    //i am deeply sorry for my awful line indenting, but this is absolutly unreadable otherwise.
    //this makes it at least barely managable.
    if ((hypot(rect.getGlobalBounds().top - getPosition().y, rect.getGlobalBounds().left - getPosition().x) //top left corner of rect
        || hypot(rect.getGlobalBounds().top - getPosition().y, rect.getGlobalBounds().left + rect.getGlobalBounds().width - getPosition().x) < getRadius() //top right corner of rect
        || hypot(rect.getGlobalBounds().top + rect.getGlobalBounds().height - getPosition().y, rect.getGlobalBounds().left - getPosition().x) < getRadius() //bottom left corner of rect
        || hypot(rect.getGlobalBounds().top + rect.getGlobalBounds().height - getPosition().y, rect.getGlobalBounds().left + rect.getGlobalBounds().width - getPosition().x) < getRadius()) //bottom right
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
    if (hypot(getPosition().y - circ.getPosition().y, getPosition().x
        - circ.getPosition().x) < getRadius() + circ.getRadius())
    {
        return true;
    }

    return false;
}