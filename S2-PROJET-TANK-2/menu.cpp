#include <iostream>
#include <stdlib.h>
#include "menu.h"

Menu::Menu() {
     choix = -1;
}

void Menu::show(LibMannette manette, bool manetteActive) {
    std::cout << "||--------------------------------------||\n"
        << "||--------------------------------------||\n"
        << "||--------BIENVENUE DANS LE JEU---------||\n"
        << "||--------------------------------------||\n"
        << "||--------------------------------------||\n"
        << "||--------------------------------------||\n"
        << "||--------------------------------------||\n"
        << "||   Q. Commencer une partie            ||\n"
        << "||   W. Les commandes                   ||\n"
        << "||   E. Quitter l'application           ||\n"
        << "||--------------------------------------||\n"
        << "||--------------------------------------||\n";
    bool active = true;
    while(active){
        if (GetKeyState('Q') & 0x8000 || (manette.get_switch1() && manetteActive)) {
            choix = 1;
            active = false;
        }
        else if (GetKeyState('W') & 0x8000 || (manette.get_switch2() && manetteActive)) {
            choix = 2;
            active = false;
        }
        else if (GetKeyState('E') & 0x8000 || (manette.get_switch3() && manetteActive)) {
            choix = 3;
            active = false;
        }
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

void Menu::showCommande(LibMannette manette, bool manetteActive)
{
    std::string value;
    std::cout << "||                                                                        ||\n"
        << "||                                                                      ||\n"
        << "||                  Commande du jeu                                     ||\n"
        << "||                                                                      ||\n"
        << "|| Deplacement du joueur avec le clavier :                              ||\n"
        << "||      W => Avancer le joueur                                          ||\n"
        << "||      S => Reculer le joueur                                          ||\n"
        << "||      A => Deplacer vers la gauche                                    ||\n"
        << "||      D => Deplacer vers la droite                                    ||\n"
        << "||      flece gauche (<-) Deplacer le canon vers la gauche              ||\n"
        << "||      fleche droite (->) Deplacer le canon vers la droite             ||\n"
        << "||      E => Tirer un missile                                           ||\n"
        << "||      Espace => Deposer une bombe                                     ||\n"
        << "||      Echape => Pour quitter le jeu                                   ||\n"
        << "||                                                                      ||\n"
        << "||                                                                      ||\n"
        << "||  Deplacement du joueur avec la manette :                             ||\n"
        << "||      Joystick vers le haut => Avancer le joueur                      ||\n"
        << "||      Joystick vers le bas => Reculer le joueur                       ||\n"
        << "||      Joystick vers la gauche => Deplacer vers la gaucghe             ||\n"
        << "||      Joystick vers la droite => Deplacer vers la droite              ||\n"
        << "||      Bouton en haut droite => Pour retourner au menu principal       ||\n"
        << "||      Bouton en haut au milieu => Tirer un missile                    ||\n"
        << "||      Bouton à gauche au milieu => Deplacer le canon vers la gauche   ||\n"
        << "||      Bouton à droite au milieu => Deplacer le canon vers la droite   ||\n\n\n";
    std::cout << "Q pour quitter ou le bouton retour";
    bool active = true;
    while (active) {
        if (GetKeyState('Q') & 0x8000 || (manette.get_switch4() && manetteActive)) {
            choix = -1;
            active = false;
        }
    }
    system("CLS");
}

void Menu::setChoix(int m_choix)
{
    choix = m_choix;
}
