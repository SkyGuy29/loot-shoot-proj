#include "Bullet.h"

Bullet::Bullet()
{
	setRadius(8.f);
	setFillColor(sf::Color::Cyan);
	setOrigin(getRadius(), getRadius());
	setPosition(640, 360); //this is temp
}

Bullet::~Bullet()
{

}

void Bullet::move()
{
	pos.x += rise;
	pos.y += run;
	setPosition(getPosition().x + run, getPosition().y + rise);
}

void Bullet::setRise(float newRise)
{
	rise = newRise;
}

void Bullet::setRun(float newRun)
{
	run = newRun;
}