#include "CollisionCirc.h"


bool CollisionCirc::isTouching(sf::RectangleShape rect)
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
bool CollisionCirc::isTouching(sf::CircleShape circ)
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