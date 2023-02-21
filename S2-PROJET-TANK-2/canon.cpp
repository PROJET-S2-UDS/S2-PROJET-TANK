#include "canon.h"

Canon::Canon()
{
}

Canon::Canon(int m_x, int m_y, Direction m_direction)
{
	coordonnee.x = m_x;
	coordonnee.y = m_y;
	direction = m_direction;
}

Canon::~Canon()
{
}

void Canon::bougerCanon(Coordonnee m_coordonnee, Direction m_direction)
{
	coordonnee = m_coordonnee;
	direction = m_direction;
}

void Canon::tirer(bool m_etat)
{
	missile.setEtat(m_etat);
}

void Canon::afficher()
{
}

bool Canon::getEtatMissile()
{
	return missile.getEtat();
}

Missile Canon::getMissile()
{
	return Missile();
}

void Canon::moveX(int m_x)
{
	coordonnee.x += m_x;
}

void Canon::moveY(int m_y)
{
	coordonnee.y = m_y;
}

Coordonnee Canon::getCoordonnee()
{
	return coordonnee;
}

Direction Canon::getDirection()
{
	return direction;
}
