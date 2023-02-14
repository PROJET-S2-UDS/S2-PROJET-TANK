#pragma once
#include <iostream>

#include "coordonnee.h"
#include "direction.h"
#include "missile.h"

#ifndef CANON_H
#define CANON_H


class Canon
{
private:
	Coordonnee coordonnee;
	Direction direction;
	Missile missile;
public:
	Canon();
	Canon(int m_x, int m_y, Direction m_direction, Missile m_missile);
	~Canon();
	void bougerCanon(Coordonnee coordonnee, Direction direction);
	bool tirer();
	void afficher();
};

#endif