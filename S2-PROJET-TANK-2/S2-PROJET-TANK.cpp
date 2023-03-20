// S2-PROJET-TANK-2.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//


#include <iostream>
#include <windows.h> 
#include <thread>
#include <sstream>
#include <time.h>
#include <cstdio>

#include "map.h"
#include "tank.h"
#include "direction.h"
#include "menu.h"

using namespace std;

bool active = true;

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

void gestionMissiles(Map* map) {
   while (active)
    {
       
        map->deplacementMissileAffichage();
    }
}

void gestionEnnemies(Map* map) {
    while (active)
    {
       map->pathEnnemie();

    }
}

void refresh(Map* map, Tank* m_tank) {
        bool boucle = true;
        COORD p = { 0,0 };
        while (boucle && active)
        {
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
            active = false;
        }
}

int main()
{
    HWND consoleWindow = GetConsoleWindow();

    // Maximiser la fenêtre de la console
    ShowWindow(consoleWindow, SW_MAXIMIZE);

    ShowConsoleCursor(false);
    Menu menu;
    while (menu.getChoix() != 3){
        int niveau = 1;
        int maxNiveau = 10;
        int tailleJeux = 15;
        int nombreEnnemie = 1;
        Map* map;
        menu.show();
        if (menu.getChoix() == 1) {
            for (int i = 0; i < maxNiveau; i++)
            {
                active = true;
                map = new Map(tailleJeux, nombreEnnemie, niveau);
                srand(time(NULL));
                int nombreMurs = rand() % 16;
                map->generateurMap();
                Tank* player = map->getPlayer();
                thread affichage(refresh, map, player);
                thread gestionMissile(gestionMissiles, map);
                thread gestionEnnemie(gestionEnnemies, map);
                while (active)
                {
                    if (GetKeyState('W') & 0x8000) {
                        map->deplacer(player, "W");
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
                    if (GetKeyState(VK_ESCAPE) & 0x8000) {
                        active = false;
                        maxNiveau = 0;
                        system("CLS");
                        menu.setChoix(-1);
                        //exit(0);
                    }
                    Sleep(100);
                }
                if (!active) {
                    affichage.join();
                    gestionMissile.join();
                    gestionEnnemie.join();
                    niveau += 1;
                    tailleJeux += 5;
                    nombreEnnemie += 1;
                }
                cout << " " << std::endl;
            }
        }
        else if (menu.getChoix() == 2) {
            menu.showCommande();
        }
    }
    return 0;
}

