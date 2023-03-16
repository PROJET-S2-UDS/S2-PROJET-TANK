// S2-PROJET-TANK-2.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//


#include <iostream>
#include <windows.h> 
#include <thread>
#include <sstream>
#include <time.h>

#include "map.h"
#include "tank.h"
#include "direction.h"

using namespace std;


void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

void gestionMissiles(Map* map) {
    while (true)
    {
        map->deplacementMissileAffichage();
    }
}

void gestionEnnemies(Map* map) {
    while (true)
    {
        map->pathEnnemie();
    }
}

void refresh(Map* map, Tank* m_tank, int maxNiveau) {
    for (int i = 0; i < maxNiveau; i++)
    {
        bool boucle = true;
        while (boucle)
        {
            COORD p = { 0,0 };
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
            map->afficheMap(std::cout, m_tank);
            if (m_tank->getHealth() <= 0) {
                boucle = false;
            }
            else if (map->getTanks()->empty()) {
                boucle = false;
            }
        }
        if (m_tank->getHealth() <= 0) {
            system("CLS");
            cout << "Game Over !";
        }
        else if (map->getTanks()->empty()) {
            system("CLS");
            int tailleMap = map->getTaille();
            int nombreEnnemie = map->getNombreEnnemie();
            map = nullptr;
            map = new Map(tailleMap, nombreEnnemie + 1);
            map->addOneNiveau();
            map->generateurMap();
            system("CLS");
        }
    }
}

int main()
{
    ShowConsoleCursor(false);
    int niveau = 0;
    int maxNiveau = 2;
    int nombreNiveau = 10;
    int tailleJeux = 20;
    int nombreEnnemie = 1;
    Map* map = new Map(tailleJeux,nombreEnnemie);
    srand(time(NULL));
    int nombreMurs = rand() % 16;
    map->generateurMap();
    Tank* player = map->getPlayer();
    thread affichage(refresh, map, player, maxNiveau);
    thread gestionMissile(gestionMissiles, map);
    thread gestionEnnemie(gestionEnnemies, map);
    while (true)
    {
        if (GetKeyState('W') & 0x8000) {
            map->deplacer(player,"W");
        }
        if (GetKeyState('S') & 0x8000) {
            map->deplacer(player, "S");
        }
        if (GetKeyState('A') & 0x8000) {
            map->deplacer(player, "A");
        }
        if (GetKeyState('D') & 0x8000) {
            map->deplacer(player, "D");
        }
        if (GetKeyState(VK_SPACE) & 0x8000) {
            player->dropBombe(true);
        }
        if (GetKeyState('E') & 0x8000) {
            player->shoot(true);
        }
        if (GetKeyState(VK_LEFT) & 0x8000) {
            map->deplacerCanon(player, "LEFT", 1);
        }
        if (GetKeyState(VK_RIGHT) & 0x8000) {
            map->deplacerCanon(player, "RIGHT", 1);
        }
        if (GetKeyState('P') & 0x8000) {
            map->killAllTank();
        }
        Sleep(100);
    }
    return 0;
}

