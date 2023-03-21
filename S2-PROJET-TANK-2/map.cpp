#include "map.h"
#include "mur.h"

int rayonEnnemie = 8;

Map::Map()
{
	niveau = 1;
	taille = 20;
	nombreEnnemie = 5;
	map = new std::string*[20];
	missilles = new std::vector<Missile*>;
	tanks = new std::vector<TankEnnemie*>;
	player = NULL;
	for (int i = 0; i < 20; i++)
	{
		map[i] = new std::string[20];
	}
	genererMap();
}

Map::Map(int m_taille, int m_nombreEnnemie, int m_niveau) {
	niveau = m_niveau;
	taille = m_taille;
	nombreEnnemie = m_nombreEnnemie;
	map = new std::string*[m_taille];
	missilles = new std::vector<Missile*>;
	tanks = new std::vector<TankEnnemie*>;
	player = NULL;
	for (int i = 0; i < m_taille; i++)
	{
		map[i] = new std::string[m_taille];
	}
	genererMap();
}

Map::~Map()
{
	tanks->clear();
	missilles->clear();
	tanks = nullptr;
	missilles = nullptr;
	player = nullptr;
	delete map;
}



void Map::afficheMap(std::ostream& o, Tank* m_tank)
{
	o.clear();
	o << "X: " << m_tank->getCoordonnee().x << " Y: " << m_tank->getCoordonnee().y << "  " << std::endl;
	o << "Vie : " << m_tank->getHealth() << "  " << std::endl;
	o << "Niveau: " << niveau << std::endl;
	for (int i = 0; i < taille; i++)
	{
		for (int z = 0; z < taille; z++)
		{
			//std::printf("Salur");
			std::cout << map[i][z];
		}
		std::cout << std::endl;
	}
	SpawnMissile(m_tank);
}

