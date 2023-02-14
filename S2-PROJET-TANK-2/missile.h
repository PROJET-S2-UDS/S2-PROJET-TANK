#pragma once
#include <iostream>

#include "munition.h"
#include "coordonnee.h"
#include "direction.h"
#ifndef MISSILE_H
#define MISSILE_H

class Missile : public Munition
{
public:
	Missile();
	Missile(Coordonnee m_coordonnee, Direction m_direction);
	~Missile();
};

#endif


