#include "munition.h"

Coordonnee Munition::getCoordonnee()
{
	return coordonnee;
}

Direction Munition::getDirection()
{
	return direction;
}

void Munition::setPosition(int m_x, int m_y, Direction m_direction)
{
	coordonnee.x = m_x;
	coordonnee.y = m_y;
	direction = m_direction;
}

void Munition::setDegat(int m_degat)
{
	degat = m_degat;
}

int Munition::getDegat()
{
	return degat;
}
