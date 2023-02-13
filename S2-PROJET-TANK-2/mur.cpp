#include "mur.h"

Mur::Mur()
{
}

Mur::~Mur()
{
}

Coordonnee Mur::getCoordonnee()
{
	return coordonnee;
}

int Mur::getLongueur()
{
	return longueur;
}

Direction Mur::getDirection()
{
	return direction;
}

Mur::Mur(int m_x, int m_y, int m_longeur, Direction m_direction)
{
	coordonnee.x = m_x;
	coordonnee.y = m_y;
	longueur = m_longeur;
	direction = m_direction;
}