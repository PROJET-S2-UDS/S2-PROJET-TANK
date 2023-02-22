#pragma once
#include<iostream>

#include "tank.h";

#ifndef TANKENNEMIE_H
#define TANKENNEMIE_H

class TankEnnemie: public Tank
{
private:
	Tank* target;
public:
	TankEnnemie();
	TankEnnemie(Tank* m_target, std::string m_name, int m_health, int m_x, int m_y, Type m_type);
	~TankEnnemie();
	void setTarget(Tank* m_target);
	Tank* getTarget();
};

#endif
