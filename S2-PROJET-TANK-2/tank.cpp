#include "tank.h"

Tank::Tank()
{
}

Tank::Tank(std::string m_name, int m_health, int m_x, int m_y, Type m_type)
{
	name = m_name;
	health = m_health;
	coordonnee.x = m_x;
	coordonnee.y = m_y;
	type = m_type;
	bombe.setDegat(50);
}

Tank::~Tank()
{
}

std::string Tank::getName()
{
	return name;
}

int Tank::getHealth()
{
	return health;
}

Coordonnee Tank::getCoordonnee()
{
	return coordonnee;
}

void Tank::setCoordonnee(int m_x, int m_y)
{
	coordonnee.x = m_x;
	coordonnee.y = m_y;
}

Type Tank::getType()
{
	return type;
}

void Tank::setHealth(int m_health)
{
	health = m_health;
}

void Tank::setName(std::string m_name)
{
	name = m_name;
}

bool Tank::shoot()
{
	canon.tirer();
	return false;
}

void Tank::dropBombe(bool m_etat)
{
	bombe.setEtat(m_etat);
}

//Retourne vrai si il reste plus de vie
bool Tank::loseHealth(int m_health)
{
	health -= m_health;
	if (health <= 0) {
		return true;
	}
	return false;
}

void Tank::moveX(int m_x)
{
	coordonnee.x += m_x;
}

void Tank::moveY(int m_y)
{
	coordonnee.y += m_y;
}

bool Tank::getEtatBombe()
{
	return bombe.getEtat();
}

Bombe Tank::getBombe()
{
	return bombe;
}
