#pragma once
#include <SFML/Graphics.hpp>

class Bullet : public sf::CircleShape
{
public:
	Bullet(float, float);
	~Bullet();
	void move();
	void setRise(float);
	void setRun(float);
private:
	sf::Vector2f pos;
	bool active = true;
	float rise = 0, run = 0;
};