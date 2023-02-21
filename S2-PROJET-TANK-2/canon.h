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
	Canon(int m_x, int m_y, Direction m_direction);
	~Canon();
	void bougerCanon(Coordonnee m_coordonnee, Direction m_direction);
	void tirer(bool m_etat);
	void afficher();
	bool getEtatMissile();
	Missile getMissile();
	void moveX(int m_x);
	void moveY(int m_y);
	Coordonnee getCoordonnee();
	Direction getDirection();
};

#endif