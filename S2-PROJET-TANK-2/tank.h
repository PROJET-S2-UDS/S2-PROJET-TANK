#pragma once

#include <string>

#include "coordonnee.h"
#include "canon.h"
#include "bombe.h"
#include "type.h"

#ifndef TANK_H
#define TANK_H

class Tank
{
protected:
	std::string name;
	int health;
	Coordonnee coordonnee;
	Bombe bombe;
	Canon canon;
	Type type;
public:
	Tank();
	Tank(std::string m_name, int m_health, int m_x, int m_y, Type m_type);
	~Tank();
	std::string getName();
	int getHealth();
	Coordonnee getCoordonnee();
	void setCoordonnee(int m_x, int m_y);
	Type getType();
	void setHealth(int m_health);
	void setName(std::string m_name);
	void shoot(bool m_etat);
	void dropBombe(bool m_etat);
	bool loseHealth(int m_health);
	void moveX(int m_x);
	void moveY(int m_y);
	bool getEtatBombe();
	Bombe getBombe();
	bool getEtatMissile();
	Missile getMissile();
	Canon getCanon();
	void setPositionCanon(int m_x, int m_y, Direction m_direction);
	void moveXCanon(int m_x);
	void moveYCanon(int m_y);
};

#endif