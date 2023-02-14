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
