#pragma once
#include <SFML/Graphics.hpp>

class Bullet : public sf::CircleShape
{
public:
	Bullet(float, float);
	Bullet(float, float, float);
	Bullet(float, float, sf::Color);
	Bullet(float, float, float, sf::Color);
	~Bullet();
	void move();
	void setRise(float);
	void setRun(float);
	sf::Clock clock;
private:
	sf::Vector2f pos;
	bool active = true;
	float rise = 0, run = 0;
};