// S2-PROJET-TANK-2.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <windows.h> 

#include "map.h"
#include "tank.h"

using namespace std;

void refresh(Map map, Tank player) {
    system("CLS");
    std::cout << "X: " << player.getCoordonnee().x << " Y: " << player.getCoordonnee().y << std::endl;
    map.afficheMap();
}

int main()
{
    Map map;
    Tank player = Tank("Tristan", 100, 0, 0, Type::player);
    map.ajouter(player);
    refresh(map, player);
    while (true)
    {
        if (GetKeyState('W') & 0x8000) {
            map.deplacer(player,"W");
            refresh(map, player);
        }
        if (GetKeyState('S') & 0x8000) {
            map.deplacer(player, "S");
            refresh(map, player);
        }
        if (GetKeyState('A') & 0x8000) {
            map.deplacer(player, "A");
            refresh(map, player);
        }
        if (GetKeyState('D') & 0x8000) {
            map.deplacer(player, "D");
            refresh(map, player);
        }
        Sleep(100);
    }

}

