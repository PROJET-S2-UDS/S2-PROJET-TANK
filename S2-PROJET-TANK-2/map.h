#pragma once

#include <iostream>

#include "tank.h"

#ifndef MAP_H
#define MAP_H

class Map
{
private:
	std::string** map;
	int taille;
	void genererMap();

public:
	Map();
	Map(int m_taille);
	void afficheMap();
	void ajouter(Tank& m_tank);
	void retirer();
	void deplacer(Tank& m_tank, std::string m_keyPress);
};

#endif