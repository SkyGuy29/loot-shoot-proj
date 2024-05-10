#pragma once
#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include <vector>


class Player : public sf::CircleShape
{
public:
	Player(sf::RenderWindow&);
	~Player();
	//returns the player's x value, not the same as its position on the screen
	float getPosX();
	//returns the player's y value, not the same as its position on the screen
	float getPosY();
	//creates a new bullet, gives it a direction to go, and adds it to the vector
	void shoot();
	//rotates the player to face the cursor. needs to be called repeatedly to
	//lock it onto the mouse
	void spin(sf::RenderWindow&);
	//performs updates to all of the bullets, including 
	//moving and deleting them
	void bulletUpdate();
	//adjusts the player's location based on acceleration, which will offset everything
	//else's position on the screen
	void move();
	//draws private sfml members to the window
	void draw(sf::RenderWindow&);
	//returns true if any bullet is colliding with something
	bool bulletCollision(sf::RectangleShape);
	bool bulletCollision(sf::CircleShape);
	//returns the damage of the bullet that is coliding with the enemy
	int hitEnemy(sf::CircleShape);
private:
	const float SPEED = 0.5;
	sf::Vector2f pos, vel;
	sf::RectangleShape gunLine;
	//gun enum to determine what gun, comes later tho
	std::vector<Bullet> bullets;
};