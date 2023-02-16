#include "bombe.h"

Bombe::Bombe()
{
	etat = false;
	degat = 50;
}

Bombe::Bombe(Coordonnee m_coordonnee, int m_degat)
{
	coordonnee = m_coordonnee;
	etat = false;
	degat = m_degat;
}

void Bombe::setCoordonnee(Coordonnee m_coordonnee)
{
	coordonnee = m_coordonnee;
}

bool Bombe::getEtat()
{
	return etat;
}

void Bombe::setEtat(bool m_etat)
{
	etat = m_etat;
}
