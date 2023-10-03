#pragma once
#include <SFML/Graphics.hpp>
#include "CollisionCirc.h"

class Bullet : public CollisionCirc
{
public:
	Bullet();
	~Bullet();
	void move();
	void setRise(float);
	void setRun(float);
private:
	bool active = true;
	float rise = 0, run = 0;
};