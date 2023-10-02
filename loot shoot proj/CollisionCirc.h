#pragma once
#include <SFML/graphics.hpp>


class CollisionCirc : public sf::CircleShape
{
public:
	bool isTouching(sf::RectangleShape);
	bool isTouching(sf::CircleShape);
protected:
	int xPos = 0, yPos = 0;
};

