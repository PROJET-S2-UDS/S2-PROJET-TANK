#include "map.h"
#include "mur.h"

int rayonEnnemie = 8;

Map::Map()
{
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

Map::Map(int m_taille, int m_nombreEnnemie) {
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

void Map::afficheMap(std::ostream& o, Tank* m_tank)
{
	o.clear();
	o << "X: " << m_tank->getCoordonnee().x << " Y: " << m_tank->getCoordonnee().y << "  " << std::endl;
	o << "Vie : " << m_tank->getHealth() << "  " << std::endl;
	for (int i = 0; i < taille; i++)
	{
		for (int z = 0; z < taille; z++)
		{
			o << map[i][z];
		}
		o << std::endl;
	}
	SpawnMissile(m_tank);
	pathEnnemie();
	std::thread deplacementMissileAffichage();
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

void Map::pathEnnemie()
{
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
				deplacerCanon(tankEnnemie, "LEFT", 1);
			}
			else if ((coordonneePlayer.y - coordonneeEnnemeie.y) > 0) {
				deplacerCanon(tankEnnemie, "RIGHT", 1);
			}
			tankEnnemie->shoot(true);
			SpawnMissile(tankEnnemie);
		}
		if ((coordonneePlayer.y == coordonneeEnnemeie.y) && std::abs(coordonneePlayer.x - coordonneeEnnemeie.x) <= rayonEnnemie) {
			if ((coordonneePlayer.x - coordonneeEnnemeie.x) < 0) {
				deplacerCanon(tankEnnemie, "UP", 1);
			}
			else if ((coordonneePlayer.x - coordonneeEnnemeie.x) > 0) {
				deplacerCanon(tankEnnemie, "DOWN", 1);
			}
			tankEnnemie->shoot(true);
			SpawnMissile(tankEnnemie);
		}
		/*if (differenceX <= differenceY) {
			if (differenceX < 0) {
				deplacer(tankEnnemie, "W");
			}
			else if (differenceX > 0){
				deplacer(tankEnnemie, "S");
			}
		}
		else if (differenceX > differenceY) {
			if (differenceY < 0) {
				deplacer(tankEnnemie, "A");
			}
			else if (differenceY > 0) {
				deplacer(tankEnnemie, "D");
			}
		}*/
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
		deplacerCanon(m_tank, "UP", 2);
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
		deplacerCanon(m_tank, "DOWN", 2);
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
		deplacerCanon(m_tank, "LEFT", 2);
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
		deplacerCanon(m_tank, "RIGHT", 2);
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

void Map::deplacerCanon(Tank* m_tank, std::string m_keyPress, int m_value)
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
		m_tank->shoot(false);
	}
}

void Map::degatEnnemie(Missile* m_missile)
{
	int x = 0;
	int y = 0;
	switch (m_missile->getDirection())
	{
	case Direction::Haut:
		x = -1;
		break;
	case Direction::Bas:
		x = 1;
		break;
	case Direction::Droit:
		y = 1;
		break;
	case Direction::Gauche:
		y = -1;
		break;
	default:
		break;
	}
	Coordonnee missileCoordonnee = m_missile->getCoordonnee();
	Coordonnee tankPlayer = player->getCoordonnee();
	if (tankPlayer.x == (missileCoordonnee.x + x) && tankPlayer.y == (missileCoordonnee.y + y)) {
		if (player->loseHealth(m_missile->getDegat())) {
			map[player->getCoordonnee().x][player->getCoordonnee().y] = " ";
			map[player->getCanon().getCoordonnee().x][player->getCanon().getCoordonnee().y] = " ";
		}
	}
	for (int i = 0; i < tanks->size(); i++)
	{
		Coordonnee tankCoordonnee = tanks->at(i)->getCoordonnee();
		if (tankCoordonnee.x == (missileCoordonnee.x + x) && tankCoordonnee.y == (missileCoordonnee.y + y)) {
			if (tanks->at(i)->loseHealth(m_missile->getDegat())) {
				map[tanks->at(i)->getCoordonnee().x][tanks->at(i)->getCoordonnee().y] = " ";
				map[tanks->at(i)->getCanon().getCoordonnee().x][tanks->at(i)->getCanon().getCoordonnee().y] = " ";
				retirer(i);
			}
		}
	}
}

void Map::deplacementMissileAffichage()
{
	if (missilles->size() != 0) {
		for (int i = 0; i < missilles->size(); i++)
		{
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
			Sleep(100); //Temps d'affichage du missile
		}
	}
}

void Map::spawnTankEnnemie(int m_nombreEnnemie, int m_degat, int m_health, Tank* m_tank)
{
	nombreEnnemie = m_nombreEnnemie;
	for (int i = 0; i < nombreEnnemie; i++)
	{
		int x = rand() % taille;
		int y = rand() % taille;
		TankEnnemie* ennemie = new TankEnnemie(m_tank,std::to_string(i), m_health, x, y, Type::ennemy);
		ajouter(ennemie);
		tanks->push_back(ennemie);
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
