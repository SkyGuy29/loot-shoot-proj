#include "Bullet.h"
#include "Player.h"

Bullet::Bullet(int dmg, float startX, float startY)
{
	setRadius(8.f);
	setFillColor(sf::Color::Cyan);
	setOrigin(getRadius(), getRadius());
	setPosition(startX, startY);
	pos = getPosition();
	damage = dmg;
}

Bullet::Bullet(int dmg, sf::Vector2f start)
{
	setRadius(8.f);
	setFillColor(sf::Color::Cyan);
	setOrigin(getRadius(), getRadius());
	setPosition(start);
	pos = getPosition();
	damage = dmg;
}

Bullet::Bullet(int dmg, float startX, float startY, float rad)
{
	setRadius(rad);
	setFillColor(sf::Color::Cyan);
	setOrigin(getRadius(), getRadius());
	setPosition(startX, startY);
	pos = getPosition();
	damage = dmg;
}

Bullet::Bullet(int dmg, sf::Vector2f start, float rad)
{
	setRadius(rad);
	setFillColor(sf::Color::Cyan);
	setOrigin(getRadius(), getRadius());
	setPosition(start);
	pos = getPosition();
	damage = dmg;
}

Bullet::~Bullet()
{

}

int Bullet::getDamage()
{
	return damage;
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

void Bullet::deactivate()
{
	active = false;
}

bool Bullet::isActive()
{
	return active;
}