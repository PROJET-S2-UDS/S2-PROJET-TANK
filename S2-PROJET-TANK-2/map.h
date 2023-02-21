#pragma once

#include <iostream>
#include <vector>
#include <thread>
#include <windows.h>

#include "tank.h"
#include "mur.h"

#ifndef MAP_H
#define MAP_H

class Map
{
private:
	std::string** map;
	int taille;
	void genererMap();
	void SpawnMissile(Tank* m_tank);
	std::vector<Missile>* missilles;
public:
	Map();
	Map(int m_taille);
	void afficheMap(std::ostream& o, Tank* m_tank);
	void ajouter(Tank* m_tank);
	void retirer();
	void deplacer(Tank* m_tank, std::string m_keyPress);
	void ajoutMur(Mur* mur[], int m_taille);
	void deplacerCanon(Tank* m_tank, std::string m_keyPress, int m_value);
	void deplacementMissileAffichage();
};

#endif