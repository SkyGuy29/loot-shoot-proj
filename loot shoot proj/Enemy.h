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
	//creates a new bullet, gives it a direction to go, and adds it to the vector
	void shoot(Player);
	//rotates the enemy to face the player.
	void spin(Player);
	//performs updates to all of the bullets, including 
	//moving and deleting them
	void bulletUpdate(Player);
	//adjusts the enemy's location based on acceleration
	void move();
	//damages the enemy's health
	void dmg(int);
	//adjusts enemy position
	void posUpdate(float, float);
	//draws private sfml members to the window
	void draw(sf::RenderWindow&);
	//returns true if any bullet is colliding with something

	bool bulletCollision(sf::RectangleShape);
	bool bulletCollision(sf::CircleShape);
protected:
	bool alive = true;
	int health = 360;
	const float speed = 0.25;
	sf::Vector2f accel;
	sf::RectangleShape gunLine;
	std::vector<Bullet> bullets;
};