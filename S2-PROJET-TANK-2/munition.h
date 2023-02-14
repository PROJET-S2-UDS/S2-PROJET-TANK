#pragma once

#include "coordonnee.h"
#include "direction.h"

#ifndef MUNITION_H
#define MUNITION_H


class Munition
{
private:
	Coordonnee coordonnee;
	Direction direction;
public:
	virtual Coordonnee getCoordonnee();
	virtual Direction getDirection();
	virtual void setPosition(int m_x, int m_y, Direction m_direction);
};

#endif
