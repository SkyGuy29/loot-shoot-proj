#pragma once
#include <SFML/Graphics.hpp>
#include "CollisionCirc.h"

class Bullet : public CollisionCirc
{
public:
	Bullet();
	~Bullet();
	void move();
private:
	int rise = 0, run = 0;
};

