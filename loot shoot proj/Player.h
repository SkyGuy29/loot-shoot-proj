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
	void shoot();
	void spin(sf::RenderWindow&);
	void move();
	void draw(sf::RenderWindow&);
private:
	sf::RectangleShape gunLine;
	//gun numbah to determine what gun, comes later tho
	std::vector<Bullet> bullets;
};

