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
private:
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
	bool shoot();
	bool dropBombe();
	bool loseHealth(int m_health);
	void moveX(int m_x);
	void moveY(int m_y);
};

#endif