#ifndef MENU_JEU_H
#define MENU_JEU_H

#include <string>
#include <vector>
#include <windows.h>
#include "Manette.hpp"

class Menu {
public:
    Menu();
    void show(lib_manette* manette);
    void executeChoice();
    int getChoix();
    void showCommande(lib_manette* manette);
    void setChoix(int m_choix);
private:
    int choix ;
};

#endif // MENU_H
