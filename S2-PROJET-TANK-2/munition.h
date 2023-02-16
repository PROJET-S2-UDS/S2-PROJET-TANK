#pragma once

#include "coordonnee.h"
#include "direction.h"

#ifndef MUNITION_H
#define MUNITION_H


class Munition
{
protected:
	Coordonnee coordonnee;
	Direction direction;
	int degat;
public:
	virtual Coordonnee getCoordonnee();
	virtual Direction getDirection();
	virtual void setPosition(int m_x, int m_y, Direction m_direction);
	virtual void setDegat(int m_degat);
	virtual int getDegat();
};

#endif
