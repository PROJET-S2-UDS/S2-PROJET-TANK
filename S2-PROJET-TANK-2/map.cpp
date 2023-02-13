#include "map.h"

Map::Map()
{
	taille = 20;
	map = new std::string*[20];
	for (int i = 0; i < 20; i++)
	{
		map[i] = new std::string[20];
	}
	genererMap();
}

Map::Map(int m_taille) {
	taille = m_taille;
	map = new std::string * [m_taille];
	for (int i = 0; i < m_taille; i++)
	{
		map[i] = new std::string[m_taille];
	}
	genererMap();
}

void Map::afficheMap()
{
	for (int i = 0; i < taille; i++)
	{
		for (int z = 0; z < taille; z++)
		{
			std::cout << map[i][z];
		}
		std::cout << std::endl;
	}
}

void Map::ajouter(Tank& m_tank)
{
	bool positionnementReussi = false;
	bool XorY = true;
	int tankX = m_tank.getCoordonnee().x;
	int tankY = m_tank.getCoordonnee().y;
	while (positionnementReussi == false)
	{
		if (map[tankX][tankY] == " ") {
			map[tankX][tankY] = "~";
			m_tank.setCoordonnee(tankX, tankY);
			positionnementReussi = true;
		}
		else {
			if (XorY) {
				tankX += 1;
				XorY = false;
			}
			else
			{
				tankY += 1;
				XorY = true;
			}
		}
	}
}

void Map::retirer()
{

}

void Map::deplacer(Tank& m_tank, std::string m_keyPress)
{
	if (m_keyPress == "W" && map[m_tank.getCoordonnee().x - 1][m_tank.getCoordonnee().y] == " ") {
		map[m_tank.getCoordonnee().x][m_tank.getCoordonnee().y] = " ";
		m_tank.moveX(-1);
		map[m_tank.getCoordonnee().x][m_tank.getCoordonnee().y] = "~";
	}
	else if (m_keyPress == "S" && map[m_tank.getCoordonnee().x + 1][m_tank.getCoordonnee().y] == " ") {
		map[m_tank.getCoordonnee().x][m_tank.getCoordonnee().y] = " ";
		std::cout << m_tank.getCoordonnee().x << m_tank.getCoordonnee().y;
		m_tank.moveX(1);
		map[m_tank.getCoordonnee().x][m_tank.getCoordonnee().y] = "~";
		std::cout << m_tank.getCoordonnee().x << m_tank.getCoordonnee().y;
	}
	else if (m_keyPress == "A" && map[m_tank.getCoordonnee().x][m_tank.getCoordonnee().y - 1] == " ") {
		map[m_tank.getCoordonnee().x][m_tank.getCoordonnee().y] = " ";
		m_tank.moveY(-1);
		map[m_tank.getCoordonnee().x][m_tank.getCoordonnee().y] = "~";
	}
	else if (m_keyPress == "D" && map[m_tank.getCoordonnee().x][m_tank.getCoordonnee().y + 1] == " ") {
		map[m_tank.getCoordonnee().x][m_tank.getCoordonnee().y] = " ";
		m_tank.moveY(1);
		map[m_tank.getCoordonnee().x][m_tank.getCoordonnee().y] = "~";
	}
}

void Map::genererMap() 
{
	int index = 0;
	//Générer les bordures de la map
	for (int i = 0; i < taille; i++)
	{
		for (int z = 0; z < taille; z++)
		{
			map[i][z] = " ";
			if (i == 0) {
				map[i][z] = "#";
			}
			if (i == taille - 1) {
				map[i][z] = "#";
			}
			if (z == 0) {
				map[i][z] = "#";
			}
			if (z == taille - 1) {
				map[i][z] = "#";
			}
			index++;
		}
	}
}