void Map::ajouter(Tank* m_tank)
{
	bool positionnementReussi = false;
	bool positionnementReussiCanon = false;
	bool XorY = true;
	int tankX = m_tank->getCoordonnee().x;
	int tankY = m_tank->getCoordonnee().y;
	Coordonnee coordonneeCanon = m_tank->getCanon().getCoordonnee();
	while (!positionnementReussi)
	{
		if (tankX < 0) {
			tankX = 0;
		}
		if (tankY < 0) {
			tankY = 0;
		}
		if (tankX >= taille) {
			tankX = taille - 1;
		}
		if (tankY >= taille) {
			tankY = taille - 1;
		}
		if (map[tankX][tankY] == " ") {
			map[tankX][tankY] = "~";
			m_tank->setCoordonnee(tankX, tankY);
			if (player == NULL) {
				player = m_tank;
			}
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
	while (!positionnementReussiCanon)
	{
		if (map[m_tank->getCoordonnee().x - 1][m_tank->getCoordonnee().y] == " ") {
			map[m_tank->getCoordonnee().x - 1][m_tank->getCoordonnee().y] = "^";
			coordonneeCanon = m_tank->getCoordonnee();
			coordonneeCanon.x -= 1;
			m_tank->setPositionCanon(coordonneeCanon.x,coordonneeCanon.y, Direction::Haut);
			positionnementReussiCanon = true;
		}
		else if (map[m_tank->getCoordonnee().x + 1][m_tank->getCoordonnee().y] == " ") {
			map[m_tank->getCoordonnee().x + 1][m_tank->getCoordonnee().y] = "^";
			coordonneeCanon = m_tank->getCoordonnee();
			coordonneeCanon.x += 1;
			m_tank->setPositionCanon(coordonneeCanon.x,coordonneeCanon.y, Direction::Bas);
			positionnementReussiCanon = true;
		}
		else if (map[m_tank->getCoordonnee().x][m_tank->getCoordonnee().y - 1] == " ") {
			map[m_tank->getCoordonnee().x + 1][m_tank->getCoordonnee().y - 1] = "<";
			coordonneeCanon = m_tank->getCoordonnee();
			coordonneeCanon.y -= 1;
			m_tank->setPositionCanon(coordonneeCanon.x,coordonneeCanon.y, Direction::Gauche);
			positionnementReussiCanon = true;
		}
		else if (map[m_tank->getCoordonnee().x][m_tank->getCoordonnee().y + 1] == " ") {
			map[m_tank->getCoordonnee().x][m_tank->getCoordonnee().y + 1] = ">";
			coordonneeCanon = m_tank->getCoordonnee();
			coordonneeCanon.y += 1;
			m_tank->setPositionCanon(coordonneeCanon.x, coordonneeCanon.y, Direction::Droit);
			positionnementReussiCanon = true;
		}
	}
}

void Map::retirer(int index)
{
	tanks->erase(tanks->begin() + index);
}

void Map::canonEnnemie() {
	for (int i = 0; i < tanks->size(); i++)
	{
		TankEnnemie* tankEnnemie = tanks->at(i);
		Coordonnee coordonneePlayer = tanks->at(i)->getTarget()->getCoordonnee();
		Coordonnee coordonneeEnnemeie = tanks->at(i)->getCoordonnee();
		bool cheminPlusCourt = false;
		int differenceX = coordonneePlayer.x - coordonneeEnnemeie.x;
		int differenceY = coordonneePlayer.y - coordonneeEnnemeie.y;
		if ((coordonneePlayer.x == coordonneeEnnemeie.x) && std::abs(coordonneePlayer.y - coordonneeEnnemeie.y) <= rayonEnnemie) {
			if ((coordonneePlayer.y - coordonneeEnnemeie.y) < 0) {
				deplacerCanonEnnemie(tankEnnemie, "LEFT", 1);
			}
			else if ((coordonneePlayer.y - coordonneeEnnemeie.y) > 0) {
				deplacerCanonEnnemie(tankEnnemie, "RIGHT", 1);
			}
			tankEnnemie->shoot(true);
			SpawnMissile(tankEnnemie);
		}
		if ((coordonneePlayer.y == coordonneeEnnemeie.y) && std::abs(coordonneePlayer.x - coordonneeEnnemeie.x) <= rayonEnnemie) {
			if ((coordonneePlayer.x - coordonneeEnnemeie.x) < 0) {
				deplacerCanonEnnemie(tankEnnemie, "UP", 1);
			}
			else if ((coordonneePlayer.x - coordonneeEnnemeie.x) > 0) {
				deplacerCanonEnnemie(tankEnnemie, "DOWN", 1);
			}
			tankEnnemie->shoot(true);
			SpawnMissile(tankEnnemie);
		}
	}
}

void Map::pathEnnemie()
{
	for (int i = 0; i < tanks->size(); i++)
	{
		try {
			Sleep(1000);
			canonEnnemie();
			TankEnnemie* tankEnnemie = tanks->at(i);
			Coordonnee coordonneePlayer = tanks->at(i)->getTarget()->getCoordonnee();
			Coordonnee coordonneeEnnemeie = tanks->at(i)->getCoordonnee();
			int differenceX = coordonneePlayer.x - coordonneeEnnemeie.x;
			int differenceY = coordonneePlayer.y - coordonneeEnnemeie.y;
			if (differenceX <= differenceY) {
				if (differenceX < 0) {
					deplacer(tankEnnemie, "W");
				}
				else if (differenceX > 0) {
					deplacer(tankEnnemie, "S");
				}
				else if (differenceY < 0) {
					deplacer(tankEnnemie, "A");
				}
				else if (differenceY > 0) {
					deplacer(tankEnnemie, "D");
				}
			}
			if (differenceX >= differenceY) {
				if (differenceY < 0) {
					deplacer(tankEnnemie, "A");
				}
				else if (differenceY > 0) {
					deplacer(tankEnnemie, "D");
				}
				else if (differenceX < 0) {
					deplacer(tankEnnemie, "W");
				}
				else if (differenceX > 0) {
					deplacer(tankEnnemie, "S");
				}
			}
		}
		catch (const std::out_of_range& oor) {
			i = 0;
		}
	}
}

Tank* Map::getPlayer()
{
	return player;
}

int Map::getTaille()
{
	return taille;
}

int Map::getNombreEnnemie()
{
	return nombreEnnemie;
}

int Map::getNiveau()
{
	return niveau;
}

void Map::addOneNiveau()
{
	niveau += 1;
}

void Map::deplacementEnnemie(TankEnnemie* m_tankEnnemie, std::string m_key, int m_x, int m_y) {
	if (map[m_tankEnnemie->getCoordonnee().x + m_x][m_tankEnnemie->getCoordonnee().y + m_y] == " ") {
		deplacer(m_tankEnnemie, m_key);
	}
	else if (map[m_tankEnnemie->getCoordonnee().x - 1][m_tankEnnemie->getCoordonnee().y] == " ") {
		deplacer(m_tankEnnemie, "W");
	}
	else if (map[m_tankEnnemie->getCoordonnee().x + 1][m_tankEnnemie->getCoordonnee().y] == " ") {
		deplacer(m_tankEnnemie, "S");
	}
	else if (map[m_tankEnnemie->getCoordonnee().x][m_tankEnnemie->getCoordonnee().y - 1] == " ") {
		deplacer(m_tankEnnemie, "A");
	}
	else if (map[m_tankEnnemie->getCoordonnee().x][m_tankEnnemie->getCoordonnee().y + 1] == " ") {
		deplacer(m_tankEnnemie, "D");
	}

}

void Map::deplacerCanonEnnemie(Tank* m_tank, std::string m_keyPress, int m_value)
{
	Coordonnee coordonneTank = m_tank->getCoordonnee();
	if (m_keyPress == "UP" && map[coordonneTank.x - m_value][coordonneTank.y] == " ") {
		map[m_tank->getCanon().getCoordonnee().x][m_tank->getCanon().getCoordonnee().y] = " ";
		m_tank->setPositionCanon(coordonneTank.x - m_value, coordonneTank.y, Direction::Haut);
		map[m_tank->getCanon().getCoordonnee().x][m_tank->getCanon().getCoordonnee().y] = "^";
	}
	if (m_keyPress == "DOWN" && map[coordonneTank.x + m_value][coordonneTank.y] == " ") {
		map[m_tank->getCanon().getCoordonnee().x][m_tank->getCanon().getCoordonnee().y] = " ";
		m_tank->setPositionCanon(coordonneTank.x + m_value, coordonneTank.y, Direction::Bas);
		map[m_tank->getCanon().getCoordonnee().x][m_tank->getCanon().getCoordonnee().y] = "^";
	}
	if (m_keyPress == "LEFT" && map[coordonneTank.x][coordonneTank.y - m_value] == " ") {
		map[m_tank->getCanon().getCoordonnee().x][m_tank->getCanon().getCoordonnee().y] = " ";
		m_tank->setPositionCanon(coordonneTank.x, coordonneTank.y - m_value, Direction::Gauche);
		map[m_tank->getCanon().getCoordonnee().x][m_tank->getCanon().getCoordonnee().y] = "<";
	}
	if (m_keyPress == "RIGHT" && map[coordonneTank.x][coordonneTank.y + m_value] == " ") {
		map[m_tank->getCanon().getCoordonnee().x][m_tank->getCanon().getCoordonnee().y] = " ";
		m_tank->setPositionCanon(coordonneTank.x, coordonneTank.y + m_value, Direction::Droit);
		map[m_tank->getCanon().getCoordonnee().x][m_tank->getCanon().getCoordonnee().y] = ">";
	}
}

void Map::deplacer(Tank* m_tank, std::string m_keyPress)
{
	Coordonnee coordonnee = m_tank->getCoordonnee();
	if (m_keyPress == "W" && map[m_tank->getCoordonnee().x - 1][m_tank->getCoordonnee().y] != "#" &&
		map[m_tank->getCoordonnee().x - 2][m_tank->getCoordonnee().y] != "~" &&
		map[m_tank->getCoordonnee().x - 2][m_tank->getCoordonnee().y] != "^") {
		if (map[m_tank->getCoordonnee().x - 1][m_tank->getCoordonnee().y] == "!") {
			m_tank->loseHealth(m_tank->getBombe().getDegat());
		}
		if (map[m_tank->getCoordonnee().x - 1][m_tank->getCoordonnee().y] == "*") {
			m_tank->loseHealth(m_tank->getMissile().getDegat());
		}
		deplacerCanonEnnemie(m_tank, "UP", 2);
		map[m_tank->getCoordonnee().x][m_tank->getCoordonnee().y] = " ";
		m_tank->moveX(-1);
		map[m_tank->getCoordonnee().x][m_tank->getCoordonnee().y] = "~";
	}
	else if (m_keyPress == "S" && map[m_tank->getCoordonnee().x + 1][m_tank->getCoordonnee().y] != "#" &&
		map[m_tank->getCoordonnee().x + 2][m_tank->getCoordonnee().y] != "~" &&
		map[m_tank->getCoordonnee().x + 2][m_tank->getCoordonnee().y] != "^") {
		if (map[m_tank->getCoordonnee().x + 1][m_tank->getCoordonnee().y] == "!") {
			m_tank->loseHealth(m_tank->getBombe().getDegat());
		}
		if (map[m_tank->getCoordonnee().x + 1][m_tank->getCoordonnee().y] == "*") {
			m_tank->loseHealth(m_tank->getMissile().getDegat());
		}
		deplacerCanonEnnemie(m_tank, "DOWN", 2);
		map[m_tank->getCoordonnee().x][m_tank->getCoordonnee().y] = " ";
		m_tank->moveX(1);
		map[m_tank->getCoordonnee().x][m_tank->getCoordonnee().y] = "~";
	}
	else if (m_keyPress == "A" && map[m_tank->getCoordonnee().x][m_tank->getCoordonnee().y - 1] != "#" &&
		map[m_tank->getCoordonnee().x][m_tank->getCoordonnee().y - 2] != "~" &&
		map[m_tank->getCoordonnee().x][m_tank->getCoordonnee().y - 2] != "<") {
		if (map[m_tank->getCoordonnee().x][m_tank->getCoordonnee().y - 1] == "!") {
			m_tank->loseHealth(m_tank->getBombe().getDegat());
		}
		if (map[m_tank->getCoordonnee().x][m_tank->getCoordonnee().y - 1] == "*") {
			m_tank->loseHealth(m_tank->getMissile().getDegat());
		}
		deplacerCanonEnnemie(m_tank, "LEFT", 2);
		map[m_tank->getCoordonnee().x][m_tank->getCoordonnee().y] = " ";
		m_tank->moveY(-1);
		map[m_tank->getCoordonnee().x][m_tank->getCoordonnee().y] = "~";
	}
	else if (m_keyPress == "D" && map[m_tank->getCoordonnee().x][m_tank->getCoordonnee().y + 1] != "#" &&
		map[m_tank->getCoordonnee().x][m_tank->getCoordonnee().y + 2] != "~" &&
		map[m_tank->getCoordonnee().x][m_tank->getCoordonnee().y + 2] != ">") {
		if (map[m_tank->getCoordonnee().x][m_tank->getCoordonnee().y + 1] == "!") {
			m_tank->loseHealth(m_tank->getBombe().getDegat());
		}
		if (map[m_tank->getCoordonnee().x][m_tank->getCoordonnee().y + 1] == "*") {
			m_tank->loseHealth(m_tank->getMissile().getDegat());
		}
		deplacerCanonEnnemie(m_tank, "RIGHT", 2);
		map[m_tank->getCoordonnee().x][m_tank->getCoordonnee().y] = " ";
		m_tank->moveY(1);
		map[m_tank->getCoordonnee().x][m_tank->getCoordonnee().y] = "~";
	}
	if (m_tank->getEtatBombe()) {
		map[coordonnee.x][coordonnee.y] = "!";
		m_tank->dropBombe(false);
	}
}

void Map::ajoutMur(std::vector<Mur*> m_mur, int m_taille)
{
	if (m_mur.size() <= 0) {
		generateurMap();
	}
	for (int i = 0; i < m_mur.size(); i++)
	{
		for (int j = 0; j < m_mur.at(i)->getLongueur(); j++)
		{
			if (m_mur.at(i)->getDirection() == Direction::Haut) {
				if (m_mur.at(i)->getCoordonnee().x - j > 0 && m_mur.at(i)->getCoordonnee().y > 0 && m_mur.at(i)->getCoordonnee().x - j < taille && m_mur.at(i)->getCoordonnee().y < taille) {
					if (map[m_mur.at(i)->getCoordonnee().x - j][m_mur.at(i)->getCoordonnee().y] == " ") {
						map[m_mur.at(i)->getCoordonnee().x - j][m_mur.at(i)->getCoordonnee().y] = "#";
					}
				}
			}
			if (m_mur.at(i)->getDirection() == Direction::Bas) {
				if (m_mur.at(i)->getCoordonnee().x + j > 0 && m_mur.at(i)->getCoordonnee().y > 0 && m_mur.at(i)->getCoordonnee().x + j < taille && m_mur.at(i)->getCoordonnee().y < taille) {
					if (map[m_mur.at(i)->getCoordonnee().x + j][m_mur.at(i)->getCoordonnee().y] == " ") {
						map[m_mur.at(i)->getCoordonnee().x + j][m_mur.at(i)->getCoordonnee().y] = "#";
					}
				}
			}

			if (m_mur.at(i)->getDirection() == Direction::Gauche) {
				if (m_mur.at(i)->getCoordonnee().x > 0 && m_mur.at(i)->getCoordonnee().y - j > 0 && m_mur.at(i)->getCoordonnee().x < taille && m_mur.at(i)->getCoordonnee().y < taille - j) {
					if (map[m_mur.at(i)->getCoordonnee().x][m_mur.at(i)->getCoordonnee().y - j] == " ") {
						map[m_mur.at(i)->getCoordonnee().x][m_mur.at(i)->getCoordonnee().y - j] = "#";
					}
				}
			}
			if (m_mur.at(i)->getDirection() == Direction::Droit) {
				if (m_mur.at(i)->getCoordonnee().x  > 0 && m_mur.at(i)->getCoordonnee().y + j > 0 && m_mur.at(i)->getCoordonnee().x < taille && m_mur.at(i)->getCoordonnee().y < taille + j) {
					if (map[m_mur.at(i)->getCoordonnee().x][m_mur.at(i)->getCoordonnee().y + j] == " ") {
						map[m_mur.at(i)->getCoordonnee().x][m_mur.at(i)->getCoordonnee().y + j] = "#";
					}
				}
			}
		}
	}
	
}

void Map::deplacerCanon(Tank* m_tank, std::string m_keyPress, int m_value)
{
	if (m_keyPress == "LEFT") {
		if (m_tank->getCanon().getDirection() == Direction::Haut) {
			if (map[m_tank->getCanon().getCoordonnee().x][m_tank->getCanon().getCoordonnee().y - 1] == " ") {
				map[m_tank->getCanon().getCoordonnee().x][m_tank->getCanon().getCoordonnee().y] = " ";
				m_tank->setPositionCanon(m_tank->getCanon().getCoordonnee().x, m_tank->getCanon().getCoordonnee().y - 1, Direction::HautGauche);
				map[m_tank->getCanon().getCoordonnee().x][m_tank->getCanon().getCoordonnee().y] = "\\";
			}
		}
		else if (m_tank->getCanon().getDirection() == Direction::Bas) {
			if (map[m_tank->getCanon().getCoordonnee().x][m_tank->getCanon().getCoordonnee().y + 1] == " ") {
				std::string test = map[m_tank->getCanon().getCoordonnee().x][m_tank->getCanon().getCoordonnee().y + 1];
				map[m_tank->getCanon().getCoordonnee().x][m_tank->getCanon().getCoordonnee().y] = " ";
				m_tank->setPositionCanon(m_tank->getCanon().getCoordonnee().x, m_tank->getCanon().getCoordonnee().y + 1, Direction::BasDroit);
				map[m_tank->getCanon().getCoordonnee().x][m_tank->getCanon().getCoordonnee().y] = "\\";
			}
		}
		else if (m_tank->getCanon().getDirection() == Direction::Droit) {
			if (map[m_tank->getCanon().getCoordonnee().x - 1][m_tank->getCanon().getCoordonnee().y] == " ") {
				map[m_tank->getCanon().getCoordonnee().x][m_tank->getCanon().getCoordonnee().y] = " ";
				m_tank->setPositionCanon(m_tank->getCanon().getCoordonnee().x - 1, m_tank->getCanon().getCoordonnee().y, Direction::HautDroite);
				map[m_tank->getCanon().getCoordonnee().x][m_tank->getCanon().getCoordonnee().y] = "/";
			}
		}
		else if (m_tank->getCanon().getDirection() == Direction::Gauche) {
			if (map[m_tank->getCanon().getCoordonnee().x + 1][m_tank->getCanon().getCoordonnee().y] == " ") {
				map[m_tank->getCanon().getCoordonnee().x][m_tank->getCanon().getCoordonnee().y] = " ";
				m_tank->setPositionCanon(m_tank->getCanon().getCoordonnee().x + 1, m_tank->getCanon().getCoordonnee().y, Direction::BasGauche);
				map[m_tank->getCanon().getCoordonnee().x][m_tank->getCanon().getCoordonnee().y] = "/";
			}
		}
		else if (m_tank->getCanon().getDirection() == Direction::HautGauche) {
			if (map[m_tank->getCanon().getCoordonnee().x + 1][m_tank->getCanon().getCoordonnee().y] == " ") {
				map[m_tank->getCanon().getCoordonnee().x][m_tank->getCanon().getCoordonnee().y] = " ";
				m_tank->setPositionCanon(m_tank->getCanon().getCoordonnee().x + 1, m_tank->getCanon().getCoordonnee().y, Direction::Gauche);
				map[m_tank->getCanon().getCoordonnee().x][m_tank->getCanon().getCoordonnee().y] = "<";
			}
		}
		else if (m_tank->getCanon().getDirection() == Direction::HautDroite) {
			if (map[m_tank->getCanon().getCoordonnee().x][m_tank->getCanon().getCoordonnee().y - 1] == " ") {
				map[m_tank->getCanon().getCoordonnee().x][m_tank->getCanon().getCoordonnee().y] = " ";
				m_tank->setPositionCanon(m_tank->getCanon().getCoordonnee().x, m_tank->getCanon().getCoordonnee().y - 1, Direction::Haut);
				map[m_tank->getCanon().getCoordonnee().x][m_tank->getCanon().getCoordonnee().y] = "^";
			}
		}
		else if (m_tank->getCanon().getDirection() == Direction::BasGauche) {
			if (map[m_tank->getCanon().getCoordonnee().x][m_tank->getCanon().getCoordonnee().y + 1] == " ") {
				map[m_tank->getCanon().getCoordonnee().x][m_tank->getCanon().getCoordonnee().y] = " ";
				m_tank->setPositionCanon(m_tank->getCanon().getCoordonnee().x, m_tank->getCanon().getCoordonnee().y + 1, Direction::Bas);
				map[m_tank->getCanon().getCoordonnee().x][m_tank->getCanon().getCoordonnee().y] = "^";
			}
		}
		else if (m_tank->getCanon().getDirection() == Direction::BasDroit) {
			if (map[m_tank->getCanon().getCoordonnee().x - 1][m_tank->getCanon().getCoordonnee().y] == " ") {
				map[m_tank->getCanon().getCoordonnee().x][m_tank->getCanon().getCoordonnee().y] = " ";
				m_tank->setPositionCanon(m_tank->getCanon().getCoordonnee().x - 1, m_tank->getCanon().getCoordonnee().y, Direction::Droit);
				map[m_tank->getCanon().getCoordonnee().x][m_tank->getCanon().getCoordonnee().y] = ">";
			}
		}
	}
	if (m_keyPress == "RIGHT") {
		if (m_tank->getCanon().getDirection() == Direction::Haut) {
			if (map[m_tank->getCanon().getCoordonnee().x][m_tank->getCanon().getCoordonnee().y + 1] == " ") {
				map[m_tank->getCanon().getCoordonnee().x][m_tank->getCanon().getCoordonnee().y] = " ";
				m_tank->setPositionCanon(m_tank->getCanon().getCoordonnee().x, m_tank->getCanon().getCoordonnee().y + 1, Direction::HautDroite);
				map[m_tank->getCanon().getCoordonnee().x][m_tank->getCanon().getCoordonnee().y] = "/";
			}
		}
		else if (m_tank->getCanon().getDirection() == Direction::Bas) {
			if (map[m_tank->getCanon().getCoordonnee().x][m_tank->getCanon().getCoordonnee().y - 1] == " ") {
				map[m_tank->getCanon().getCoordonnee().x][m_tank->getCanon().getCoordonnee().y] = " ";
				m_tank->setPositionCanon(m_tank->getCanon().getCoordonnee().x, m_tank->getCanon().getCoordonnee().y - 1, Direction::BasGauche);
				map[m_tank->getCanon().getCoordonnee().x][m_tank->getCanon().getCoordonnee().y] = "/";
			}
		}
		else if (m_tank->getCanon().getDirection() == Direction::Droit) {
			if (map[m_tank->getCanon().getCoordonnee().x + 1][m_tank->getCanon().getCoordonnee().y] == " ") {
				map[m_tank->getCanon().getCoordonnee().x][m_tank->getCanon().getCoordonnee().y] = " ";
				m_tank->setPositionCanon(m_tank->getCanon().getCoordonnee().x + 1, m_tank->getCanon().getCoordonnee().y, Direction::BasDroit);
				map[m_tank->getCanon().getCoordonnee().x][m_tank->getCanon().getCoordonnee().y] = "\\";
			}
		}
		else if (m_tank->getCanon().getDirection() == Direction::Gauche) {
			if (map[m_tank->getCanon().getCoordonnee().x - 1][m_tank->getCanon().getCoordonnee().y] == " ") {
				map[m_tank->getCanon().getCoordonnee().x][m_tank->getCanon().getCoordonnee().y] = " ";
				m_tank->setPositionCanon(m_tank->getCanon().getCoordonnee().x - 1, m_tank->getCanon().getCoordonnee().y, Direction::HautGauche);
				map[m_tank->getCanon().getCoordonnee().x][m_tank->getCanon().getCoordonnee().y] = "\\";
			}
		}
		else if (m_tank->getCanon().getDirection() == Direction::HautGauche) {
			if (map[m_tank->getCanon().getCoordonnee().x][m_tank->getCanon().getCoordonnee().y + 1] == " ") {
				map[m_tank->getCanon().getCoordonnee().x][m_tank->getCanon().getCoordonnee().y] = " ";
				m_tank->setPositionCanon(m_tank->getCanon().getCoordonnee().x, m_tank->getCanon().getCoordonnee().y + 1, Direction::Haut);
				map[m_tank->getCanon().getCoordonnee().x][m_tank->getCanon().getCoordonnee().y] = "^";
			}
		}
		else if (m_tank->getCanon().getDirection() == Direction::HautDroite) {
			if (map[m_tank->getCanon().getCoordonnee().x + 1][m_tank->getCanon().getCoordonnee().y] == " ") {
				map[m_tank->getCanon().getCoordonnee().x][m_tank->getCanon().getCoordonnee().y] = " ";
				m_tank->setPositionCanon(m_tank->getCanon().getCoordonnee().x + 1, m_tank->getCanon().getCoordonnee().y, Direction::Droit);
				map[m_tank->getCanon().getCoordonnee().x][m_tank->getCanon().getCoordonnee().y] = ">";
			}
		}
		else if (m_tank->getCanon().getDirection() == Direction::BasGauche) {
			if (map[m_tank->getCanon().getCoordonnee().x - 1][m_tank->getCanon().getCoordonnee().y] == " ") {
				map[m_tank->getCanon().getCoordonnee().x][m_tank->getCanon().getCoordonnee().y] = " ";
				m_tank->setPositionCanon(m_tank->getCanon().getCoordonnee().x - 1, m_tank->getCanon().getCoordonnee().y, Direction::Gauche);
				map[m_tank->getCanon().getCoordonnee().x][m_tank->getCanon().getCoordonnee().y] = "<";
			}
		}
		else if (m_tank->getCanon().getDirection() == Direction::BasDroit) {
			if (map[m_tank->getCanon().getCoordonnee().x][m_tank->getCanon().getCoordonnee().y - 1] == " ") {
				map[m_tank->getCanon().getCoordonnee().x][m_tank->getCanon().getCoordonnee().y] = " ";
				m_tank->setPositionCanon(m_tank->getCanon().getCoordonnee().x, m_tank->getCanon().getCoordonnee().y - 1, Direction::Bas);
				map[m_tank->getCanon().getCoordonnee().x][m_tank->getCanon().getCoordonnee().y] = "^";
			}
		}
	}
}

void Map::SpawnMissile(Tank* m_tank)
{
	if (m_tank->getEtatMissile()) {
		Coordonnee coordonneeCanon = m_tank->getCanon().getCoordonnee();
		if (m_tank->getCanon().getDirection() == Direction::Haut && map[coordonneeCanon.x -1][coordonneeCanon.y] == " ") {
			map[coordonneeCanon.x - 1][coordonneeCanon.y] = "*";
			missilles->push_back(new Missile(coordonneeCanon,Direction::Haut, 20));
		}
		if (m_tank->getCanon().getDirection() == Direction::Bas && map[coordonneeCanon.x + 1][coordonneeCanon.y] == " ") {
			map[coordonneeCanon.x + 1][coordonneeCanon.y] = "*";
			missilles->push_back(new Missile(coordonneeCanon, Direction::Bas, 20));
		}
		if (m_tank->getCanon().getDirection() == Direction::Gauche && map[coordonneeCanon.x][coordonneeCanon.y - 1] == " ") {
			map[coordonneeCanon.x][coordonneeCanon.y - 1] = "*";
			missilles->push_back(new Missile(coordonneeCanon, Direction::Gauche, 20));
		}
		if (m_tank->getCanon().getDirection() == Direction::Droit && map[coordonneeCanon.x][coordonneeCanon.y + 1] == " ") {
			map[coordonneeCanon.x][coordonneeCanon.y + 1] = "*";
			missilles->push_back(new Missile(coordonneeCanon, Direction::Droit, 20));
		}
		//Quatre coins
		if (m_tank->getCanon().getDirection() == Direction::HautGauche && map[coordonneeCanon.x - 1][coordonneeCanon.y - 1] == " ") {
			map[coordonneeCanon.x - 1][coordonneeCanon.y - 1] = "*";
			missilles->push_back(new Missile(coordonneeCanon, Direction::HautGauche, 20));
		}
		if (m_tank->getCanon().getDirection() == Direction::HautDroite && map[coordonneeCanon.x - 1][coordonneeCanon.y + 1] == " ") {
			map[coordonneeCanon.x - 1][coordonneeCanon.y + 1] = "*";
			missilles->push_back(new Missile(coordonneeCanon, Direction::HautDroite, 20));
		}
		if (m_tank->getCanon().getDirection() == Direction::BasGauche && map[coordonneeCanon.x + 1][coordonneeCanon.y - 1] == " ") {
			map[coordonneeCanon.x + 1][coordonneeCanon.y - 1] = "*";
			missilles->push_back(new Missile(coordonneeCanon, Direction::BasGauche, 20));
		}
		if (m_tank->getCanon().getDirection() == Direction::BasDroit && map[coordonneeCanon.x + 1][coordonneeCanon.y + 1] == " ") {
			map[coordonneeCanon.x + 1][coordonneeCanon.y + 1] = "*";
			missilles->push_back(new Missile(coordonneeCanon, Direction::BasDroit, 20));
		}
		m_tank->shoot(false);
	}
}

void Map::degatEnnemie(Missile* m_missile)
{
	int x = 0;
	int y = 0;
	int x2 = 0;
	int y2 = 0;
	if (m_missile->getDirection() == Direction::Haut) {
		x = -1;
		x2 = -2;
	}
	else if (m_missile->getDirection() == Direction::Bas) {
		x = 1;
		x2 = 2;
	}
	else if (m_missile->getDirection() == Direction::Droit) {
		y = 1;
		y2 = 2;
	}
	else if (m_missile->getDirection() == Direction::Gauche) {
		y = -1;
		y2 = -2;
	}
	else if (m_missile->getDirection() == Direction::HautGauche) {
		x = -1;
		y = -1;
		x2 = -2;
		y2 = -2;
	}
	else if (m_missile->getDirection() == Direction::HautDroite) {
		x = -1;
		y = 1;
		x2 = -2;
		y2 = 2;
	}
	else if (m_missile->getDirection() == Direction::BasGauche) {
		x = 1;
		y = -1;
		x2 = 2;
		y2 = -2;
	}
	else if (m_missile->getDirection() == Direction::BasDroit) {
		x = 1;
		y = 1;
		x2 = 2;
		y2 = 2;
	}
	Coordonnee missileCoordonnee = m_missile->getCoordonnee();
	Coordonnee tankPlayer = player->getCoordonnee();
	if ((tankPlayer.x == (missileCoordonnee.x + x) && tankPlayer.y == (missileCoordonnee.y + y)) || (tankPlayer.x == (missileCoordonnee.x + x2) && tankPlayer.y == (missileCoordonnee.y + y2))) {
		if (player->loseHealth(m_missile->getDegat())) {
			map[player->getCoordonnee().x][player->getCoordonnee().y] = " ";
			map[player->getCanon().getCoordonnee().x][player->getCanon().getCoordonnee().y] = " ";
		}
	}
	for (int i = 0; i < tanks->size(); i++)
	{
		Coordonnee tankCoordonnee = tanks->at(i)->getCoordonnee();
		if ((tankCoordonnee.x == (missileCoordonnee.x + x) && tankCoordonnee.y == (missileCoordonnee.y + y)) || (tankCoordonnee.x == (missileCoordonnee.x + x2) && tankCoordonnee.y == (missileCoordonnee.y + y2))) {
			if (tanks->at(i)->loseHealth(m_missile->getDegat())) {
				try {
					map[tanks->at(i)->getCoordonnee().x][tanks->at(i)->getCoordonnee().y] = " ";
					map[tanks->at(i)->getCanon().getCoordonnee().x][tanks->at(i)->getCanon().getCoordonnee().y] = " ";
					if (tanks->size() > 0) {
						retirer(i);
					}
				}
				catch (...) {
					system("CLS");
					std::cout << "Erreur";
				}
			}
		}
	}
}

void Map::deplacementMissileAffichage()
{
	if (missilles->size() != 0) {
		for (int i = 0; i < missilles->size(); i++){
			if (missilles->at(i)->getDirection() == Direction::Haut) {
				map[missilles->at(i)->getCoordonnee().x][missilles->at(i)->getCoordonnee().y] = " ";
				missilles->at(i)->moveX(-1);
				map[missilles->at(i)->getCoordonnee().x][missilles->at(i)->getCoordonnee().y] = "*";
			}
			if (missilles->at(i)->getDirection() == Direction::Bas) {
				map[missilles->at(i)->getCoordonnee().x][missilles->at(i)->getCoordonnee().y] = " ";
				missilles->at(i)->moveX(1);
				map[missilles->at(i)->getCoordonnee().x][missilles->at(i)->getCoordonnee().y] = "*";
			}
			if (missilles->at(i)->getDirection() == Direction::Gauche) {
				map[missilles->at(i)->getCoordonnee().x][missilles->at(i)->getCoordonnee().y] = " ";
				missilles->at(i)->moveY(-1);
				map[missilles->at(i)->getCoordonnee().x][missilles->at(i)->getCoordonnee().y] = "*";
			}
			if (missilles->at(i)->getDirection() == Direction::Droit) {
				map[missilles->at(i)->getCoordonnee().x][missilles->at(i)->getCoordonnee().y] = " ";
				missilles->at(i)->moveY(1);
				map[missilles->at(i)->getCoordonnee().x][missilles->at(i)->getCoordonnee().y] = "*";
			}
			//Quatre coins
			if (missilles->at(i)->getDirection() == Direction::HautGauche) {
				map[missilles->at(i)->getCoordonnee().x][missilles->at(i)->getCoordonnee().y] = " ";
				missilles->at(i)->moveX(-1);
				missilles->at(i)->moveY(-1);
				map[missilles->at(i)->getCoordonnee().x][missilles->at(i)->getCoordonnee().y] = "*";
			}
			if (missilles->at(i)->getDirection() == Direction::HautDroite) {
				map[missilles->at(i)->getCoordonnee().x][missilles->at(i)->getCoordonnee().y] = " ";
				missilles->at(i)->moveX(-1);
				missilles->at(i)->moveY(1);
				map[missilles->at(i)->getCoordonnee().x][missilles->at(i)->getCoordonnee().y] = "*";
			}
			if (missilles->at(i)->getDirection() == Direction::BasGauche) {
				map[missilles->at(i)->getCoordonnee().x][missilles->at(i)->getCoordonnee().y] = " ";
				missilles->at(i)->moveY(-1);
				missilles->at(i)->moveX(1);
				map[missilles->at(i)->getCoordonnee().x][missilles->at(i)->getCoordonnee().y] = "*";
			}
			if (missilles->at(i)->getDirection() == Direction::BasDroit) {
				map[missilles->at(i)->getCoordonnee().x][missilles->at(i)->getCoordonnee().y] = " ";
				missilles->at(i)->moveY(1);
				missilles->at(i)->moveX(1);
				map[missilles->at(i)->getCoordonnee().x][missilles->at(i)->getCoordonnee().y] = "*";
			}
			if ((map[missilles->at(i)->getCoordonnee().x + 1][missilles->at(i)->getCoordonnee().y] != " " || 
				map[missilles->at(i)->getCoordonnee().x - 1][missilles->at(i)->getCoordonnee().y] != " ") &&
				(missilles->at(i)->getDirection() == Direction::Haut || missilles->at(i)->getDirection() == Direction::Bas)) {
				degatEnnemie(missilles->at(i));
				map[missilles->at(i)->getCoordonnee().x][missilles->at(i)->getCoordonnee().y] = " ";
				missilles->erase(missilles->begin() + i);
			}
			else if ((map[missilles->at(i)->getCoordonnee().x][missilles->at(i)->getCoordonnee().y + 1] != " " ||
				map[missilles->at(i)->getCoordonnee().x][missilles->at(i)->getCoordonnee().y - 1] != " ") && 
				(missilles->at(i)->getDirection() == Direction::Droit || missilles->at(i)->getDirection() == Direction::Gauche)) {
				degatEnnemie(missilles->at(i));
				map[missilles->at(i)->getCoordonnee().x][missilles->at(i)->getCoordonnee().y] = " ";
				missilles->erase(missilles->begin() + i);
			}
			else if ((map[missilles->at(i)->getCoordonnee().x + 1][missilles->at(i)->getCoordonnee().y + 1] != " " ||
				map[missilles->at(i)->getCoordonnee().x - 1][missilles->at(i)->getCoordonnee().y - 1] != " ") &&
				(missilles->at(i)->getDirection() == Direction::BasDroit || missilles->at(i)->getDirection() == Direction::HautGauche)) {
				degatEnnemie(missilles->at(i));
				map[missilles->at(i)->getCoordonnee().x][missilles->at(i)->getCoordonnee().y] = " ";
				missilles->erase(missilles->begin() + i);
			}
			else if ((map[missilles->at(i)->getCoordonnee().x + 1][missilles->at(i)->getCoordonnee().y - 1] != " " ||
				map[missilles->at(i)->getCoordonnee().x - 1][missilles->at(i)->getCoordonnee().y + 1] != " ") &&
				(missilles->at(i)->getDirection() == Direction::HautDroite || missilles->at(i)->getDirection() == Direction::BasGauche)) {
				degatEnnemie(missilles->at(i));
				map[missilles->at(i)->getCoordonnee().x][missilles->at(i)->getCoordonnee().y] = " ";
				missilles->erase(missilles->begin() + i);
			}
			if (missilles->size() == 0) {
				Sleep(300);
			}
			else {
				Sleep(300 / missilles->size()); //Temps d'affichage du missile
			}
		}
	}
}

void Map::spawnTankEnnemie(int m_nombreEnnemie, int m_degat, int m_health, Tank* m_tank)
{
	nombreEnnemie = m_nombreEnnemie;
	for (int i = 0; i < nombreEnnemie; i++)
	{
		int x = rand() % taille - 1;
		int y = rand() % taille - 1;
		TankEnnemie* ennemie = new TankEnnemie(m_tank,std::to_string(i), m_health, x, y, Type::ennemy);
		ajouter(ennemie);
		tanks->push_back(ennemie);
	}
}

std::vector<TankEnnemie*>* Map::getTanks()
{
	return tanks;
}

void Map::genererMap() 
{
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
		}
	}
}

