#ifndef MENU_JEU_H
#define MENU_JEU_H

#include <string>
#include <vector>

#include "libMannette.h"

class Menu {
public:
    Menu();
    void show(LibMannette manette, bool manetteActive);
    void executeChoice();
    int getChoix();
    void showCommande(LibMannette manette, bool manetteActive);
    void setChoix(int m_choix);
private:
    int choix ;
};

#endif // MENU_H
