#include "Bullet.h"
#include "Player.h"

Bullet::Bullet(float startX, float startY)
{
	setRadius(8.f);
	setFillColor(sf::Color::Cyan);
	setOrigin(getRadius(), getRadius());
	setPosition(startX, startY); //this is temp
	pos = getPosition();
}

Bullet::~Bullet()
{

}

void Bullet::move()
{
	pos.x += run;
	pos.y += rise;
	setPosition(pos.x + run, pos.y + rise);
}

void Bullet::setRise(float newRise)
{
	rise = newRise;
}

void Bullet::setRun(float newRun)
{
	run = newRun;
}