#pragma once

#include <iostream>
#include <vector>
#include <thread>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <mutex>

#include "tank.h"
#include "mur.h"
#include "tankEnnemie.h"
#include "Manette.hpp"

#ifndef MAP_H
#define MAP_H

class Map
{
private:
	std::string** map;
	int niveau;
	int taille;
	int nombreEnnemie;
	Tank* player;
	std::vector<Missile*>* missilles;
	std::vector<TankEnnemie*>* tanks;
	void genererMap();
	void SpawnMissile(Tank* m_tank);
	void degatEnnemie(Missile* m_missile);
	void retirer(int index);
	void deplacerCanonEnnemie(Tank* m_tank, std::string m_keyPress, int m_value);
	void canonEnnemie();
	void deplacementEnnemie(TankEnnemie* m_tankEnnemie, std::string m_key, int m_x, int m_y);
public:
	Map();
	Map(int m_taille, int m_nombreEnnemie, int m_niveau);
	~Map();
	void afficheMap(std::ostream& o, Tank* m_tank);
	void ajouter(Tank* m_tank);
	void deplacer(Tank* m_tank, std::string m_keyPress);
	void ajoutMur(std::vector<Mur*>, int m_taille);
	void deplacerCanon(Tank* m_tank, std::string m_keyPress, int m_value);
	void deplacementMissileAffichage();
	void spawnTankEnnemie(int m_nombreEnnemie, int m_degat, int m_health, Tank* m_tank);
	std::vector<TankEnnemie*>* getTanks();
	void pathEnnemie();
	Tank* getPlayer();
	int getTaille();
	int getNombreEnnemie();
	int getNiveau();
	void addOneNiveau();
	void generateurMap();
	void killAllTank();
};

#endif