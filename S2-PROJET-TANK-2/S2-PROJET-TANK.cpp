// S2-PROJET-TANK-2.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
//:)

#include <iostream>
#include <windows.h> 
#include <thread>

#include "map.h"
#include "tank.h"
#include "direction.h"

using namespace std;

void refresh(Map map, Tank* player) {
    while (true)
    {
        system("CLS");
        std::cout << "X: " << player->getCoordonnee().x << " Y: " << player->getCoordonnee().y << std::endl;
        map.afficheMap();
        Sleep(40);
    }
}

int main()
{
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
        Sleep(100);
    }

}

