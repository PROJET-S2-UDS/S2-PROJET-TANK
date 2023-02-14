#pragma once

#include <iostream>
#include "coordonnee.h"
#include "direction.h"

#ifndef MUR_H
#define MUR_H

class Mur
{
private:
	Coordonnee coordonnee;
	int longueur;
	Direction direction;
public:
	Mur(int m_x, int m_y, int m_longeur, Direction m_direction);
	Mur();
	~Mur();
	Coordonnee getCoordonnee();
	int getLongueur();
	Direction getDirection();
};

#endif