void Map::generateurMap() {
	srand(time(NULL));
	int nombreMurs = rand() % 16;
	std::vector<Mur*> murs;
	Tank* player = new Tank("Player", 100, 0, 0, Type::player);
	murs.push_back(new Mur(0, 12, 5, Direction::Droit));
	murs.push_back(new Mur(10, 6, 6, Direction::Droit));
	murs.push_back(new Mur(20, 18, 7, Direction::Haut));
	murs.push_back(new Mur(5, 5, 5, Direction::Haut));
	murs.push_back(new Mur(5, 12, 5, Direction::Droit));
	/*for (int i = 0; i < nombreMurs; i++) {
		int x = rand() % taille;
		int y = rand() % taille;
		int longeur = rand() % 5;
		int directionNumber = rand() % 4;
		Direction direction;
		if (directionNumber == 0) {
			direction = Direction::Haut;
		}
		else if (directionNumber == 1) {
			direction = Direction::Bas;
		}
		else if (directionNumber == 2) {
			direction = Direction::Droit;
		}
		else if (directionNumber == 3) {
			direction = Direction::Gauche;
		}
		if (x < 0) {
			x = 0;
		}
		if (y < 0) {
			y = 0;
		}
		if (x > taille) {
			x = taille;
		}
		if (y > taille) {
			y = taille;
		}
		if (longeur < 2) {
			longeur =3;
		}
		murs.push_back(new Mur(x, y, longeur, direction));
	}*/
	ajoutMur(murs, murs.size());
	ajouter(player);
	spawnTankEnnemie(nombreEnnemie, 50, 2, player);
}

void Map::killAllTank()
{
	tanks->clear();
	Sleep(200);
}