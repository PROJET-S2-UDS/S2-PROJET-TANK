#include "missile.h"

Missile::Missile()
{
	degat = 20;
	etat = false;
}

Missile::Missile(Coordonnee m_coordonnee, Direction m_direction, int m_degat)
{
	coordonnee = m_coordonnee;
	direction = m_direction;
	degat = m_degat;
	etat = true;
}

Missile::~Missile()
{
}

void Missile::moveX(int m_x)
{
	coordonnee.x += m_x;
}

void Missile::moveY(int m_y)
{
	coordonnee.y += m_y;
}
