#pragma once
#include <SFML/Graphics.hpp>
#include "CollisionCirc.h"
#include "Bullet.h"
#include <vector>


class Player : public CollisionCirc
{
public:
	Player(sf::RenderWindow&);
	~Player();
	//creates a new bullet, gives it a direction to go, and adds it to the vector
	void shoot();
	//rotates the player to face the cursor. needs to be called repeatedly to
	//lock it onto the mouse
	void spin(sf::RenderWindow&);
	//performs updates to all of the bullets, including 
	//moving and deleting them
	void bulletUpdate();
	//adjusts the player's location, which will offset everything
	//else's position on the screen
	void move();
	//draws private sfml members to the window
	void draw(sf::RenderWindow&);
	//returns true if any bullet is colliding with something
	bool bulletCollision(sf::RectangleShape);
	bool bulletCollision(sf::CircleShape);
private:
	sf::RectangleShape gunLine;
	//gun numb to determine what gun, comes later tho
	std::vector<Bullet> bullets;
};