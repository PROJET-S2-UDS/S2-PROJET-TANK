// S2-PROJET-TANK-2.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//


#include <iostream>
#include <windows.h> 
#include <thread>
#include <sstream>

#include "map.h"
#include "tank.h"
#include "direction.h"

using namespace std;

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

void refresh(Map map, Tank* m_tank) {
    while (m_tank->getHealth() > 0)
    {
        COORD p = { 0,0 };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
        map.afficheMap(std::cout, m_tank);
    }
    system("CLS");
    cout << "Game Over !";
}

int main()
{
    ShowConsoleCursor(false);
    Map map;
    Tank* player = new Tank("Player", 100, 0, 0, Type::player);
    int taille = 5;
    Mur* mur[5] = { new Mur(3, 2, 4, Direction::Bas), new Mur(15, 13, 6, Direction::Haut), new Mur(10, 0, 6, Direction::Droit), new Mur(2, 13, 6, Direction::Gauche), new Mur(17, 17, 6, Direction::Haut) };
    map.ajoutMur(mur, taille);
    map.ajouter(player);
    thread affichage(refresh, map, player);
    while (true)
    {
        if (GetKeyState('W') & 0x8000) {
            map.deplacer(player,"W");
        }
        if (GetKeyState('S') & 0x8000) {
            map.deplacer(player, "S");
        }
        if (GetKeyState('A') & 0x8000) {
            map.deplacer(player, "A");
        }
        if (GetKeyState('D') & 0x8000) {
            map.deplacer(player, "D");
        }
        if (GetKeyState(VK_SPACE) & 0x8000) {
            player->dropBombe(true);
        }
        Sleep(100);
    }

}

