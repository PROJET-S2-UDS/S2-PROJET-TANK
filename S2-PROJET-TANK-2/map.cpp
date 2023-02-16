#include "map.h"
#include "mur.h"


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

void Map::afficheMap(std::ostream& o, Tank* m_tank)
{
	o.clear();
	o << "X: " << m_tank->getCoordonnee().x << " Y: " << m_tank->getCoordonnee().y << std::endl;
	o << "Vie : " << m_tank->getHealth() << "  " << std::endl;
	for (int i = 0; i < taille; i++)
	{
		for (int z = 0; z < taille; z++)
		{
			o << map[i][z];
		}
		o << std::endl;
	}
}

void Map::ajouter(Tank* m_tank)
{
	bool positionnementReussi = false;
	bool XorY = true;
	int tankX = m_tank->getCoordonnee().x;
	int tankY = m_tank->getCoordonnee().y;
	while (positionnementReussi == false)
	{
		if (map[tankX][tankY] == " ") {
			map[tankX][tankY] = "~";
			m_tank->setCoordonnee(tankX, tankY);
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

void Map::deplacer(Tank* m_tank, std::string m_keyPress)
{
	Coordonnee coordonnee = m_tank->getCoordonnee();
	if (m_keyPress == "W" && map[m_tank->getCoordonnee().x - 1][m_tank->getCoordonnee().y] != "#") {
		if (map[m_tank->getCoordonnee().x - 1][m_tank->getCoordonnee().y] == "!") {
			m_tank->loseHealth(m_tank->getBombe().getDegat());
		}
		map[m_tank->getCoordonnee().x][m_tank->getCoordonnee().y] = " ";
		m_tank->moveX(-1);
		map[m_tank->getCoordonnee().x][m_tank->getCoordonnee().y] = "~";
	}
	else if (m_keyPress == "S" && map[m_tank->getCoordonnee().x + 1][m_tank->getCoordonnee().y] != "#") {
		if (map[m_tank->getCoordonnee().x + 1][m_tank->getCoordonnee().y] == "!") {
			m_tank->loseHealth(m_tank->getBombe().getDegat());
		}
		map[m_tank->getCoordonnee().x][m_tank->getCoordonnee().y] = " ";
		m_tank->moveX(1);
		map[m_tank->getCoordonnee().x][m_tank->getCoordonnee().y] = "~";
	}
	else if (m_keyPress == "A" && map[m_tank->getCoordonnee().x][m_tank->getCoordonnee().y - 1] != "#") {
		if (map[m_tank->getCoordonnee().x][m_tank->getCoordonnee().y - 1] == "!") {
			m_tank->loseHealth(m_tank->getBombe().getDegat());
		}
		map[m_tank->getCoordonnee().x][m_tank->getCoordonnee().y] = " ";
		m_tank->moveY(-1);
		map[m_tank->getCoordonnee().x][m_tank->getCoordonnee().y] = "~";
	}
	else if (m_keyPress == "D" && map[m_tank->getCoordonnee().x][m_tank->getCoordonnee().y + 1] != "#") {
		if (map[m_tank->getCoordonnee().x][m_tank->getCoordonnee().y + 1] == "!") {
			m_tank->loseHealth(m_tank->getBombe().getDegat());
		}
		map[m_tank->getCoordonnee().x][m_tank->getCoordonnee().y] = " ";
		m_tank->moveY(1);
		map[m_tank->getCoordonnee().x][m_tank->getCoordonnee().y] = "~";
	}
	if (m_tank->getEtatBombe()) {
		map[coordonnee.x][coordonnee.y] = "!";
		m_tank->dropBombe(false);
	}
}

void Map::ajoutMur(Mur* mur[], int m_taille)
{
	for (int i = 0; i < m_taille; i++)
	{
		for (int z = 0; z < mur[i]->getLongueur(); z++)
		{
			if ((mur[i]->getCoordonnee().x + z) < taille  && (mur[i]->getCoordonnee().y + z) < taille) {
				if (mur[i]->getDirection() == Direction::Haut)
				{
					map[mur[i]->getCoordonnee().x + z][mur[i]->getCoordonnee().y] = "#";
				}
				else if (mur[i]->getDirection() == Direction::Bas) {
					map[mur[i]->getCoordonnee().x - z][mur[i]->getCoordonnee().y] = "#";
				}
				else if (mur[i]->getDirection() == Direction::Gauche) {
					map[mur[i]->getCoordonnee().x][mur[i]->getCoordonnee().y - z] = "#";
				}
				else if (mur[i]->getDirection() == Direction::Droit) {
					map[mur[i]->getCoordonnee().x][mur[i]->getCoordonnee().y + z] = "#";
				}
			}
		}
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
