#pragma once
#include <SFML/graphics.hpp>


class CollisionCirc : public sf::CircleShape
{
public:
	bool isTouching(sf::RectangleShape);
	bool isTouching(sf::CircleShape);
protected:
	sf::Vector2f pos;
};

