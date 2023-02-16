#pragma once
#include "munition.h"

#ifndef BOMBE_H
#define BOME_H

class Bombe : public Munition
{
private:
	bool etat;
public:
	Bombe();
	Bombe(Coordonnee m_coordonnee, int m_degat);
	void setCoordonnee(Coordonnee m_coordonnee);
	bool getEtat();
	void setEtat(bool m_etat);
};

#endif
