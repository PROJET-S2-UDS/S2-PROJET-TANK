#include "canon.h"

Canon::Canon()
{
}

Canon::Canon(int m_x, int m_y, Direction m_direction, Missile m_missile)
{
	coordonnee.x = m_x;
	coordonnee.y = m_y;
	direction = m_direction;
	missile = m_missile;
}

Canon::~Canon()
{
}

void Canon::bougerCanon(Coordonnee coordonnee, Direction direction)
{

}

bool Canon::tirer()
{
	missile.getCoordonnee();
	return true;
}

void Canon::afficher()
{
}
