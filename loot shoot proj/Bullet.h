#pragma once
#include <SFML/Graphics.hpp>

class Bullet : public sf::CircleShape
{
public:
	Bullet(int, float, float);
	Bullet(int, sf::Vector2f);
	Bullet(int, float, float, float);
	Bullet(int, sf::Vector2f, float);
	~Bullet();
	int getDamage();
	void move();
	void setRise(float);
	void setRun(float);
	void deactivate();
	bool isActive();
	sf::Clock clock;
private:
	sf::Vector2f pos;
	int damage = 0;
	bool active = true;
	float rise = 0, run = 0;
};