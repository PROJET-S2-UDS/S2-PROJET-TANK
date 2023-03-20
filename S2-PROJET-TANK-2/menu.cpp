#include <iostream>
#include <stdlib.h>
#include "menu.h"

Menu::Menu() {
     choix = -1;
}

void Menu::show() {
    std::cout << "||--------------------------------------||\n"
        << "||--------------------------------------||\n"
        << "||--------BIENVENUE DANS LE JEU---------||\n"
        << "||--------------------------------------||\n"
        << "||--------------------------------------||\n"
        << "||--------------------------------------||\n"
        << "||--------------------------------------||\n"
        << "||   1. Commencer une partie            ||\n"
        << "||   2. Les commandes                   ||\n"
        << "||   3. Quitter l'application           ||\n"
        << "||--------------------------------------||\n"
        << "||--------------------------------------||\n";
        std::cout << "Entrez votre choix (1-3): ";
        std::cin >> choix;
        if (choix < 0 || choix > 4) {
            std::cout << "Choix invalide, veuillez réessayer.\n";
            choix = -1;
        }
        system("CLS");
}

void Menu::executeChoice() {
    switch (choix) {
    case 1:
        std::cout << "Vous avez choisi de commencer une partie.\n";
        break;
    case 2:
        std::cout << "Vous avez choisi de voir les commandes.\n";
        break;
    case 3:
        std::cout << "Vous avez choisi de quitter l'application.\n";
        exit(0);
    default:
        break;
    }
}

int Menu::getChoix()
{
    return choix;
}

void Menu::showCommande()
{
    std::string value;
    std::cout << "||                                                          ||\n"
        << "||                                                          ||\n"
        << "||                  Commande du jeu                         ||\n"
        << "||                                                          ||\n"
        << "|| Deplacement du joueur :                                     ||\n"
        << "||      W => Avancer le joueur                              ||\n"
        << "||      S => Reculer le joueur                              ||\n"
        << "||      A => Deplacer vers la gauche                        ||\n"
        << "||      D => Deplacer vers la droite                        ||\n"
        << "||      flece gauche (<-) Deplacer le canon vers la gauche  ||\n"
        << "||      fleche droite (->) Deplacer le canon vers la droite ||\n"
        << "||      E => Tirer un missile                               ||\n"
        << "||      Espace => Deposer une bombe                         ||\n"
        << "||      Echape => Pour quitter le jeu                       ||\n";
    std::cout << "Quitter (Q) ";
    std::cin >> value;
    if (value == "Q" || value == "q") {
        system("CLS");
        choix = -1;
    }
}

void Menu::setChoix(int m_choix)
{
    choix = m_choix;
}
