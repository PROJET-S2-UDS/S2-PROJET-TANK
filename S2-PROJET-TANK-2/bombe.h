#pragma once
#include "munition.h"

#ifndef BOMBE_H
#define BOME_H

class Bombe : public Munition
{
public:
	Bombe();
	Bombe(Coordonnee m_coordonnee, int m_degat);
	void setCoordonnee(Coordonnee m_coordonnee);
};

#endif
