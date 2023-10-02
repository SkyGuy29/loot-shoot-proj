#include "Bullet.h"

Bullet::Bullet()
{

}

Bullet::~Bullet()
{

}

void Bullet::move()
{
	yPos += rise;
	xPos += run;
}