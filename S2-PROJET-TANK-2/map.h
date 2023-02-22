#pragma once

#include <iostream>
#include <vector>
#include <thread>
#include <windows.h>

#include "tank.h"
#include "mur.h"
#include "tankEnnemie.h"

#ifndef MAP_H
#define MAP_H

class Map
{
private:
	std::string** map;
	int taille;
	int nombreEnnemie;
	std::vector<Missile*>* missilles;
	std::vector<TankEnnemie*>* tanks;
	void genererMap();
	void SpawnMissile(Tank* m_tank);
	void degatEnnemie(Missile* m_missile);
	void retirer(int index);
public:
	Map();
	Map(int m_taille, int m_nombreEnnemie);
	void afficheMap(std::ostream& o, Tank* m_tank);
	void ajouter(Tank* m_tank);
	void deplacer(Tank* m_tank, std::string m_keyPress);
	void ajoutMur(Mur* mur[], int m_taille);
	void deplacerCanon(Tank* m_tank, std::string m_keyPress, int m_value);
	void deplacementMissileAffichage();
	void spawnTankEnnemie(int m_nombreEnnemie, int m_degat, int m_health, Tank* m_tank);
};

#endif