#pragma once
#include <SFML/Graphics.hpp>


class Player : public sf::CircleShape
{
public:
	Player(sf::RenderWindow&);
	~Player();
	bool isTouching(sf::RectangleShape);
	bool isTouching(sf::CircleShape);
	void shoot();
	void spin(sf::RenderWindow&);
	void move();
	void draw(sf::RenderWindow&);
private:
	sf::RectangleShape gunLine;
	//gun numbah to determine what gun, comes later tho
	//bullet object
	int xPos = 0, yPos = 0;
};

