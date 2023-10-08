#pragma once
#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include "Player.h"
#include <vector>


class Enemy : public sf::CircleShape
{
public:
	Enemy(sf::RenderWindow&);
	~Enemy();
	//returns the enemy's x value, not the same as its position on the screen
	float getPosX();
	//returns the enemy's y value, not the same as its position on the screen
	float getPosY();
	//creates a new bullet, gives it a direction to go, and adds it to the vector
	void shoot(Player);
	//rotates the enemy to face the player.
	void spin(Player);
	//performs updates to all of the bullets, including 
	//moving and deleting them
	void bulletUpdate(Player);
	//adjusts the enemy's location based on acceleration, which will offset everything
	//else's position on the screen
	void move();

	void dmg(int);
	//adjusts enemy position
	void posUpdate(float, float);
	//draws private sfml members to the window
	void draw(sf::RenderWindow&);
	//returns true if any bullet is colliding with something

	bool bulletCollision(sf::RectangleShape);
	bool bulletCollision(sf::CircleShape);
private:
	bool alive = true;
	int health = 360;
	const float speed = 0.25;
	sf::Vector2f accel;
	sf::RectangleShape gunLine;
	std::vector<Bullet> bullets;
};