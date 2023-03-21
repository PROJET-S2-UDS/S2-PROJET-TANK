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
#include "libMannette.h"

using namespace std;

bool active = true;
bool manetteActive = false;
bool retourMenu = false;

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

void refresh(Map* map, Tank* m_tank, LibMannette manette) {
        bool boucle = true;
        COORD p = { 0,0 };
        while (boucle && active)
        {
            int healthPrevious = m_tank->getHealth();
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
            map->afficheMap(std::cout, m_tank);
            if (healthPrevious != m_tank->getHealth()) {
                manette.activer_moteur(true);
            }
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
            Sleep(1000);
            retourMenu = true;
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
    LibMannette manette1 = LibMannette(manetteActive);
    Menu menu;
    while (menu.getChoix() != 3){
        int niveau = 1;
        int maxNiveau = 10;
        int tailleJeux = 15;
        int nombreEnnemie = 1;
        Map* map;
        menu.show(manette1,manetteActive);
        retourMenu = false;
        if (menu.getChoix() == 1) {
            for (int i = 0; i < maxNiveau; i++)
            {
                active = true;
                map = new Map(tailleJeux, nombreEnnemie, niveau);
                srand(time(NULL));
                int nombreMurs = rand() % 16;
                map->generateurMap();
                Tank* player = map->getPlayer();
                thread affichage(refresh, map, player, manette1);
                thread gestionMissile(gestionMissiles, map);
                thread gestionEnnemie(gestionEnnemies, map);
                while (active)
                {
                    manette1.modifier_vie(std::round(player->getHealth()/10));
                    if (GetKeyState('W') & 0x8000 || (manette1.get_joyStrick_Gauche_X() == 1 && manetteActive) ) {
                        map->deplacer(player, "W");
                    }
                    if (GetKeyState('S') & 0x8000 || (manette1.get_joyStrick_Gauche_X() == -1 && manetteActive)) {
                        map->deplacer(player, "S");
                    }
                    if (GetKeyState('A') & 0x8000 || (manette1.get_joyStrick_Gauche_Y() == 1 && manetteActive)) {
                        map->deplacer(player, "A");
                    }
                    if (GetKeyState('D') & 0x8000 || (manette1.get_joyStrick_Gauche_Y() == -1 && manetteActive)) {
                        map->deplacer(player, "D");
                    }
                    if (GetKeyState(VK_SPACE) & 0x8000 || (manette1.get_accelerometre() && manetteActive)) {
                        player->dropBombe(true);
                    }
                    if (GetKeyState('E') & 0x8000 || (manette1.get_switch1() && manetteActive)) {
                        player->shoot(true);
                    }
                    if (GetKeyState(VK_LEFT) & 0x8000 || (manette1.get_switch2() && manetteActive)) {
                        map->deplacerCanon(player, "LEFT", 1);
                    }
                    if (GetKeyState(VK_RIGHT) & 0x8000 || (manette1.get_switch3() && manetteActive)) {
                        map->deplacerCanon(player, "RIGHT", 1);
                    }
                    if (GetKeyState('P') & 0x8000) {
                        map->killAllTank();
                    }
                    if (GetKeyState(VK_ESCAPE) & 0x8000 || (manette1.get_switch4() && manetteActive) || retourMenu) {
                        active = false;
                        maxNiveau = 0;
                        system("CLS");
                        menu.setChoix(-1);
                    }
                    Sleep(100);
                }
                if (!active) {
                    affichage.join();
                    system("CLS");
                    gestionMissile.join();
                    gestionEnnemie.join();
                    niveau += 1;
                    if (niveau < 7) {
                        tailleJeux += 5;
                    }
                    nombreEnnemie += 1;
                }
                cout << " " << std::endl;
            }
        }
        else if (menu.getChoix() == 2) {
            menu.showCommande(manette1,manetteActive);
        }
    }
    return 0;
}

